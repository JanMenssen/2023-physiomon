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

#include <QScatterSeries>

class numericChart : public baseChart {

  public :
  
    numericChart(int chan, int *chanlist);
    ~numericChart();

    // these two methods are stubs, they are not needed in the numerical display
    
    void setYaxis(float ymin, float ymax){};
    void setTimeAxis(float nsec){};
    void setPrecision(channelStruct *channelInfo);

  
    void initPlot(physiomon_channels *channels);
    void setLabels(channelStruct *channelInfo);
    void updatePlot(int ichan, int nsamples, float* data);
  
    virtual bool initUpdatePlot();
    virtual void finishUpdatePlot();

    // these variables are about updating the screen

    private :

      void calcValuePositions();
      void calcLabelPositions();
      void plotLabel(int n,QString labelTxt);
      void plotValue(int n,float value);
      float calcScaleFactor();
    
      QValueAxis *m_axisX = NULL;
      QValueAxis *m_axisY = NULL;
      
      QScatterSeries *m_series = nullptr;
      
      // positions in the graph to place the text

      QPointF m_valuePos[MAX_CHANNELS_IN_DISPLAY];   
      QPointF m_labelPos[MAX_CHANNELS_IN_DISPLAY];

      //-jm QFont m_fontLabels = QFont();
      //-jm QFont m_fontValues = QFont();
      
      QStringList m_labelTxt;

      float m_average[MAX_CHANNELS_IN_DISPLAY];
      int m_precision[MAX_CHANNELS_IN_DISPLAY];
      
      QFont m_usedFont;
      float m_scaleFactor;                       // factor the value are larger compared to the labels
      
      QGraphicsSimpleTextItem **m_value = nullptr;
      QGraphicsSimpleTextItem **m_label = nullptr;

};

#endif