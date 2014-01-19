#include "camera_info.h"
#include "stdlib.h"
#include "modes.h"
#include "clock.h"
#include "shooting.h"
#include "console.h"
#include "conf.h"
#include "keyboard.h"
#include "histogram.h"
#include "action_stack.h"
#include "script_api.h"

//----------------------------------------------------------------------------------

#define AS_FUNC_ENTRY   0xa32f1c9e      // Magic number to flag a function ptr on the stack

//----------------------------------------------------------------------------------
// action stack memory structure

#define ACTION_STACK_SIZE 48
#define MAX_ACTION_STACKS 5

typedef struct _action_stack
{
    long                    stack[ACTION_STACK_SIZE];   // Actions and parameters
    int                     stack_ptr;                  // Current position in stack
    AS_ID                   comp_id;                    // Unique ID
    unsigned long           delay_target_ticks;         // Used for sleep function
    struct _action_stack*   next;                       // next action stack
} action_stack_t;

//----------------------------------------------------------------------------------
// Global variables for implementation

static action_stack_t* action_stacks = NULL;            // List of active stacks
static action_stack_t* active_stack = NULL;             // Currently executing stack
static action_stack_t* free_stacks = NULL;              // Free list (for reuse of memory)
static int num_stacks = 0;                              // Number of active stacks
static AS_ID task_comp_id = 1;                          // Next stack ID (0 = unused / finished stack)

//----------------------------------------------------------------------------------
// Stack management functions

// Returns true if the task denoted by comp_id has finished execution.
// comp_id is returned by action_stack_create().
int action_stack_is_finished(AS_ID comp_id)
{
    action_stack_t *p = action_stacks;
    while (p)
    {
        if (p->comp_id == comp_id)
            return 0;
        p = p->next;
    }

    return 1;
}

// Starts a new action stack with initial stack entry p.
// The action stack is alive as long as its stack has entries.
// The proc_func parameter is a pointer to the initial processing function
// for the stack
AS_ID action_stack_create(action_func proc_func)
{
    // Cap the maximum number of action_stacks
    if (num_stacks == MAX_ACTION_STACKS)
        return -1;

    // Initialize new action stack
    action_stack_t* stack = 0;
    if (free_stacks)
    {
        // Reuse previous memory block
        stack = free_stacks;
        free_stacks = free_stacks->next;
    }
    else
    {
        // Get a new block
        stack = (action_stack_t*)malloc(sizeof(action_stack_t));
    }
    memset(stack,0,sizeof(action_stack_t));

    // Insert at start of list - stacks execute in order of most recent creation
    stack->next = action_stacks;
    action_stacks = stack;

    // Initialize id & processing function
    stack->comp_id = task_comp_id;
    stack->stack[0] = (long)proc_func;
    stack->stack[1] = AS_FUNC_ENTRY;    // Can't use action_push_func as active_stack not set
    stack->stack_ptr = 1;

    ++num_stacks;

    // Increment task_comp_id
    // For this to clash with a running stack you would need to leave one running
    // while 4 billion more were created - highly unlikely.
    ++task_comp_id;
    // Reset just in case it wraps around to 'finished' value
    if (task_comp_id == 0) task_comp_id = 1;

    return stack->comp_id;
}

// Clean up and release an action stack
static void action_stack_finish(action_stack_t *p)
{
    // Check in case already finalised
    if (p->comp_id == 0) return;

    // Remove 'active_stack' from the list since it is done execuing
    if (p == action_stacks)
    {
        action_stacks = action_stacks->next;
    }
    else
    {
        action_stack_t* prev = action_stacks;
        while (prev && (prev->next != p))
        {
            prev = prev->next;
        }
        if (prev)
        {
            prev->next = prev->next->next;
        }
    }

    --num_stacks;

    // Mark as free in case this function gets called again
    p->comp_id = 0;
    p->stack_ptr = -1;

    // Instead of freeing memory, save it to the free list
    // Next time this block will be reused
    p->next = free_stacks;
    free_stacks = p;
}

// Find and terminate an action stack
// comp_id is returned by action_stack_create().
void action_stack_kill(AS_ID comp_id)
{
    action_stack_t *p = action_stacks;
    while (p)
    {
        if (p->comp_id == comp_id)
        {
            action_stack_finish(p);
            return;
        }
        p = p->next;
    }
}

