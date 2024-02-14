// bleHR
//
//    class to implement the heart rate
//
//  modifications
//
//    30-dec-2019  JM   initial version

#include <ArduinoBLE.h>
#include "bleHR.h"

// constructor

bleHR::bleHR() { 

  strtStop = false;
}


// subscribe
//
//    subscribe to the heart rate

bool bleHR::init(BLEDevice peripheral) {  
  
  bool hrDevSet = false;
  
  hrDev = peripheral.characteristic("2a37");
  if (hrDev) hrDevSet = true;
  return hrDevSet;
}


// strt
//
//    subscibes to the characteristic and receive values

bool bleHR::strt() {

  bool subscribed = (hrDev.subscribe() && (hrDev.properties() & BLENotify));
  
  strtStop = subscribed;
  return subscribed;

}
// stop
//
//    unsubscribe and stop with receiving values

bool bleHR::stop() {
                
  strtStop = false;
  return hrDev.unsubscribe();
}

// isStarted
//
//    returns if device is started

bool bleHR::isStarted() {

  return strtStop;
}


// updateValue
//
//    this functions updates the value if new values are received. Should be called
//    by the eventhandler

bool bleHR::isUpdated(int *n, int *data) {
  
  int nrBytesRead = 0;
  bool updated = false;
  
  if (strtStop && hrDev.valueUpdated()) {
  
    byte tmpData[4];
    nrBytesRead = hrDev.readValue(tmpData,4);
  
    // depending on bit 0, data should be handled
    
    if (bitRead(tmpData[0],0) == 0) {
      data[0] = (int)(tmpData[1]);
    } else {
      data[0] = (int)(256*tmpData[1])+tmpData[2];
    }

    *n = 1;
    updated = true;       
  } 
    
  return updated;
}
