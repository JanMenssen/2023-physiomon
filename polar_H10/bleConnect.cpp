//
// bleConnect
//
//    implemeentation of the bleConnect class. This class search a BLE device by it's name
//    and tries to connect with it
//
// modifications
//    15-jul-2022   JM    initial version

#include "bleConnect.h"

// constructor

bleConnect::bleConnect() {
  
  connected = false;
}


// seachAndConnect
//
//    this routine search a BLE device by it's name and if found connects with
//    it

bool bleConnect::searchAndConnect(String devName, int timeOut) {
  
  BLE.begin();
  BLE.scanForName(devName);

  unsigned long startTime = millis();
  while ((millis()-startTime < timeOut) && !peripheral) {
    peripheral = BLE.available();
  } 
  
  BLE.stopScan();
  if (peripheral){
    connected = peripheral.connect();
    connected = peripheral.discoverAttributes(); 
  }

  return connected;  
}


// isDeviceConnected
//
//    returns true if the device is connected. If connected the periperhal is in the
//    arghument list

bool bleConnect::isDeviceConnected(BLEDevice *connectedPeripheral) {

  *connectedPeripheral = peripheral;
  if (connected) connected = peripheral.connected();
  return connected;
}


// disconnect
//
// disconnect the device 

void bleConnect::disconnect() {
  
  peripheral.disconnect();
  connected = false;

  return;
}