//----------------------------------------------------------------------------------
// Add / remove a generic entry from the stack
// Note - these assume 'active_stack' is set correctly.

// Get top Nth entry off the stack (without removing it)
// Can only be called from an action stack
long action_top(int n)
{
    if (active_stack)
        return active_stack->stack[active_stack->stack_ptr-n];
    return 0;
}

// Pop top entry off the stack
// Can only be called from an action stack
long action_pop()
{
    if (active_stack)
        return active_stack->stack[active_stack->stack_ptr--];
    return 0;
}

// Pop top func entry off the stack
// Can only be called from an action stack
long action_pop_func(int nParam)
{
    for (; nParam >= 0; nParam--)
        action_pop();
    return action_pop();    // Return function pointer / last parameter
}

// Push a new entry onto the stack
// Can only be called from an action stack
void action_push(long p)
{
    if (active_stack)
        active_stack->stack[++active_stack->stack_ptr] = p;
}

// Push a function onto the stack
void action_push_func(action_func f)
{
    action_push((long)f);
    action_push(AS_FUNC_ENTRY);
}

//----------------------------------------------------------------------------------
// Delay processing

// handle initializing and checking a timeout value set by 'delay'
// returns zero if the timeout has not expired, 1 if it has
// does not pop the delay value off the stack or clear the delay value
static int action_process_delay(long delay)
{
    unsigned t = get_tick_count();
    // FIXME take care if overflow occurs
    if (active_stack->delay_target_ticks == 0)
    {
        /* delay of -1 signals indefinite (actually 1 day) delay*/
        if(delay == -1)
            delay = 86400000;

        active_stack->delay_target_ticks = t+delay;
        return 0;
    }
    if (active_stack->delay_target_ticks <= t)
    {
        return 1;
    }
    return 0;
}

//----------------------------------------------------------------------------------
// Custom functions to push specific actions onto the stack

// Pop a sleep from the stack
// Can only be called from an action stack
void action_pop_delay()
{
    active_stack->delay_target_ticks = 0;
    action_pop_func(1);
}

// Process a sleep function from the stack
static int action_stack_AS_SLEEP()
{
    long delay = action_top(2);

    if (action_process_delay(delay))
    {
        action_pop_delay();
        return 1;
    }

    return 0;
}

// Push a sleep onto the stack
// Can only be called from an action stack
void action_push_delay(long msec)
{
    action_push(msec);
    action_push_func(action_stack_AS_SLEEP);
}

// Process a button press action from the stack
static int action_stack_AS_PRESS()
{
    extern int usb_sync_wait;

    long skey = action_pop_func(1); // Key parameter returned

    if ((skey == KEY_SHOOT_FULL) && conf.remote_enable && conf.synch_enable) usb_sync_wait = 1;

    kbd_key_press(skey);

    return 1;
}

// Push a button press action onto the stack
// Can only be called from an action stack
void action_push_press(long key)
{
    // WARNING stack program flow is reversed
    action_push_delay(camera_info.cam_key_press_delay);
    action_push(key);
    action_push_func(action_stack_AS_PRESS);
}

// Process a button release action from the stack
static int action_stack_AS_RELEASE()
{
    long skey = action_pop_func(1); // Key parameter returned
    kbd_key_release(skey);
    return 1;
}

// Push a button release action onto the stack
// Can only be called from an action stack
void action_push_release(long key)
{
    // WARNING stack program flow is reversed
    action_push_delay(camera_info.cam_key_release_delay);
    action_push(key);
    action_push_func(action_stack_AS_RELEASE);
}

// Push a button click action onto the stack (press, optional delay, release)
// Can only be called from an action stack
void action_push_click(long key)
{
    // WARNING stack program flow is reversed
    action_push_release(key);
    action_push_press(key);
}

//----------------------------------------------------------------------------------
// 'Shoot' actions

