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

#include "basechart.h"

class scopeChart: public baseChart {

  public :

    scopeChart(int nchan);
    ~scopeChart();
    void setTimeAxis(float nsec);
    void setYaxis(float ymin, float ymax);
    void update(int nchan, int nsamples, float *data);
    void finishUpdate();

  private :
  
    bool m_first[MAX_CHANNELS_IN_DISPLAY] = {true, true, true};
    int m_curIndx[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};

    QLineSeries *m_scopeLine = NULL;
    int m_yLimits[2] = {0,0};

};

#endif