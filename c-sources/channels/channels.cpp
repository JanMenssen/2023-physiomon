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

void cyclicBuffer::read(int *n,float *data) {

  int ntal = 0;
  
  while (m_indxRead != m_indxWrite) {
    data[ntal++] = m_data[m_indxRead++];
    if (m_indxRead >= m_len) m_indxRead = 0;
  }

  *n = ntal;
  return;
}

// cyclicBuffer write method

void cyclicBuffer::write(int n, float *data) {

  for (int i=0;i<n;i++) {
    m_data[m_indxWrite++] = data[i];
    if (m_indxWrite >= m_len) m_indxWrite = 0;
  }
  
  return;
}

// channels constructor
//
//    the length of the buffers in seconds is set

channels::channels(float length) {
  
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

          float sampleRate = device->m_analogIn[ianalog].sampleRate;
          int buflen = int(m_lengthInSeconds * sampleRate);

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

// readDisplay
//
//    reads the data for the display from a channel

void channels::readDisplay(int ichan, int *nSamples, float *data) {

  m_buffers[ichan].display->read(nSamples, data);
}

// readStore
//
//    reads the data for the storage from a channel

void channels::readStore(int ichan, int *nSamples, float *data) {

  m_buffers[ichan].store->read(nSamples, data);
}

// channels writeData
//
//    writes data to the display and store buffers. Channel number is input

void channels::writeData(int ichan, float data) {

  m_buffers[ichan].display->write(1,&data);
  m_buffers[ichan].store->write(1,&data);

}