// Action stack function - wait for shooting to be finished
// parameters - retry flag
static int action_stack_AS_WAIT_SHOOTING_DONE()
{
    // Are we there yet?
    if (!shooting_in_progress())
    {
        // Remove this action from stack
        int retry = action_pop_func(1); // Retry parameter returned

        // Check if shoot succeeded or not
        if (camera_info.state.state_shooting_progress == SHOOTING_PROGRESS_NONE)
        {
            if (retry)
            {
                // Shoot failed, retry once, if it fails again give up
                action_push_shoot(0);

                // Short delay before retrying shoot
                action_push_delay(250);
            }
            else
            {
                // Failed - already retried, or no retry requested
                // Return 'shoot' status to script - 2 = shoot failed
                libscriptapi->set_as_ret(2);
            }
        }
        else
        {
            // Return 'shoot' status to script - 0 = shoot succesful
            libscriptapi->set_as_ret(0);

            // Final script config delay (XXX FIXME find out how to wait to jpeg save finished)
            if (conf.script_shoot_delay > 0)
                action_push_delay(conf.script_shoot_delay*100);
        }

        return 1;
    }
    return 0;
}

// Action stack function - wait for flash to charge
static int action_stack_AS_WAIT_FLASH()
{
    if (shooting_is_flash_ready())
    {
        action_pop_func(0);
        return 1;
    }
    return 0;
}

// Action stack function - wait for camera ready to shoot after half press, or timeout
// parameters - timeout delay, retry flag
static int action_stack_AS_WAIT_SHOOTING_IN_PROGRESS()
{
    // Get parameters
    int timeout = action_top(2);
    int retry = action_top(3);

    if (shooting_in_progress() || camera_info.state.mode_video)
    {
        // Remove this action from the stack
        action_pop_func(2);

        // Push the rest of the shoot actions onto the stack (reversed flow)

        // Push 'retry if failed' parameter for exit action
        action_push(retry);
        action_push_func(action_stack_AS_WAIT_SHOOTING_DONE);

        // Full press shutter
        action_push_click(KEY_SHOOT_FULL);

        // Wait for flash recharged
        action_push_func(action_stack_AS_WAIT_FLASH);

        return 1;
    }
    if (get_tick_count() >= timeout)
    {
        // Remove this action from the stack
        action_pop_func(2);

        // Return 'shoot' status to script - 1 = shutter half press timed out
        libscriptapi->set_as_ret(1);

        return 1;
    }
    return 0;
}

// Push the core 'shoot' actions onto the stack
// Note: action stack actions are processed in reverse order
void action_push_shoot(int retry)
{
    // Init shooting state
    camera_info.state.state_shooting_progress = SHOOTING_PROGRESS_NONE;

    // Wait for camera ready to shoot or timeout
    action_push(retry);
    action_push(get_tick_count() + 5000);
    action_push_func(action_stack_AS_WAIT_SHOOTING_IN_PROGRESS);

    // Half press shutter
    action_push_press(KEY_SHOOT_HALF);
}

int action_stack_AS_SHOOT()
{
    // Remove this action from stack
    action_pop_func(0);

    // Push the shoot actions (with retry on shoot failure)
    action_push_shoot(1);

    return 1;
}

//----------------------------------------------------------------------------------
// Stack execution

// Run the topmost function on the active stack.
static void action_stack_process()
{
    int process = 1;

    while (process && (active_stack->stack_ptr >= 0))
    {
        // Get function address and id from stack
        long id = action_top(0);
        action_func f = (action_func)action_top(1);
        if (id == AS_FUNC_ENTRY)    // Safety check
        {
            process = f();
        }
        else
        {
            char buf[100];
            sprintf(buf,"AS Error - Not a Function. Aborting. %d %08x %08x.",active_stack->stack_ptr,id,f);
            script_console_add_line((long)buf);
            action_stack_finish(active_stack);
            return;
        }
    }

    if (active_stack->stack_ptr < 0)
    {
        action_stack_finish(active_stack);
    }
}

// Run the topmost function on each stack
void action_stack_process_all()
{
    active_stack = action_stacks;

    while (active_stack)
    {
        // Save the next stack in case the current one ends and 
        // releases it's stack during execution
        action_stack_t *next = active_stack->next;

        // Process stack functions
        action_stack_process();

        active_stack = next;
    }
}

//----------------------------------------------------------------------------------
