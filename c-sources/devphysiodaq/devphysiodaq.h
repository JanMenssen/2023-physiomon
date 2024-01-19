//
// devPhysioDaq
//
//    header file for hte <devPhysioDaq> device, an arduino than samples analog ports arduino
//    transfer the raw data to the host using the seriol ports

#ifndef _devPhysioDaq_H
#define _devPhysioDaq_H

#include <QString>
#include "arduinocomm.h"
#include "measuredevice.h"
#include "channels.h"

class devPhysioDaq : public measureDevice {

  public :

    devPhysioDaq();
    ~devPhysioDaq();

    void initialise();
    QString isConnected();
    void setSampleRate(int ms);
    bool isStarted();
    void setStartStop(bool start);
    void iniRead(QString deviceName);
    void read(channels *channels); 

  private :

    QString m_address = "";
    arduinoComm m_arduino;
   
    void writeValueToAllChannels(analogInStruct *analogIn,channels *channels,int value);
};

#endif