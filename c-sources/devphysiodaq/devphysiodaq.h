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
#include "physiomon_channels.h"

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
    void read(physiomon_channels *channels); 

  private :

    QString m_address = "";
    arduinoComm *m_arduino = nullptr;
   
    void writeValueToAllChannels(analogInStruct *analogIn,physiomon_channels *channels,short value);
};

#endif