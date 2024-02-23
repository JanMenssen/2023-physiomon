//
// sweepChart.h
//
//    class that updates the screen like a oscilloscope in sweep mode. If on the end of ths screen, the 
//    scteen is cleared and the next pixel is on the levt 
//
//  modifications
//    26-jan-2024   JM    initial version
//    23-feb-2024   JM    now based on <graphchart> due to introduction numeric displat

#ifndef _SWEEPCHART_H
#define _SWEEPCHART_H

#include "graphchart.h"

class sweepChart: public graphChart {

  public :

    sweepChart(int nchan, int *chanlist);
    ~sweepChart(); 
    bool initUpdate();
    void update(int ichan, int nsamples, float *data);
};

#endif