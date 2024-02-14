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
    void setYaxis(float ymin, float ymax);
    void update(int ichan, int nsamples, float *data);
    void finishUpdate();
    
  private :
  
    void addExtraPoints(float time);

    bool m_firstScreen = true;
    int m_curIndx[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
    float m_yLimits[2] = {0.0 , 0.0};                                      

    QLineSeries *m_scopeLine = NULL;
};

#endif