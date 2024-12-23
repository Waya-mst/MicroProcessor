#include "crt0.c"
#include "ChrFont0.h"

void interrupt_handler(){}

void main(){
    volatile int *sw_ptr = (int *)0xff04;
    volatile int *led7seg_ptr = (int *)0xff18;

    for(;;){
        *led7seg_ptr = *sw_ptr;
    }
}