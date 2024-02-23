//
// scopeChart.h
//
//    class that updates the screen like a osciloscope. if on the upper right part of the screen 
//    the next point overrides the points on the left 
//
//  modifications
//    26-jan-2024   JM    initial version
//    23-feb-2024   JM    now derived from <graphchart> due to introduction numeric display

#ifndef _SCOPECHART_H
#define _SCOPECHART_H

#include "graphchart.h"

class scopeChart: public graphChart {

  public :

    scopeChart(int nchan, int *chanlist);
    ~scopeChart();
    void setYaxis(float ymin, float ymax);
    void update(int ichan, int nsamples, float *data);
    void finishUpdate();
    
  private :

    // needed for the vertical line red line on the screen

    float m_yLimits[2] = {0.0 , 0.0};                                      
    QLineSeries *m_scopeLine = NULL;
};

#endif