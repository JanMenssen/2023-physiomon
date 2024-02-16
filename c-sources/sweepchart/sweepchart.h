//
// sweepChart.h
//
//    class that updates the screen like a oscilloscope in sweep mode. If on the end of ths screen, the 
//    scteen is cleared and the next pixel is on the levt 
//
//  modifications
//    26-jan-2025   JM    initial version

#ifndef _SWEEPCHART_H
#define _SWEEPCHART_H

#include "basechart.h"

class sweepChart: public baseChart {

  public :

    sweepChart(int nchan, int *chanlist);
    ~sweepChart(); 
    bool initUpdate();
    void update(int ichan, int nsamples, float *data);
};

#endif