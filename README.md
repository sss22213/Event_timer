# Event timer

## Description:
  Event timer engine by system clock

## Test environment:
  - Ubuntu 20.04 x86_64.
  - STM32 Cortex M (NOT TEST).
  - Anything system with system tick.

## Test:
  - Description:
    Test environment on Ubuntu 20.04 x86_64.
    
  ```Clike=
  make
  ```

  ```Clike=
  ./main
  ```

## Dependance:
  - C compile
  
## API:
  * Create new timer
  ```Clike=
  // NEW_TIMER(timer name, init_sys_timer_func, start_sys_timer_func, stop_sys_timer_func, process_event);
  NEW_TIMER(timer1, init_sys_timer_func, start_sys_timer_func, stop_sys_timer_func, process_event);
  ```
  
  * Initial timer
  ```Clike=
  // void timer_init(struct _timer *timer)
  timer_init(&timer1);
  ```
  
  * New timer event
  ```Clike=
  // Trigger time unit system tick.
  NEW_EVENT_TIMER(timer_event_name, EVENT_TEST, trigger_time);
  ```
    
  * Add time event to event queue.
  ```Clike=
  // _Bool timer_settimeevent(struct _timer*, struct _event_timer*);
  timer_settimeevent(&timer1, &timer_event_1);
  ```
  
  * Delay (unit: system tick)
  ```Clike=
  void timer_delay(struct _timer*, int);
  ```
  

---

## Porting:
  1. Add system tick
  
  * System create timer by macro NEW_TIMER.
  ```Clike=
  NEW_TIMER(timer_name, init_sys_timer_func, start_sys_timer_func, stop_sys_timer_func, process_event);
  ```
  
  * Please implement system tick initial on function init_sys_timer_func.
  ```Clike=
  void init_sys_timer_func(void);
  ```
  
  * Please implement timer start on function start_sys_timer_func.
  ```Clike=
  void start_sys_timer_func(void);
  ```
  
  * Please implement timer stop on function stop_sys_timer_func.
  ```Clike=
  void stop_sys_timer_func(void)
  ```
  2. Add own custom to event
  
  * Every line represent single event.
  ```Clike=
  // On event.h
  typedef enum {
    EVENT_HEAD,
    EVENT_TEST,
    EVENT_TEST1,
    EVENT_TEST2
  } TIMER_EVENT;
  ```
  
  * Every case represent single event processing.
  ```Clike=
  // On event.c
  void process_event(TIMER_EVENT timer_event)
  {
      switch (timer_event) {
      case EVENT_TEST:
          // When event EVENT_TEST is triggered, excute event_func1.
          event_func1();
          break;

      case EVENT_TEST1:
          // When event EVENT_TEST1 is triggered, excute event_func1.
          event_func2();
          break;

      case EVENT_TEST2:
          // When event EVENT_TEST2 is triggered, excute event_func3.
          event_func3();
          break;

      default:
          break;
      }
  }
  ```
 

 



