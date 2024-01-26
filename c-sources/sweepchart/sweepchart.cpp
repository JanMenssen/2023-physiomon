//
// sweepChart.cpp
//
//    implementation of the <sweepChart> class. This class updates the screen like a oscilloscope in sweep 
//    mode. If on the end of ths screen, the scteen is cleared and the next pixel is on the levt 
//
//  modifications
//    26-jan-2025   JM    initial version

#include "sweepchart.h"

// constructor

sweepChart::sweepChart(int nchan) : baseChart(nchan) {

}
// destructor

sweepChart::~sweepChart() {
  
}
// update

void sweepChart::update(int nchan, int nsamples, float *data) {
  
}
