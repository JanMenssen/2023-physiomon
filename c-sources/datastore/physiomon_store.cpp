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

void physiomon_store::configure(physiomon_settings *settings) {

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

