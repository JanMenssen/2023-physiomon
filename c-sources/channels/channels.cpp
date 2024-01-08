//
// channels.cpp
//
//      implementation of the channels class in the fysiomon project. A channel contains information
//      and databuffers. Data from the device is copied to the channels class and the display and 
//      storage engine uses this data
//
//  modifications
//    08-jan-2024   JM  initial version

#include <stdio.h>
#include "channels.h"

// constructor

channels::channels() {
  printf("\n in channels constructor");
}