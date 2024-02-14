//
//  physiomon_channels.h
//
//      header file for the channels class in the fysiomon project
//
//  modifications
//    08-jan-2024   JM  initial version
//    11-feb-2024   JM  renamed to <physiomon_channels

#ifndef _PHYSIOMON_CHANNELS_H
#define _PHYSIOMON_CHANNELS_H

#include "physiomon_settings.h"
#include "measuredevice.h"

// cyclic buffer stores the samples

class cyclicBuffer {

  public :

    cyclicBuffer(int n);
    ~cyclicBuffer();

    void read(int *n, float *data);
    void write(int n, float *data);

  private :

    float *m_data = NULL;
    int m_indxWrite = 0;
    int m_indxRead = 0;
    int m_len = 0;
};


struct bufferStruct {
  int sampleRate; 
  cyclicBuffer *display;
  cyclicBuffer *store;
};

class physiomon_channels{

  public:

    physiomon_channels(float length);
  
    void configure(physiomon_settings *settings, measureDevice *device);
    void readDisplay(int nchan, int *nSamples, float *data);
    void readStore(int nchan, int *nSamples, float *data);
    void writeData(int ichan, float data);
    int getSampleRate(int channel);

  private :

    bufferStruct *m_buffers = NULL;
    float m_lengthInSeconds = 0.0;

};

#endif
