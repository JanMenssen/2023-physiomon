// bleECG
//
//    interface of the class to obtain ECG from tha Polar H10
//
//  modifications
//
//    03-jul-2022  JM   initial version

#include <ArduinoBLE.h>

class bleECG {

  private:
    BLEDevice peripheral;
    BLECharacteristic pmdControlPoint;
    BLECharacteristic pmdData;
    bool strtStop;

  public:
    bleECG();
    bool init(BLEDevice peripheral);
    bool strt();
    bool stop();
    bool isUpdated(int *n, int *data);  
    bool isStarted();
};