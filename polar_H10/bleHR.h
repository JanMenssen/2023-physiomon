//
// bleHR
//
//    class to implement the heart rate
//
//  modifications
//
//    30-dec-2019  JM   initial version

#include <ArduinoBLE.h>

class bleHR {

  private:
    BLEDevice peripheral;
    BLECharacteristic hrDev;
    bool strtStop;
      
  public:
    bleHR();
    bool init(BLEDevice peripheral);
    bool strt();
    bool stop();
    bool isUpdated(int *n, int *data);
    bool isStarted();
};
