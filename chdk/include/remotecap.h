/* remotecap functions and structures exported to modules*/
#ifndef REMOTECAP_H
#define REMOTECAP_H
typedef struct {
    unsigned int address;
    unsigned int length;
} ptp_data_chunk;

// get supported remote capture data types
int remotecap_get_target_support(void);
// set request remote capture data
int remotecap_set_target(int type, int lstart, int lcount);
// set timeout for hooks, in ms. <=0 sets default
void remotecap_set_timeout(int timeout);
// returns non-zero if remotecap requires the DNG module to stay loaded
int remotecap_using_dng_module();
#endif
