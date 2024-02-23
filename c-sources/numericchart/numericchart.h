//
// numericChart.h
//
//    shows measured data in numerics on the screen
//
//  modifications
//    23-feb-2024   JM    initial version

#ifndef _NUMERICCHART_H
#define _NUMERICCHART_H

#include "physiomon_channels.h"
#include "basechart.h"

class numericChart : public baseChart {

  public :
  
    numericChart(int chan, int *chanlist);
    ~numericChart();

    QChart *getChart();

    // these two methods are stubs, they are not needed in the numerical display
    
    void setYaxis(float ymin, float ymax){};
    void setTimeAxis(float nsec){};
    
    void initPlot(physiomon_channels *channels);
    virtual void update(int ichan, int nsamples, float* data) {};
    virtual bool initUpdate();
    virtual void finishUpdate();

    // these variables are about updating the screen

    int m_indx[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};

    QChart *m_chart = NULL;   

};

#endif