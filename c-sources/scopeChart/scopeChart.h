//
// scopeChart.h
//
//    class that updates the screen like a osciloscope. if on the upper right part of the screen 
//    the next point overrides the points on the left 
//
//  modifications
//    26-jan-2025   JM    initial version

#ifndef _SCOPECHART_H
#define _SCOPECHART_H

#include "scopechart.h"

class scopeChart: public baseChart {

  public :
    scopeChart(int nchan);
    ~scopeChart();
    void update(int nchan, int nsamples, float *data);
};

#endif