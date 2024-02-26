//
// numericChart.h
//
//    shows measured data in numerics on the screen
//
//  modifications
//    23-feb-2024   JM    initial version

#ifndef _NUMERICCHART_H
#define _NUMERICCHART_H

#include "basechart.h"
#include "physiomon_channels.h"
#include "physiomon_settings.h"

#include <QRectF>
#include <QChart>

#define MAX_CHANNELS_IN_DISPLAY 3

class numericChart : public baseChart {

  public :
  
    numericChart(int chan, int *chanlist);
    ~numericChart();

    //-jm QChart *getChart();

    // these two methods are stubs, they are not needed in the numerical display
    
    void setYaxis(float ymin, float ymax){};
    void setTimeAxis(float nsec){};
    
    void initPlot(physiomon_channels *channels);
    void setLabels(physiomon_settings *settings);
    void update(int ichan, int nsamples, float* data);
  
    virtual bool initUpdate();
    virtual void finishUpdate();

    // these variables are about updating the screen

    private :

      int m_numchan;
      int m_channels[MAX_CHANNELS_IN_DISPLAY];

      QRectF m_numArea[MAX_CHANNELS_IN_DISPLAY];
      QPointF m_posLabel[MAX_CHANNELS_IN_DISPLAY];
      QPointF m_posValue[MAX_CHANNELS_IN_DISPLAY];

      QFont m_fontLabels = QFont();
      QFont m_fontValues = QFont();
      QStringList m_labelTxt;

      float m_Value[MAX_CHANNELS_IN_DISPLAY];
      
      QGraphicsSimpleTextItem **m_text = nullptr;
      QGraphicsSimpleTextItem **m_labels = nullptr;

};

#endif