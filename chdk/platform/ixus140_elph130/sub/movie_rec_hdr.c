#include "conf.h"

void change_video_tables(int a, int b){
}

// not working, see comments in code_gen.txt
extern int video_compression_rate2;
extern int video_compression_rate;
void set_quality(){ // -17 highest; +12 lowest
 if (conf.video_mode) {
    video_compression_rate2 = video_compression_rate=12-((conf.video_quality-1)*(12+17)/(99-1));
 }
}
