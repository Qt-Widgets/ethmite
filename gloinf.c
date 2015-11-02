
#include "gloinf.h"
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

char frameset = 0;
gloinf_frame almanac[5];

struct tm *gloinf_gmtime(int32_t n4, int32_t n);
void gloinf_print_frame(FILE *stream, gloinf_frame *frame);
void gloinf_print_unit(FILE *stream, int32_t secday, gloinf_line4 *s4, gloinf_line5 *s5, gloinf_linea1 *a1, gloinf_linea2 *a2);

struct tm *gloinf_gmtime(int32_t n4, int32_t n) {
    time_t t = ((26 + 4 * (n4 - 1)) * 36525) + (n - 1) * 100;
    t *= 864;
    t -= 43200/* + 3 * 3600*/;
    return gmtime(&t);
}

void gloinf_print_frame(FILE *stream, gloinf_frame *frame) {
    int32_t h, m, s, secday;
    
    h = (frame->s1.t >> 7) & 0x1F;
    m = (frame->s1.t >> 1) & 0x3F;
    s = (frame->s1.t & 0x1) ? 30 : 0;
    secday = (h * 3600 + m * 60 + s) % 86400;

    gloinf_print_unit(stream, secday, &frame->s4, &frame->s5, &frame->s6 , &frame->s7 );
    gloinf_print_unit(stream, secday, &frame->s4, &frame->s5, &frame->s8 , &frame->s9 );
    gloinf_print_unit(stream, secday, &frame->s4, &frame->s5, &frame->s10, &frame->s11);
    gloinf_print_unit(stream, secday, &frame->s4, &frame->s5, &frame->s12, &frame->s13);
    if (frame->frame_index < 5) {
        gloinf_print_unit(stream, secday, &frame->s4, &frame->s5, &frame->s14, &frame->s15);
    }
}

void gloinf_print_unit(FILE *stream, int32_t secday, gloinf_line4 *s4, gloinf_line5 *s5, gloinf_linea1 *a1, gloinf_linea2 *a2) {
    struct tm *stm;

    stm = gloinf_gmtime(s5->n4, s4->nt);

    fprintf(stream, "%02d %02d %04d %8d SCAEGROUP\n", 
            stm->tm_mday, stm->tm_mon + 1, stm->tm_year + 1900, secday);
    stm = gloinf_gmtime(s5->n4, s5->n);

    fprintf(stream, "%2d % 3d %2d  %02d %02d %04d % 16.9E % 16.9E % 16.9E % 16.9E\n", 
            a1->n, a2->h, a1->c, 
            stm->tm_mday, stm->tm_mon + 1, stm->tm_year + 1900, 
            a2->t, s5->tau, s5->taug, a1->tau);
    fprintf(stream, "% 14.7E % 14.7E % 14.7E % 14.7E % 14.7E % 14.7E\n", 
            a1->lambda, a1->di, a2->omega, a1->eps, 
            a2->dt, a2->dtt);
    
//    time_t t;
//    stm = gloinf_gmtime(s5->n4, s5->n);
//    t = mktime(stm);
//    puts(ctime(&t));
//    fprintf("frame index: %d, %d, %d\n", frame_index, a1->n, y);
}

void gloinf_print(gloinf_frame *frame) {
    int32_t index;
    char framebit;
    
	setlocale(LC_NUMERIC, "C");
    _set_output_format(_TWO_DIGIT_EXPONENT);
    
    index = frame->frame_index - 1;
    
    if (frame->frame_index > 0 && frame->frame_index <= 5) {
        framebit = (char)(1 << index);
        if (!(frameset & framebit)) {
            memcpy(&almanac[index], frame, sizeof(gloinf_frame));
//            gloinf_print_frame(stdout, frame);
            frameset |= framebit;
        }
        
        if (frameset == 0x1F) {
//            puts("ENDOFFRAME");
            gloinf_save("latest.agl");
            frameset = 0;
        }
    }
}

void gloinf_save(const char *fname) {
    FILE *f;
    int32_t i;
    gloinf_frame *frame;
	setlocale(LC_NUMERIC, "C");
    f = fopen(fname, "w");
    if (f == NULL) {
        printf("Error: gloinf_save fopen %s\n", fname);
    }
    else {
        for (i = 0; i < 5; i++) {
            frame = &almanac[i];
            gloinf_print_frame(f, frame);
        }
        fclose(f);
    }
}

