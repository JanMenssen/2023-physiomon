//
// stripChart
//
//    implementation ot fhe <stripChart> class. This class updates the screen like a paper scrip chart recorder,
//    if on the upper right part of the screen data is shifted to the left and the new data is added on the right  
//
// modifications
//    26-jan-2024  JM   initial version

#include "stripChart.h"

// constructor

stripChart::stripChart(int nchan) : baseChart(nchan) {
}

// destructor

stripChart::~stripChart() {

}
// update

void stripChart::update(int nchan, int nsamples, float *data) {
  
}
