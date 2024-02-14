//
// bleConnect
//
//    interfacr for the bleComnect class. This class search for a ble device by its name
//    and connects it
//
//  modfications
//    15-jul-2022   JM    initial value

#ifndef BLECONNECT_H
#define BLECONNECT_H

#include <ArduinoBLE.h>

class bleConnect {

  public :
    bleConnect();
    bool searchAndConnect(String devName, int timeOut);
    bool isDeviceConnected(BLEDevice *peripheral);
    void disconnect();

  private :  
    bool connected;
    BLEDevice peripheral;    
};

#endif