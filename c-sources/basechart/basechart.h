//
// baseChart.h
//
//    abstract class for the graphic displays. Do not use this class but use the inherited classes instead
// 
//        - scopeChart   : updating like an oscilloscope
//        - stripChart   : updating like a paper stripschart recorder
//        - sweepChart   : sweep updating mode
//
//  modifications
//    26-jan-2025   JM    initial version

#ifndef _BASECHART_H
#define _BASECHART_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
#include <QPointF>

#include "physiomon_channels.h"

// maximum of 3 channels in one display

#define MAX_CHANNELS_IN_DISPLAY 3

class baseChart {

  public :
  
    baseChart(int n, int *chanlist);
    ~baseChart();

    virtual void setYaxis(float ymin, float ymax) = 0;
    virtual void setTimeAxis(float nsec) = 0;
    virtual void initPlot(physiomon_channels *channels) = 0;
    virtual void update(int ichan, int nsamples, float* data) = 0;
    virtual bool initUpdate() = 0;
    virtual void finishUpdate() = 0;
    virtual QChart *getChart() = 0;

    // some members are set to public, so they can be easy accessed by th child classes

    int m_channels[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
    int m_numchan = 0;
};

#endif