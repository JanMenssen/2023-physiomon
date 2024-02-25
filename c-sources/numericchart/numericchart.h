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

#include <QRectF>

class numericChart : public baseChart {

  public :
  
    numericChart(int chan, int *chanlist);
    ~numericChart();

    //-jm QChart *getChart();

    // these two methods are stubs, they are not needed in the numerical display
    
    void setYaxis(float ymin, float ymax){};
    void setTimeAxis(float nsec){};
    
    void initPlot(physiomon_channels *channels);
    void update(int ichan, int nsamples, float* data);
    virtual bool initUpdate();
    virtual void finishUpdate();

    // these variables are about updating the screen

    private :

      QRectF m_numArea[MAX_CHANNELS_IN_DISPLAY];
      QPointF m_posLabel[MAX_CHANNELS_IN_DISPLAY];
      QPointF m_posValue[MAX_CHANNELS_IN_DISPLAY];

      QFont m_fontLabels = QFont();
      QFont m_fontValues = QFont();

      float m_Value[MAX_CHANNELS_IN_DISPLAY];
      
      QGraphicsSimpleTextItem **m_text = nullptr;
      QGraphicsSimpleTextItem **m_labels = nullptr;

};

#endif