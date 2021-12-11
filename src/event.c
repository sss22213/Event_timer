#include "event.h"

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