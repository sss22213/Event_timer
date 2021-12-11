#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdio.h>

typedef enum {
    EVENT_HEAD,
    EVENT_TEST,
    EVENT_TEST1,
    EVENT_TEST2
} TIMER_EVENT;

void process_event(TIMER_EVENT timer_event);

#endif