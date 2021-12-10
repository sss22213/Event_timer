#include "timer.h"

static inline void _init(struct _timer *timer)
{
    BUG_ON(EVENT_END > MAXIMUM_EVENT_NUMBER_TIMER);
    timer->ptr_init_sys_timer();

    for (int idx = 0; idx < MAXIMUM_EVENT_NUMBER_TIMER; idx++) {
        timer->event_timer[idx].ms_timeout = INT_MAX;
    }

    timer->tick = 0;
}

static inline void _delay_ms(int ms)
{

}

static inline void _swap(struct _timer *timer, struct _event_timer *event_timer1, struct _event_timer *event_timer2)
{
       struct _event_timer tmp = *event_timer1;
       *event_timer1 = *event_timer2;
       *event_timer2 = tmp;
}

static inline void _inc_tick_timer(struct _timer *timer)
{
    timer->tick++;

    if (timer->tick >= INT_MAX) {
        timer->tick = 0;
    }
}

void timer_init(struct _timer *timer)
{
    _init(timer);
}

_Bool _push(struct _timer *timer, struct _event_timer *event_timer)
{
    timer->ptr_stop_sys_timer();

    // Insert event into group.
    timer->event_timer[timer->cur_event] = *event_timer;
    timer->cur_event++;

    // Sorting (Bubble sort) by time sequence.
    for (int idx_i = 0; idx_i< MAXIMUM_EVENT_NUMBER_TIMER; idx_i++) {
        for (int idx_j = 0; idx_j < MAXIMUM_EVENT_NUMBER_TIMER; idx_j++) {
            if (timer->event_timer[idx_i].ms_timeout < timer->event_timer[idx_j].ms_timeout) {
                _swap(timer, &(timer->event_timer[idx_i]), &(timer->event_timer[idx_j]));
            }
        }
    }

    timer->ptr_start_sys_timer();

    return true;
}

_Bool timer_settimeevent(struct _timer *timer, struct _event_timer *event_timer)
{
    return _push(timer, event_timer);
}

void process_event_timer(struct _timer* timer)
{
    for (int idx = 0; idx < timer->cur_event; idx++) {
        if (timer->event_timer[idx].ms_timeout < INT_MAX && timer->tick > 0) {
            if (timer->tick % timer->event_timer[idx].ms_timeout == 0) {
                timer->event_timer[idx].ptr_excute_func();
            }
        }
    }

    _inc_tick_timer(timer);
}

