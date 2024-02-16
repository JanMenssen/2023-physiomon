//
// phsyiomon_channels.cpp
//
//      implementation of the channels class in the fysiomon project. A channel contains information
//      and databuffers. Data from the device is copied to the channels class and the display and 
//      storage engine uses this data
//
//  modifications
//    08-jan-2024   JM  initial version
//    11-feb-2024   JM  renamed to <physiomon_channels>
//    16-feb-2024   JM  faster cyclic buffer (memcpy instead of for loop)

#include <QDebug.h>
#include "physiomon_channels.h"

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

  *n = 0;

  if (m_indxWrite > m_indxRead) {
    memcpy(data,&m_data[m_indxRead],(m_indxWrite-m_indxRead) * sizeof(float));
    *n = (m_indxWrite - m_indxRead);
  }
 
  if (m_indxWrite < m_indxRead) { 
    int split = m_len - m_indxRead;
    memcpy(data,&m_data[m_indxRead], split * sizeof(float));
    memcpy(&data[split],m_data,m_indxWrite * sizeof(float));
    *n = m_indxWrite - m_indxRead + m_len;
  }  

  m_indxRead = m_indxWrite;
 
  //-jm  int ntal = 0;
  //-jm while (m_indxRead != m_indxWrite) {
  //-jm   data[ntal++] = m_data[m_indxRead++];
  //-jm  if (m_indxRead >= m_len) m_indxRead = 0;
  //-jm }
  //-jm 
  //-jm *n = ntal;

  return;
}

// cyclicBuffer write method

void cyclicBuffer::write(int n, float *data) {

  if ((m_indxWrite + n) <= m_len) {

    memcpy(&m_data[m_indxWrite],data,n * sizeof(float));
    m_indxWrite += n;
  
  } else {

    int split = m_len - m_indxWrite;
    memcpy(&m_data[m_indxWrite],data, split + sizeof(float));
    memcpy(m_data,&data[split], (n-split) * sizeof(float));
    m_indxWrite = n - split;
  
  }

  //-jm for (int i=0;i<n;i++) {
  //-jm   m_data[m_indxWrite++] = data[i];
  //-jm   if (m_indxWrite >= m_len) m_indxWrite = 0;
  //-jm }
  
  return;
}

// channels constructor
//
//    the length of the buffers in seconds is set

physiomon_channels::physiomon_channels(float length) {
  
  m_lengthInSeconds = length;
}

// channels configure
//
//    getting the info from the <settings> and <device> class, this method configures the 
//    buffers in the <channels> class

void physiomon_channels::configure(physiomon_settings *settings, measureDevice *device) {

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

// readDisplay
//
//    reads the data for the display from a channel

void physiomon_channels::readDisplay(int ichan, int *nSamples, float *data) {

  m_buffers[ichan].display->read(nSamples, data);  
}

// readStore
//
//    reads the data for the storage from a channel

void physiomon_channels::readStore(int ichan, int *nSamples, float *data) {

  m_buffers[ichan].store->read(nSamples, data);
}

// channels writeData
//
//    writes data to the display and store buffers. Channel number is input

void physiomon_channels::writeData(int ichan, float data) {

  m_buffers[ichan].display->write(1,&data);
  //-jm m_buffers[ichan].store->write(1,&data);

}

// channels getSampleRate
//
//    returns the sampleRate for the desired channel

int physiomon_channels::getSampleRate(int channel) {

  return m_buffers[channel].sampleRate;
}
