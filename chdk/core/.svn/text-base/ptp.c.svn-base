#include "camera_info.h"
#include "stddef.h"
#include "stdlib.h"
#include "keyboard.h"
#include "ptp_chdk.h"
#include "core.h"
#include "task.h"
#include "script.h"
#include "action_stack.h"
#include "live_view.h"
#include "meminfo.h"
#include "modules.h"
#include "callfunc.h"

#include "remotecap_core.h"
static int buf_size=0;

// process id for scripts, increments before each attempt to run script
// does not handle wraparound
static unsigned script_run_id; 

static int handle_ptp(
                int h, ptp_data *data, int opcode, int sess_id, int trans_id,
                int param1, int param2, int param3, int param4, int param5);

static void init_chdk_ptp()
{
  int r;
 
  // wait until ptp_handlers_info is initialised and add CHDK PTP interface
  r = 0x17;
  while ( r==0x17 )
  {
    r = add_ptp_handler(PTP_OC_CHDK,handle_ptp,0);
    msleep(250);
  }

  ExitTask();
}

void init_chdk_ptp_task()
{
    CreateTask("InitCHDKPTP", 0x19, 0x200, init_chdk_ptp);
};

/*
WARNING: it appears that on some vxworks cameras,
if a call to recv_ptp_data doesn't end on a word (4 byte) boundery,
subsequent calls will return corrupt data
the final call not ending on a word boundery is OK.
see http://chdk.setepontos.com/index.php?topic=6730.msg76760#msg76760
*/
static int recv_ptp_data(ptp_data *data, char *buf, int size)
  // repeated calls per transaction are ok
{
  while ( size >= buf_size )
  {
    data->recv_data(data->handle,buf,buf_size,0,0);
    // XXX check for success??

    size -= buf_size;
    buf += buf_size;
  }
  if ( size != 0 )
  {
    data->recv_data(data->handle,buf,size,0,0);
    // XXX check for success??
  }

  return 1;
}

// camera will shut down if you ignore a recv data phase
static void flush_recv_ptp_data(ptp_data *data,int size) {
  char *buf;
  buf = malloc((size > buf_size) ? buf_size:size);
  if(!buf) // buf_size should always be less then available memory
    return;
  while ( size > 0 )
  {
    if ( size >= buf_size )
    {
      recv_ptp_data(data,buf,buf_size);
      size -= buf_size;
    } else {
      recv_ptp_data(data,buf,size);
      size = 0;
    }
  }
  free(buf);
}

static int send_ptp_data(ptp_data *data, const char *buf, int size)
  // repeated calls per transaction are *not* ok
{
  int tmpsize;
  
  tmpsize = size;
  while ( size >= buf_size )
  {
    if ( data->send_data(data->handle,buf,buf_size,tmpsize,0,0,0) )
    {
      return 0;
    }

    tmpsize = 0;
    size -= buf_size;
    buf += buf_size;
  }
  if ( size != 0 )
  {
    if ( data->send_data(data->handle,buf,size,tmpsize,0,0,0) )
    {
      return 0;
    }
  }

  return 1;
}

// TODO this could be a generic ring buffer of words
#define PTP_SCRIPT_MSG_Q_LEN 16
typedef struct {
  unsigned r; // index of current read value
  unsigned w; // index of next write value, if w == r, empty TODO "full" currently wastes a slot
  ptp_script_msg *q[PTP_SCRIPT_MSG_Q_LEN];
} ptp_script_msg_q;

// TODO it would be better to allocate these only when needed
ptp_script_msg_q msg_q_in; // messages to pc from script
ptp_script_msg_q msg_q_out; // messages to script from pc

unsigned script_msg_q_next(unsigned i) {
  if(i == PTP_SCRIPT_MSG_Q_LEN - 1) {
    return 0;
  }
  return i+1;
}

unsigned script_msg_q_full(ptp_script_msg_q *q) {
  return (script_msg_q_next(q->w) == q->r);
}

unsigned script_msg_q_empty(ptp_script_msg_q *q) {
  return (q->w == q->r);
}

int enqueue_script_msg(ptp_script_msg_q *q,ptp_script_msg *msg) {
  unsigned w = script_msg_q_next(q->w);
  if(w == q->r) {
    return 0;
  }
  if(msg == NULL) {
    return 0;
  }
  q->q[q->w] = msg;
  q->w = w;
  return 1;
}

