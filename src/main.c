#include "timer.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

struct _timer *ptr_timer;
struct itimerval ovalue;
struct itimerval value;

void event_func1(void)
{
    printf("func1\n");
}

void event_func2(void)
{
    printf("func2\n");
}

void event_func3(void)
{
    printf("func3\n");
}

void process_event(TIMER_EVENT timer_event)
{
    switch (timer_event) {
    case EVENT_TEST:
        event_func1();
        break;

    case EVENT_TEST1:
        event_func2();
        break;

    case EVENT_TEST2:
        event_func3();
        break;

    default:
        break;
    }
}

void systick(int sig)
{
    ptr_timer->ptr_process_event_timer(ptr_timer);
}

void init_sys_timer_func()
{
    signal(SIGALRM, systick);
}

void start_sys_timer_func()
{
    value.it_value.tv_sec = 1;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, &ovalue);
}

void stop_sys_timer_func()
{
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, &ovalue);
}


int main(int argc, char **argv)
{
    
    NEW_TIMER(timer1, init_sys_timer_func, start_sys_timer_func, stop_sys_timer_func, process_event);
    timer_init(&timer1);

    ptr_timer = &timer1;

    printf("111\n");
    timer_delay(&timer1, 5);
    printf("222\n");

    NEW_EVENT_TIMER(timer_event_1, EVENT_TEST, 5);
    NEW_EVENT_TIMER(timer_event_2, EVENT_TEST1, 2);
    NEW_EVENT_TIMER(timer_event_3, EVENT_TEST2, 2);

    timer_settimeevent(&timer1, &timer_event_1);
    timer_settimeevent(&timer1, &timer_event_2);
    timer_settimeevent(&timer1, &timer_event_3);

    while(1);
        
    return 0;
}