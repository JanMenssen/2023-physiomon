//
// polar_H10
//
//    this is a test program to read the Heart Rate from a Polar H10 
//
// modifications
//   11-jan-2020  JM  initial version
//   03-jul-2022  JM  a lot of changes
//   14-feb-2024  JM  renamed from <bleArduino> to <polar_H10> and now on Arduino UNO R4

#include "Arduino.h"
#include "bleConnect.h"
#include "bleHR.h"
#include "bleECG.h"
#include <ArduinoBLE.h>

//-jm #include "hostinterface.h"
#include "keyBoardHandler.h"

bleConnect myConnectDev;
bleHR myHR;
bleECG myECG;
//-jm hostInterface myCommander(57600);
//-jm keyBoardHandler myCommander(57600);

int len = 0;
int dataBuffer[100];

// callback routines for the host Interface

//-jm void setStartStop(int n, int *data);
//-jm void connect(int n, int *data);
//-jm void returnVersion(int *, int *data);

// setup function

void setup() {

  Serial.begin(9600);


  //-jm BLEDevice usedPeripheral; 

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //-jm myCommander.init();

  //-jm myCommander.setEvent('v',returnVersion);
  //-jm myCommander.setEvent('x',setStartStop);
  //-jm myCommander.setEvent('c',connect);
}


// loop
//
//    this is the main loop of the program

void loop() {


  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
  delay(500);

  //-jm BLEDevice usedPeripheral;
  //-jm boolean connected = false;

  // check new commands from host interface
  
  Serial.println("in loop");

  //-jm myCommander.handleCmd();

  // and if connected update if new values

  //-jm if (myConnectDev.isDeviceConnected(&usedPeripheral)) {

    //-jm Serial.println("connected");

    // The labView progeam MusicDAQ expect one sample for all channels in the stream. However now we have
    // multiple samples for one channel, therefore we transmit every single sample seperate
    
    //-jm if (myECG.isUpdated(&len,dataBuffer)) {
//-jm      myCommander.sendCmd(87,len,dataBuffer);    
      //-jm for (int i=0;i<len;i++) myCommander.sendCmd(87,1,&dataBuffer[i]);
    //-jm }
    //-jm if (myHR.isUpdated(&len,dataBuffer)) myCommander.sendCmd(78,len,dataBuffer);
  //-jm }    
}


// returnVersion
//
//    this routine returns the current version of the Arduino program

//-jm void returnVersion(int n, int *data) {

//-jm  digitalWrite(LED_BUILTIN, LOW);

//-jm  int returnData[21] = {77,117,115,105,99,68,97,113,32,45,32,80,111,108,97,114,32,118,48,46,49};
//-JM  myCommander.sendCmd('V',21,returnData);

//-jm  return;
//-jm }


// setStartStop
//
//    starts and stops the BLE data transfer

/*
void setStartStop(int n, int *data) {

  boolean startIt = bitRead(data[0],0);
  
  if (startIt) {
    myHR.strt();
    myECG.strt();
  } else {
    myHR.stop();
    myECG.stop();    
  } 

  return;
}
*/

// connect
//
//    initialises and tries to connect with the BLE peripheral.
/*
void connect(int n, int *data) {

  boolean status = true;
  BLEDevice usedPeripheral;

  // read the name of the peripheral and try to connect

  char nameOfDevice[50];
 
  for (int i = 0; i<50; i++) nameOfDevice[i] = 0;
  for (int i = 0; i<n; i++) nameOfDevice[i] = lowByte(data[i]);

  // if still connected disconntect before connect again
  
  digitalWrite(LED_BUILTIN,LOW);
  
  if (myConnectDev.isDeviceConnected(&usedPeripheral)) usedPeripheral.disconnect();
  if (myHR.isStarted()) myHR.stop();
  if (myECG.isStarted()) myECG.stop();
  
  if (status) status = myConnectDev.searchAndConnect(nameOfDevice,2500);
  if (status) status = myConnectDev.isDeviceConnected(&usedPeripheral);

  if (status) status = myECG.init(usedPeripheral);
  if (status) status = myHR.init(usedPeripheral);  

  // turn led on if device is connected

  digitalWrite(LED_BUILTIN,(status ? HIGH : LOW));  
  
  // and return to host connection status

  data[0] = (status ? 1 : 0);
  myCommander.sendCmd('C',1,data);
  
  return;
}
*/