ptp_script_msg* dequeue_script_msg(ptp_script_msg_q *q) {
  ptp_script_msg *msg;
  if(script_msg_q_empty(q)) {
    return NULL;
  }
  msg = q->q[q->r];
  q->r = script_msg_q_next(q->r);
  return msg;
}

// remove all messages from queue
void empty_script_msg_q(ptp_script_msg_q *q) {
    ptp_script_msg *msg;
    while((msg = dequeue_script_msg(q))) {
        free(msg);
    }
}

// public interface for script
// create a message to be queued later
ptp_script_msg* ptp_script_create_msg(unsigned type, unsigned subtype, unsigned datasize, const void *data) {
  ptp_script_msg *msg;
  msg = malloc(sizeof(ptp_script_msg) + datasize);
  msg->size = datasize;
  msg->type = type;
  msg->subtype = subtype;
  // caller may fill in data themselves
  // datasize may be empty (e.g. empty string)
  if(data && datasize) {
      memcpy(msg->data,data,msg->size);
  }
  return msg;
}

// add a message to the outgoing queue
int ptp_script_write_msg(ptp_script_msg *msg) {
  msg->script_id = script_run_id;
  return enqueue_script_msg(&msg_q_out,msg);
}

// retrieve the next message in the incoming queue
ptp_script_msg* ptp_script_read_msg(void) {
  ptp_script_msg *msg;
  while(1) {
    msg = dequeue_script_msg(&msg_q_in); 
    // no messages
    if(!msg) {
        return NULL;
    }
    // does message belong to our script
    if(!msg->script_id || msg->script_id == script_run_id) {
      return msg;
    } else {
    // no: discard and keep looking
      free(msg);
    }
  }
}

// convenience function write an error message
int ptp_script_write_error_msg(unsigned errtype, const char *err) {
  if(script_msg_q_full(&msg_q_out)) {
    return 0;
  }
  ptp_script_msg *msg = ptp_script_create_msg(PTP_CHDK_S_MSGTYPE_ERR,errtype,strlen(err),err);
  if(!msg) {
    return 0;
  }
  return ptp_script_write_msg(msg);
}

static char*   ptp_script = 0;
static int     ptp_script_state = 0;

// Called from kbd process to start PTP script
// Load Lua module, parse PTP script and start execution if parse ok.
void start_ptp_script()
{
    if (ptp_script)
    {
        module_set_script_lang(0);  // Force Lua script language
        if (libscriptapi->script_start(ptp_script,1))
        {
            camera_info.state.auto_started = 0;
            ptp_script_state = script_stack_start();
        }
        else
            ptp_script_state = -1;
        ptp_script = 0;
    }
}

// Setup for kbd task to start script, wait until started and return startup state
static long script_start_ptp( char *script )
{
    ptp_script = script;
    while (ptp_script) msleep(10);
    return ptp_script_state;
}

