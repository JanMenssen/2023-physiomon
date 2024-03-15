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

class physiomon_store {

  public :
  
    physiomon_store(QString filename);
    ~physiomon_store();
    void configure(physiomon_settings *settings);
    void write(int groupnr);  
    void writeEvent(QString eventStr);
    bool isStorageOn();
    void setStorage(bool onoff);

  private :

    void prepareWrite(int groupnr, int channr, float *data);
};

#endif
