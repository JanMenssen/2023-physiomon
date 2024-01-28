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

    sweepChart(int nchan);
    ~sweepChart(); 
    void setTimeAxis(float nsec);
    void update(int nchan, int nsamples, float *data);

  private :
  
    int m_curIndx[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
};

#endif