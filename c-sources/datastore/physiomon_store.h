//
// phsyiomon_store.h
//
//    header file for the data storage engine of the project
//
// modifications
//    15-mar-2024  JM initial version

#ifndef _PHYSIOMON_STORE_H
#define _PHYSIOMON_STORE_H

#include <QString>

#include "physiomon.h"
#include "physiomon_settings.h"
#include "physiomon_channels.h"

// structure needed for the diffent storage engines

struct groupInfoStruct {
  QString name;
  int sampleRate;
  int nchan = 0;
  int chanlist[MAX_CHANNELS];
}; 

class physiomon_store {

  public :
  
    physiomon_store(QString filename);
    ~physiomon_store();
    void configure(physiomon_settings *settings, physiomon_channels *channels);
    void write(int groupnr);  
    void writeEvent(QString eventStr);
    bool isStorageOn();
    void setStorage(bool onoff);

  private :

    groupInfoStruct m_groupInfo[MAX_STORES];
    void prepareWrite(int groupnr, int channr, float *data);
};

#endif
