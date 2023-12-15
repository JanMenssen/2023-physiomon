// devFysioDaq
//
//    simple Arduino device that samples analog ports at a given frequeny
//
//  modifications
//      15-dec-2023  JM  initial version

// include necessary classes

#include "arduino.h"
#include "hostinterface.h"

// define the instances of the classes. For the UNO Wifi Rev2, 115200 baud
// is the maximal baudrate

hostInterface   myCommander(1200);

char     command;
int      lenData;

bool startIt;

// callback functions

//-jm void setStartStop(int n, int *data);
//-jm void returnVersion(int n, int *data);

// setup
//
//    this function is called at initialisation

void setup() {

  // set LED at startup off

  pinMode(LED_BUILTIN, OUTPUT);  
  digitalWrite(LED_BUILTIN, LOW);

  // intialise the interface with the hoat

  myCommander.init();
  myCommander.setEvent('x', setStartStop);
  myCommander.setEvent('v', returnVersion);

}

int n = 0;
int data[10];

void loop() {

  // and handle a possible command

  myCommander.handleCmd();

  // done
}


// returnVersion
//
//      returns the current version of the Arduino program
 
void returnVersion(int n, int *data) {
 
  int retData[21] = {65, 114, 100, 117, 105, 110, 111, 32, 45, 32, 77, 101, 100, 76, 97, 98, 32, 118, 48, 46, 53};

  //-jm digitalWrite(LED_BUILTIN,HIGH);
  myCommander.sendCmd('V', 21, retData);
}


// setStartStop
//
//     starts or stops all devices, currently only ADC
 
void setStartStop(int n, int *data) {

  boolean startIt;

  // check program should be started

  startIt = (data[0] == 1);

  digitalWrite(LED_BUILTIN,(startIt ? HIGH : LOW));

  return;
}
