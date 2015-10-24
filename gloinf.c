
#include "gloinf.h"
#include <time.h>

struct tm *gloinf_gmtime(int32_t n4, int32_t n);

struct tm *gloinf_gmtime(int32_t n4, int32_t n) {
    time_t t = ((26 + 4 * (n4 - 1)) * 36525) + (n - 1) * 100;
    t *= 864;
    t -= 43200/* + 3 * 3600*/;
    return gmtime(&t);
}

void gloinf_print(gloinf_frame *frame) {
    int32_t h, m, s, ds;
    time_t t;
    struct tm *stm;
    
    h = (frame->s1.t >> 7) & 0x1F;
    m = (frame->s1.t >> 1) & 0x3F;
    s = (frame->s1.t & 0x1) ? 30 : 0;

    stm = gloinf_gmtime(frame->s5.n4, frame->s4.nt);
    ds = (h * 3600 + m * 60 + s) % 86400;

    printf("%02d %02d %04d %5d SCAE\n", stm->tm_mday, stm->tm_mon, 1900 + stm->tm_year, ds);
    stm = gloinf_gmtime(frame->s5.n4, frame->s5.n);
    printf("%2d %2d %2d %02d\n", frame->s6.n, frame->s7.h, frame->s6.c, stm->tm_mday);
    
    printf("%02d:%02d:%02d\n", h, m, s);
    stm = gloinf_gmtime(frame->s5.n4, frame->s5.n);
    t = mktime(stm);
    puts(ctime(&t));
    
//    printf("frame index: %d, %d, %d\n", frame->frame_index, frame->s6.n, y);
}

