//
// irqTimer.h
//
//    header file for the <irqTimer class, timer for interrupts. Currently the following 
//    Arduino types are supported
//
//      - Arduino Uno R4 Wifi
//      - Arduino Uno R3
//
//  modifications
//      18-jan-2024   JM  initial version

#ifndef _IRQTIMER_H
#define _IRQTIMER_H

#include "Arduino.h"

typedef void (*isrFunction)();

class irqTimer {
  
  public:
    irqTimer();
    bool init(long int us,isrFunction callback);
    bool start();
    bool stop();
    void setEnableIRQ(boolean enable);
    void attachInterrupt(isrFunction callback);
    void detachInterrupt();

  private:
    long int m_microseconds = 0;
    isrFunction m_callback = NULL;
};

#endif
