//
// channels.cpp
//
//      implementation of the channels class in the fysiomon project. A channel contains information
//      and databuffers. Data from the device is copied to the channels class and the display and 
//      storage engine uses this data
//
//  modifications
//    08-jan-2024   JM  initial version

#include <QDebug.h>

#include "channels.h"

// constructor

channels::channels(int n) {
  
  qDebug() << "--> in channels";
}

// configure
//
//    getting the info from the <settings> and <device> class, this method configures the 
//    buffers in the <channels> class

void channels::configure() {
}

// getSampleRate
//
//    returns the sample getSampleRate

void channels::getSampleRate() {
}

// readData
//
//    reads the data from a channel. This can be storage or display data

void channels::readData() {
}

// writeData
//
//    writes data to the channel buffers. Channel number is input

void channels::writeData() {
}
