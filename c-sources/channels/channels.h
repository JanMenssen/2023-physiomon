//
//  channels.h
//
//      header file for the channels class in the fysiomon project
//
//  modifications
//    08-jan-2024   JM  initial version

#ifndef CHANNELS_H
#define CHANNELS_H

class channels{

  public:
    channels(int n);
    void configure();
    void getSampleRate();
    void readData();
    void writeData();
};

#endif
