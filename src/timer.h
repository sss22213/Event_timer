#ifndef __TIMER_H__
#define __TIMER_H__
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#define UNUSED(x) ((void)(x))
#define TIMER_BUG_ON(x) UNUSED(sizeof(struct {int:-!!(x);}))
#define MAXIMUM_EVENT_NUMBER_TIMER  30 
#define GET_CURRENT_TIMER(NAME_TIMER) ((NAME_TIMER)->tick)

#define NEW_TIMER(NAME_TIMER, PTR_INIT_SYS_TIMER, PTR_START_SYS_TIMER, PTR_STOP_SYS_TIMER, PTR_PROCESS_EVENT_TIMER) \
                        struct _timer (NAME_TIMER) = {\
                            .ptr_init_sys_timer = (PTR_INIT_SYS_TIMER),\
                            .ptr_start_sys_timer = (PTR_START_SYS_TIMER),\
                            .ptr_stop_sys_timer = (PTR_STOP_SYS_TIMER),\
                            .ptr_process_event_timer = process_event_timer,\
                            .ptr_event_timer = (PTR_PROCESS_EVENT_TIMER)\
                        }

#define NEW_EVENT_TIMER(NAME_EVENT_TIMER, EVENT_TIMER, TIMEOUT_MS) \
                            struct _event_timer NAME_EVENT_TIMER = {\
                                .event = EVENT_TIMER,\
                                .ms_timeout = TIMEOUT_MS\
                            }
                            
#define EVENT_TIMER_FOR_EACH(NAME_TIMER, CALLBACK_FUNC) \
                        for (int idx = 0; idx < MAXIMUM_EVENT_NUMBER_TIMER; idx++) \
                        {\
                            CALLBACK_FUNC((NAME_TIMER)->event_timer[idx]);\
                        }

typedef enum {
    EVENT_HEAD,
    EVENT_TEST,
    EVENT_TEST1,
    EVENT_TEST2
} TIMER_EVENT;

struct _event_timer {
    TIMER_EVENT event;
    uint32_t ms_timeout;
};

struct _timer {
    uint32_t tick;
    uint32_t delay_count;
    struct _event_timer event_timer[MAXIMUM_EVENT_NUMBER_TIMER];
    void (*ptr_init_sys_timer)(void);
    void (*ptr_start_sys_timer)(void);
    void (*ptr_stop_sys_timer)(void);
    void (*ptr_process_event_timer)(struct _timer*);
    void (*ptr_event_timer)(TIMER_EVENT);
};

_Bool timer_settimeevent(struct _timer*, struct _event_timer*);
void process_event_timer(struct _timer*);
void timer_init(struct _timer*);
void timer_delay(struct _timer*, int);

#endif