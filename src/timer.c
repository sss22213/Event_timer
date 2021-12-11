#include "timer.h"

/**
 * @brief Initial timer 
 * 
 * @param timer structure of timer
 */
static inline void _init(struct _timer *timer)
{
    timer->ptr_init_sys_timer();

    for (int idx = 0; idx < MAXIMUM_EVENT_NUMBER_TIMER; idx++) {
        timer->event_timer[idx].ms_timeout = 0;
    }

    timer->tick = 0;

    timer->ptr_start_sys_timer();
}

/**
 * @brief Increase tick
 * 
 * @param timer structure of timer
 */
static inline void _inc_tick_timer(struct _timer *timer)
{
    timer->tick++;

    if (timer->tick >= INT_MAX) {
        timer->tick = 0;
    }
}

/**
 * @brief Decrease timer tick
 * 
 * @param timer structure of timer
 */
static inline void _dec_delay_timer(struct _timer *timer)
{
    timer->delay_count--;
}

/**
 * @brief Initial timer by call function _init
 * 
 * @param timer structure of timer
 */
void timer_init(struct _timer *timer)
{
    _init(timer);
}

/**
 * @brief Push event_timer into group
 * 
 * @param timer structure of timer
 * @param event_timer timer event
 * 
 * @retval If success, return true.Otherwise, return false.
 */
_Bool _push(struct _timer *timer, struct _event_timer *event_timer)
{
    timer->ptr_stop_sys_timer();
    
    // Insert event into empty object in group.
    for (int event_idx = 1; event_idx < MAXIMUM_EVENT_NUMBER_TIMER; event_idx++) {
        if (timer->event_timer[event_idx].ms_timeout <= 0) {
            timer->event_timer[event_idx] = *event_timer;
            timer->ptr_start_sys_timer();
            return true;
        }
    }

    timer->ptr_start_sys_timer();

    return false;
}

/**
 * @brief Settimeout by function _push
 * 
 * @param timer structure of timer
 * @param event_timer timer event
 * 
 * @retval If success, return true.Otherwise, return false.
 */
_Bool timer_settimeevent(struct _timer *timer, struct _event_timer *event_timer)
{
    return _push(timer, event_timer);
}

/**
 * @brief event processing
 * 
 * @param timer structure of timer
 */
void process_event_timer(struct _timer* timer)
{
    for (int idx = 1; idx < MAXIMUM_EVENT_NUMBER_TIMER; idx++) {
        if (timer->event_timer[idx].ms_timeout > 0) {
            timer->event_timer[idx].ms_timeout--;
            if (timer->event_timer[idx].ms_timeout == 0) {
                timer->ptr_event_timer(timer->event_timer[idx].event);
            }
        }
    }

    _dec_delay_timer(timer);

    _inc_tick_timer(timer);
}

/**
 * @brief delay time
 * 
 * @param timer structure of timer
 * @param ms delay time
 */
void timer_delay(struct _timer *timer, int ms)
{
    timer->delay_count = ms;
    while (timer->delay_count != 0);
}