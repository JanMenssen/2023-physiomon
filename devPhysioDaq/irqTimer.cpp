//
//  irqTimer
//
//      implementation of the <irqTimer> class. In this class a timer interrupt is 
//      generated. It should be general and working on different Arduino types
//
//  modifications
//    18-jan-2024   JM  initial version

#include "irqTimer.h"

// here all arduino types are defined. Only one should be selected

//-jm #define ARDUINO_UNO_R4
#define ARDUINO_UNO_R3
//-jm #define ARDUINO_MEGA_2560
//-jm #define ARDUINO_EUN_R3_WIFI_R2

// =====================================================================================
//
//    implementation for the Arduino R4 Wifi
//
//    currently the implementation of Phil Schatzmann is used and adapted
//    https://www.pschatzmann.ch/home/2023/07/01/under-the-hood-arduino-uno-r4-timers/
//
//    FspTimers are used, these are standard, no library is needed
//
// ======================================================================================

#ifdef ARDUINO_UNO_R4

#include "FspTimer.h"

// every timer has a special format of setup of the interrupt callback routine, Therefore
// we choose to have in the routine an ISR and this ISR should call the ISR defined in
// the main program. 
//
//  using this solution with static function makes it possible to work with the same class
//  definitions

isrFunction to_isr_function = NULL;

void uno_r4_timer_callback(timer_callback_args_t __attribute((unused)) *p_args) {
  to_isr_function(); 
}

FspTimer uno_r4_timer;

// constructor of the class

irqTimer::irqTimer() {
}

// init
//
//     period and interrupt routine are set by this routine. On succes a True 
//     is returned, else a False


bool irqTimer::init(long int us,isrFunction callback) {

  bool retcode = true;
  
  m_microseconds = us;
  to_isr_function = callback;

  // find availabe timer

  uint8_t timer_type = GPT_TIMER;
  uint8_t t_indx = FspTimer::get_available_timer(timer_type,true);  
  retcode = (t_indx > 0);
  
  // initialize the timer found

  if (retcode) {
    float frequency = 1e6/m_microseconds;
    FspTimer::force_use_of_pwm_reserved_timer();
    retcode = uno_r4_timer.begin(TIMER_MODE_PERIODIC, timer_type, t_indx, frequency, 0.0, uno_r4_timer_callback);
  }

  if (retcode) retcode = uno_r4_timer.setup_overflow_irq();
  if (retcode) retcode = uno_r4_timer.open();

  // done, return
  
  return retcode;
}

// start
//
//    starts the timer

bool irqTimer::start() {

  bool retcode = uno_r4_timer.start();
  return retcode;

}

// setEnableIRQ
//
//      enables or disables the interrupt

void irqTimer::setEnableIRQ(bool enable) {

}

//  attachInterrupt
//
//    sets the interrupt callback routine

void irqTimer::attachInterrupt(isrFunction callback) {

  to_isr_function = callback;
}

//  detachInterrupt
//
//    clear the interrupt routine, interupt is received but nothing
//    is done

void irqTimer::detachInterrupt() {

  to_isr_function = NULL;

}

#endif

// =====================================================================================
//
//    implementation for the Arduino Uno R3
//
//    currently the <TIMERINTERRUP_GENERIC_LIBRAY is use
//    https://github.com/khoih-prog/TimerInterrupt_Generic
//
//    the library should be installed first
// ======================================================================================
 
#ifdef ARDUINO_UNO_R3

// debug level, set levels 0-4, 

#define TIMER_INTERRUPT_DEBUG         2
#define _TIMERINTERRUPT_LOGLEVEL_     0

// Select USING_16MHZ     == true for  16MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_8MHZ      == true for   8MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_250KHZ    == true for 250KHz to Timer TCBx => shorter timer, but better accuracy
//
// Not select for default 250KHz to Timer TCBx => longer timer,  but worse accuracy

#define USING_16MHZ     true
#define USING_8MHZ      false
#define USING_250KHZ    false

#define USE_TIMER_0     false
#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false

#include "TimerInterrupt_Generic.h"

// constructor

irqTimer::irqTimer() {
  
}

// initialization

bool irqTimer::init(long int us, isrFunction callback) {
  
  // end temopory commands

  m_microseconds = us;
  m_callback = callback;

  ITimer1.init();
    
  return true;
}

// enable IRQ routine depending on boolean
//
//    NOTE : the init is not necessary for MEGA and UNO

void irqTimer::setEnableIRQ(boolean enable) {

  if (enable) {
    ITimer1.resumeTimer();
  } else {
    ITimer1.pauseTimer();
  }
}

// start
//
//    starts the timer, currently not implemented

bool irqTimer::start() {
  
  float frequency = 1e6 / m_microseconds;
	bool retcode = ITimer1.attachInterrupt(frequency, m_callback, 0);
  
  return retcode;
}

// stop
//
//    stops the timer, currently not implemented

bool irqTimer::stop() {

  ITimer1.pauseTimer();
  return true;
}

// attachInterrupt
//
//    currently not implemented

void irqTimer::attachInterrupt(isrFunction callback) {

  m_callback = callback;
}


// detachInterrupt
//
//    currently not implemented()

void irqTimer::detachInterrupt() {

  m_callback = NULL;
  ITimer1.detachInterrupt();

}

 #endif