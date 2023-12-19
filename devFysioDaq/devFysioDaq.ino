//
// devFysioDaq
//
//    analog input from an Arduino. Currently it supports the following commands
//
//      - x       : start/stops the device
//      - c       : configures the device (samplerate in ms is set)
//      - v       : version information is returned
//
//  Modifications
//    04-okt-2014    JM   initial version
//    29-jan-2016    JM   now makes use of callBack functions
//    06-feb-2017    JM   now returned
//    15-feb-2017    JM   Interrupts are now handled in intr1ms and callback is used
//    18-feb-2017    JM   TimerOne library is used instead of intr1ms, intr1ms obsolete

// include necessary classes

#include "Arduino.h"
#include "adc.h"
#include "hostinterface.h"
#include <TimerOne.h>

// define the instances of the classes

hostInterface   myCommander(BAUDRATE);
adc             myADC(1);

// other variables

int adc_buffer[MAX_ADC_CHANNELS];

char     command;
int      lenData;

bool startIt;
bool LEDon;

// callback functions

void setStartStop(int n, int *data);
void configure(int n, int *data);
void returnVersion(int n, int *data);

// interupt-routine (every 1 ms)

void timerISR();

// setup
//
//    this function is called at initialisation

void setup() {

  // set LED at startup off

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // intialise the interface with the hoat

  myCommander.start();
  myCommander.setEvent('x', setStartStop);
  myCommander.setEvent('c', configure);
  myCommander.setEvent('v', returnVersion);

  // and setup and enable the timer interrupt routine

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerISR);
 
}


// loop
//
//  in the loop function, the Arduino checks command from PC and send data to PC
//  in necessary

void loop() {

  // handle received command from the host (if any)

  myCommander.handleCmd();

  // if ADC started and data vailable send it to the hist

  if (myADC.isStarted()) {
    if (myADC.getData(&lenData, adc_buffer)) myCommander.sendCmd(65, lenData, adc_buffer);
  }

  // done

}


// returnVersion
//
//      returns the current version of the Arduino program

void returnVersion(int n, int *data) {
 
  int retData[23] = {65, 114, 100, 117, 105, 110, 111, 32, 45, 32, 70, 121, 115, 105, 111, 68, 97, 113, 32, 118, 48, 46, 56};

  myCommander.sendCmd('V', 23, retData);
  
  return;
}


// configure
//
//     sets the sample rate (in ms) for the ADC

void configure(int n, int *data) {

  myADC.setSampleRate(data[0]);
  return;
}


// setStartStop
//
//     starts or stops all devices, currently only ADC

void setStartStop(int n, int *data) {

  boolean startIt;

  // check ADC (bit 0) should be started

  startIt = bitRead(data[0], 0);
  digitalWrite(LED_BUILTIN, (startIt ? HIGH : LOW));
  myADC.setStartStop(startIt);

  return;
}


// and the interrupt routine

void timerISR() {
  myADC.readADC();
}

