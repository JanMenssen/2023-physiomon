//
//  channels.h
//
//      header file for the channels class in the fysiomon project
//
//  modifications
//    08-jan-2024   JM  initial version

#ifndef CHANNELS_H
#define CHANNELS_H

#include "settings.h"
#include "measuredevice.h"

#define MAX_CHANNELS 5

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

class channels{

  public:

    channels(float length);
  
    void configure(settings *settings, measureDevice *device);
    void getSampleRate();
    void readData();
    void writeData(int ichan, float data);

  private :

    bufferStruct *m_buffers = NULL;
    float m_lengthInSeconds = 0.0;

};

#endif
