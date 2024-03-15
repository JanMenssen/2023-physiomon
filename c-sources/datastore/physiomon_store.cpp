//
// physiomon_store.cpp
//
//      implementation of the storage engine in the physiomon project. This engine is responsible 
//      for the storage to disk of the signals
//
//  modifications
//      15-mar-2024  JM   initial version

#include "physiomon_store.h"

// constructor

physiomon_store::physiomon_store(QString filename) {

}

// destructor

physiomon_store::~physiomon_store() {

}

// configure
//
//    using the information in the setting structure, this method configures the datastores

void physiomon_store::configure(physiomon_settings *settings, physiomon_channels *channels) {

  // first get the groupnames from the settings struct

  int numstore = settings->m_numstore;
  for (int i=0;i<numstore;i++) m_groupInfo[i].name = settings->m_stores[i].groupname;

  // next create a channel list for all stores

  int numchannels = settings->m_numchan;
  for (int i=0;i<numchannels;i++) {
    int usedStore = settings->m_channels[i].store;
    if (usedStore > 0) m_groupInfo[usedStore-1].chanlist[m_groupInfo[usedStore-1].nchan++] = i;
  }

  // and get the sample rate for all stores. Currently this is done by getting the sample rate 
  // for the first channel in the list, assuming the channels in the list have the same sample 
  // rate (this is needed for one store)

  for (int i=0;i<numstore;i++) {
    int firstchan = m_groupInfo[i].chanlist[0];
    m_groupInfo[i].sampleRate = channels->getSampleRate(firstchan);
  }

  // done 
}
  
// prepare4write

void physiomon_store::prepareWrite(int groupnr, int channr, float *data) {

}

// write

void physiomon_store::write(int groupnr) {

}

// writeEvent

void physiomon_store::writeEvent(QString event) {

}
  
// isStorageOn

bool physiomon_store::isStorageOn() {

  return true;
}

// setStorage

void physiomon_store::setStorage(bool onoff) {

}

