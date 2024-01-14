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

// cyclicBuffer constructor
//
//    allocates memory for the data and set all indices to 0

cyclicBuffer::cyclicBuffer(int n) {

  m_len = n;
  m_indxWrite = 0;
  m_indxRead = 0;

  m_data = new float[m_len];

}

// cyclicBuffer destructor
//
//    frees up the memory

cyclicBuffer::~cyclicBuffer() {

  if (m_data != NULL) delete m_data;

}

// cyclicBuffer read method

void cyclicBuffer::read(int *n, float *data) {
  
  return;
}

// cyclicBuffer write method

void cyclicBuffer::write(int n, float *data) {

  return;
}

// channels constructor
//
//    the length of the buffers in seconds is set

channels::channels(float length) {
  
  qDebug() << "--> in channels";

  m_lengthInSeconds = length;
}

// channels configure
//
//    getting the info from the <settings> and <device> class, this method configures the 
//    buffers in the <channels> class

void channels::configure(settings *settings, measureDevice *device) {

  // for every channel

  int numchan = settings->m_numchan;
  m_buffers = new bufferStruct[numchan];
  for (int ichan = 0; ichan < numchan; ichan++) {

    int source = settings->m_channels[ichan].source;

    // analog channel

    if (settings->m_channels[ichan].type == TYPE_ANALOG_IN ) {

      int numanalog = device->m_nrAnalogIn;
      for (int ianalog = 0; ianalog< numanalog; ianalog++) {
        
        // source found, create buffers

        if (source == ianalog) {

          int sampleRate = device->m_analogIn[ianalog].sampleRate;
          int buflen = int(m_lengthInSeconds / sampleRate);

          m_buffers[ichan].sampleRate = sampleRate;
          m_buffers[ichan].display = new cyclicBuffer(buflen);
          m_buffers[ichan].store = new cyclicBuffer(buflen);
        }
      }
    }

    // numeric channel (should be implemented)

  }
}  

// channels getSampleRate
//
//    returns the sample getSampleRate

void channels::getSampleRate() {
}

// channels readData
//
//    reads the data from a channel. This can be storage or display data

void channels::readData() {
}

// channels writeData
//
//    writes data to the channel buffers. Channel number is input

void channels::writeData() {
}
