// bleECG
//
//    class to implement the heart rate
//
//  modifications
//
//    03-jul-2022  JM   initial version

#include <ArduinoBLE.h>
#include "bleECG.h"

int error = 0;

void testFunction(BLEDevice central, BLECharacteristic characteristic) {
  
  byte data[15];
  
  int nrBytes = 0;
  while (!characteristic.valueUpdated());
  
  nrBytes = characteristic.readValue(data,15);  
  if (nrBytes > 4) error = data[3];
  return;
}

// constructor

bleECG::bleECG() { 
  
  strtStop = false;
}


// init
//
//    initialises the ECG

bool bleECG::init(BLEDevice peripheral) {  
  
  bool subscribed = false;
  
  // pmdControlPoint and pmdData characteristics

  pmdControlPoint = peripheral.characteristic("FB005C81-02E7-F387-1CAD-8ACD2D8DF0C8");
  pmdData = peripheral.characteristic("FB005C82-02E7-F387-1CAD-8ACD2D8DF0C8");
 
  // check the device is a ECG device

  byte data[15];
  int nrBytesRead = pmdControlPoint.readValue(data,15);
  bool ecgDevice = (data[1] && 0x01);
  
  return ecgDevice;

  
}


// strt
//
//    starts receiving ecg data

bool bleECG::strt() {
    
  // Control point works with event function, if possible this should be solved in the 
  // future  

  pmdControlPoint.setEventHandler(BLEWritten,testFunction);
  
  // subscribe to both characteristics

  pmdControlPoint.subscribe();
  pmdData.subscribe();

  // Send start cmd

  byte initCmd[2]= {0x01, 0x00};
  pmdControlPoint.writeValue(initCmd,2);

  byte strtCmd[10] = {0x02,0x00,0x00,0x01,0x82,0x00,0x01,0x01,0x0E,0x00};
  pmdControlPoint.writeValue(strtCmd,10);

  strtStop = true;  
  return true;
}


// stop
//
//    unsubscribe to characteristic and stop receiving data

bool bleECG::stop() {

  // send stop command

  byte stopCmd[2]= {0x03, 0x00};
  pmdControlPoint.writeValue(stopCmd,2);

  // and unsubscripe to both characteristics

  pmdData.unsubscribe();
  pmdControlPoint.unsubscribe();

  strtStop = false;

  return true;
}

// isStarted
//
//    checks if service is started

bool bleECG::isStarted() {

  return strtStop;
}


// updateValue
//
//    this functions updates the value if new values are received. Should be called
//    by the eventhandler

bool bleECG::isUpdated(int *n, int *data) {
  
//-jm  if (debugStatus) Serial.println("===> in bleHR::updateValue");  

  int nrBytesRead = 0;
  byte tmpData[256];
  
  bool updated = false;
  
  if (strtStop && pmdData.valueUpdated()) {

    // decode data

    nrBytesRead = pmdData.readValue(tmpData,256);
    for (int i = 10; i < nrBytesRead ; i = i + 3) {
      int iSample = (i-10)/3;
      data[iSample] = (tmpData[i+1] << 8) + tmpData[i];;
    }

    *n = (nrBytesRead - 10) /3;
    updated = (nrBytesRead == 229);       
  } 

 return updated;
  
}


