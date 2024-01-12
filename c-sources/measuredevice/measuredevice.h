//
// measuredevice.h
//
//      header file abstract class for the device handler. This class should be inherited
//      by the device
//
// modificatons
//    12-jan-2024   JM    initial version

#ifndef _MEASUREDEVICE_H
#define _MEASUREDEVICE_H

class measuredevice {

  public :

    measuredevice();
    ~measuredevice();

    void initialise();
    bool isStarted();
    void setStartStop();
    void iniRead();
    void configure();

};

#endif