static int handle_ptp(
               int h, ptp_data *data, int opcode, int sess_id, int trans_id,
               int param1, int param2, int param3, int param4, int param5)
{
  static union {
    char *str;
  } temp_data;
  static int temp_data_kind = 0; // 0: nothing, 1: ascii string
  static int temp_data_extra; // size (ascii string)
  PTPContainer ptp;

  // initialise default response
  memset(&ptp,0,sizeof(PTPContainer));
  ptp.code = PTP_RC_OK;
  ptp.sess_id = sess_id;
  ptp.trans_id = trans_id;
  ptp.num_param = 0;
  
  // TODO 
  // calling this on every PTP command is not good on cameras without CAM_FIRMWARE_MEMINFO
  // since it figures out free memory by repeatedly malloc'ing!
  // using half of available memory may be undesirable in some cases as well
  buf_size=(core_get_free_memory()>>1);
  // make sure size is an integer number of words (avoid some possible issues with multiple receive calls)
  buf_size &= 0xFFFFFFFC;

  // handle command
  switch ( param1 )
  {

    case PTP_CHDK_Version:
      ptp.num_param = 2;
      ptp.param1 = PTP_CHDK_VERSION_MAJOR;
      ptp.param2 = PTP_CHDK_VERSION_MINOR;
      break;
    case PTP_CHDK_ScriptSupport:
      ptp.num_param = 1;
      ptp.param1 = 0;
      ptp.param1 |= PTP_CHDK_SCRIPT_SUPPORT_LUA;
      break;
    case PTP_CHDK_ScriptStatus:
      ptp.num_param = 1;
      ptp.param1 = 0;
      ptp.param1 |= script_is_running()?PTP_CHDK_SCRIPT_STATUS_RUN:0;
      ptp.param1 |= (!script_msg_q_empty(&msg_q_out))?PTP_CHDK_SCRIPT_STATUS_MSG:0;
      break;
    case PTP_CHDK_GetMemory:
      if ( param2 == 0 || param3 < 1 ) // null pointer or invalid size?
      {
        ptp.code = PTP_RC_GeneralError;
        break;
      }

      if ( !send_ptp_data(data,(char *) param2,param3) )
      {
        ptp.code = PTP_RC_GeneralError;
      }
      break;
      
    case PTP_CHDK_SetMemory:
      if ( param2 == 0 || param3 < 1 ) // null pointer or invalid size?
      {
        ptp.code = PTP_RC_GeneralError;
        break;
      }

      data->get_data_size(data->handle); // XXX required call before receiving
      if ( !recv_ptp_data(data,(char *) param2,param3) )
      {
        ptp.code = PTP_RC_GeneralError;
      }
      break;

    case PTP_CHDK_CallFunction:
      {
        int s = data->get_data_size(data->handle);
        if (s <= 0 || (s&3)) // no data or not an integer number of args
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        unsigned *buf = malloc(s);

        if ( buf == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        if ( recv_ptp_data(data,(char *) buf,s) )
        {
          ptp.num_param = 1;
          ptp.param1 = call_func_ptr((void *)buf[0],(unsigned *)buf+1,(s-4)/4);
        } else {
          ptp.code = PTP_RC_GeneralError;
        }

        free(buf);
        break;
      }

    case PTP_CHDK_TempData:
      if ( param2 & PTP_CHDK_TD_DOWNLOAD )
      {
        const char *s = NULL;
        size_t l = 0;

        if ( temp_data_kind == 0 )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        if ( temp_data_kind == 1 )
        {
          s = temp_data.str;
          l = temp_data_extra;
        }

        if ( !send_ptp_data(data,s,l) )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        
      } else if ( ! (param2 & PTP_CHDK_TD_CLEAR) ) {
        if ( temp_data_kind == 1 )
        {
          free(temp_data.str);
        }
        temp_data_kind = 0;

        temp_data_extra = data->get_data_size(data->handle);

        temp_data.str = (char *) malloc(temp_data_extra);
        if ( temp_data.str == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        if ( !recv_ptp_data(data,temp_data.str,temp_data_extra) )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        temp_data_kind = 1;
      }
      if ( param2 & PTP_CHDK_TD_CLEAR )
      {
        if ( temp_data_kind == 1 )
        {
          free(temp_data.str);
        }
        temp_data_kind = 0;
      }
      break;

    case PTP_CHDK_UploadFile:
      {
        FILE *f=NULL;
        char *buf=NULL, *fn=NULL;
        unsigned data_size,fn_len,chunk_size;
        data_size = data->get_data_size(data->handle);
        while ( data_size > 0 ) {
            chunk_size = (data_size > buf_size) ? buf_size:data_size;
            // first time through
            // allocate buffer, parse out the file name and open file
            if(!buf) {
                buf=malloc(chunk_size);
                if(!buf) {
                    ptp.code = PTP_RC_GeneralError;
                    break;
                }
                recv_ptp_data(data,buf,chunk_size);
                fn_len = *(unsigned *)buf;
                fn = malloc(fn_len+1);
                if(!fn) {
                    ptp.code = PTP_RC_GeneralError;
                    break;
                }
                memcpy(fn,buf+4,fn_len);
                fn[fn_len] = 0;
                f = fopen(fn,"wb");
                free(fn);
                if(!f) {
                    ptp.code = PTP_RC_GeneralError;
                    break;
                }
                fwrite(buf+4+fn_len,1,chunk_size - 4 - fn_len,f);
            } else {
                recv_ptp_data(data,buf,chunk_size);
                fwrite(buf,1,chunk_size,f);
            }
            data_size -= chunk_size;
        }
        if(f) {
            fclose(f);
        }

        free(buf);
        if(data_size > 0 && ptp.code != PTP_RC_OK) { 
            flush_recv_ptp_data(data,data_size); 
        } 
        break;
      }
      
    case PTP_CHDK_DownloadFile:
      {
        FILE *f;
        int tmp,t,s,r;
        char *buf, *fn;

        if ( temp_data_kind != 1 )
        {
          // send dummy data, otherwise error hoses connection
          send_ptp_data(data,"\0",1);
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        fn = (char *) malloc(temp_data_extra+1);
        if ( fn == NULL )
        {
          // send dummy data, otherwise error hoses connection
          send_ptp_data(data,"\0",1);
          free(temp_data.str);
          temp_data_kind = 0;
          ptp.code = PTP_RC_GeneralError;
          break;
        }
        memcpy(fn,temp_data.str,temp_data_extra);
        fn[temp_data_extra] = '\0';

        free(temp_data.str);
        temp_data_kind = 0;

        f = fopen(fn,"rb");
        if ( f == NULL )
        {
          // send dummy data, otherwise error hoses connection
          send_ptp_data(data,"\0",1);
          ptp.code = PTP_RC_GeneralError;
          free(fn);
          break;
        }
        free(fn);

        fseek(f,0,SEEK_END);
        s = ftell(f);
        fseek(f,0,SEEK_SET);

        buf = (char *) malloc(buf_size);
        if ( buf == NULL )
        {
          // send dummy data, otherwise error hoses connection
          send_ptp_data(data,"\0",1);
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        tmp = s;
        t = s;
        while ( (r = fread(buf,1,(t<buf_size)?t:buf_size,f)) > 0 )
        {
          t -= r;
          // cannot use send_ptp_data here
          data->send_data(data->handle,buf,r,tmp,0,0,0);
          tmp = 0;
        }
        fclose(f);
        // XXX check that we actually read/send s bytes! (t == 0)

        ptp.num_param = 1;
        ptp.param1 = s;

        free(buf);

        break;
      }
      break;

    case PTP_CHDK_ExecuteScript:
      {
        int s;
        char *buf;

        ptp.num_param = 2;
        ptp.param1 = script_run_id; // in error case, ID of most recent script

        s = data->get_data_size(data->handle);

        if ( (param2&PTP_CHDK_SL_MASK) != PTP_CHDK_SL_LUA )
        {
          flush_recv_ptp_data(data,s);
          ptp.code = PTP_RC_ParameterNotSupported;
          break;
        }
        
        buf = (char *) malloc(s);
        if ( buf == NULL )
        {
          ptp.code = PTP_RC_GeneralError;
          break;
        }

        recv_ptp_data(data,buf,s);

        // applies to both running and "interrupted" state, since interrupted means running restore
        if (camera_info.state.state_kbd_script_run) {
            // note script ID is still incremented in this case
            if (param2 & PTP_CHDK_SCRIPT_FL_NOKILL) {
                // no message is added in this case, since the running script might also be doing 
                // stuff with messages
                ptp.param2 = PTP_CHDK_S_ERR_SCRIPTRUNNING;
                free(buf);
                break;
            }
            // kill the script
            script_wait_terminate();
        }
        // empty message queues if requested. 
        if(param2 & PTP_CHDK_SCRIPT_FL_FLUSH_CAM_MSGS) {
            empty_script_msg_q(&msg_q_out);
        }
        // Script either was not running or has been killed, so safe to remove from inbound queue outside of kbd task
        if(param2 & PTP_CHDK_SCRIPT_FL_FLUSH_HOST_MSGS) {
            empty_script_msg_q(&msg_q_in);
        }

        // increment script ID if script is loaded
        script_run_id++;
        ptp.param1 = script_run_id;

        // error details will be passed in a message
        if (script_start_ptp(buf) < 0) {
          ptp.param2 = PTP_CHDK_S_ERRTYPE_COMPILE;
        } else {
          ptp.param2 = PTP_CHDK_S_ERRTYPE_NONE;
        }

        free(buf);
        
        break;
      }
    case PTP_CHDK_ReadScriptMsg:
    {
      char *pdata="";
      unsigned datasize=1;

      ptp_script_msg *msg = dequeue_script_msg(&msg_q_out);
      ptp.num_param = 4;
      if(msg) {
        ptp.param1 = msg->type;
        ptp.param2 = msg->subtype;
        ptp.param3 = msg->script_id;
        ptp.param4 = msg->size;
        // empty messages must have a data phase, so use default if no data
        if(msg->size) {
            datasize = msg->size;
            pdata = msg->data;
        }
	  } else {
        // return a fully formed message for easier handling
        ptp.param1 = PTP_CHDK_S_MSGTYPE_NONE;
        ptp.param2 = 0;
        ptp.param3 = 0;
        ptp.param4 = 0;
      }

      // NOTE message is lost if sending failed
      if ( !send_ptp_data(data,pdata,datasize) )
      {
        ptp.code = PTP_RC_GeneralError;
      }
      free(msg);
      break;
    }
    case PTP_CHDK_WriteScriptMsg:
    {
      int msg_size;
      ptp_script_msg *msg;
      ptp.num_param = 1;
      ptp.param1 = PTP_CHDK_S_MSGSTATUS_OK;
      if (!script_is_running()) {
        ptp.param1 = PTP_CHDK_S_MSGSTATUS_NOTRUN;
      } else if(param2 && param2 != script_run_id) {// check if target script for message is running
        ptp.param1 = PTP_CHDK_S_MSGSTATUS_BADID;
      } else if(script_msg_q_full(&msg_q_in)) {
        ptp.param1 = PTP_CHDK_S_MSGSTATUS_QFULL;
      }

      msg_size = data->get_data_size(data->handle);

      // if something was wrong, don't bother creating message, just flush
      if(ptp.param1 != PTP_CHDK_S_MSGSTATUS_OK) {
        flush_recv_ptp_data(data,msg_size);
        break;
      }
      msg = ptp_script_create_msg(PTP_CHDK_S_MSGTYPE_USER,PTP_CHDK_TYPE_STRING,msg_size,NULL);
      if ( !msg ) // malloc error or zero size
      {
        // if size is zero, things will get hosed no matter what
        flush_recv_ptp_data(data,msg_size);
        ptp.code = PTP_RC_GeneralError;
        break;
      }
      msg->script_id = param2;
      if ( !recv_ptp_data(data,msg->data,msg->size) )
      {
        ptp.code = PTP_RC_GeneralError;
        free(msg);
        break;
      }
      if( !enqueue_script_msg(&msg_q_in,msg) ) {
        ptp.code = PTP_RC_GeneralError;
        free(msg);
      }
      break;
    }

    case PTP_CHDK_GetDisplayData:
        {
            extern int live_view_get_data(ptp_data *data, int flags);

            ptp.num_param = 1;
            ptp.param1 = live_view_get_data(data,param2);
            if(!ptp.param1)
            {
                ptp.code = PTP_RC_GeneralError;
                // send dummy data, otherwise error hoses connection
                send_ptp_data(data,"\0",1);
            }
        }
        break;
    case PTP_CHDK_RemoteCaptureIsReady:
        ptp.num_param = 2;
        remotecap_is_ready(&ptp.param1,&ptp.param2);
        break;
    case PTP_CHDK_RemoteCaptureGetData:
        {
            unsigned int rcgd_size;
            int rcgd_status;
            char *rcgd_addr;
            int rcgd_pos;

            rcgd_status = remotecap_get_data_chunk(param2, &rcgd_addr, &rcgd_size, &rcgd_pos);
            ptp.num_param = 3;
            ptp.param3 = rcgd_pos; //client needs to seek to this file position before writing the chunk (-1 = ignore)
            if ( (rcgd_addr==0) || (rcgd_size==0) ) {
                // send dummy data, otherwise error hoses connection
                send_ptp_data(data,"\0",1);
                ptp.param1 = 0; //size
                ptp.param2 = 0; //0 = no more chunks
            } else {
                // send directly using send_data to avoid multiple send calls
                data->send_data(data->handle,rcgd_addr,rcgd_size,rcgd_size,0,0,0);
                
                ptp.param1 = rcgd_size; //size
                if(rcgd_status == REMOTECAP_CHUNK_STATUS_MORE) {
                    ptp.param2 = 1;
                } else {
                    ptp.param2 = 0;
                }
            }
            // data send complete, free hooks etc as needed, set error status if required
            if(!remotecap_send_complete(rcgd_status,param2)) {
                ptp.code = PTP_RC_GeneralError;
            }
        }
        break;
    default:
      ptp.code = PTP_RC_ParameterNotSupported;
      break;
  }

  // send response
  data->send_resp( data->handle, &ptp, 0 );
  
  return 1;
}
