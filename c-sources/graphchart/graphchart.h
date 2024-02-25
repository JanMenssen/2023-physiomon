//
// graphChart.h
//
//    abstract class for the graphic displays. Do not use this class but use the inherited classes instead
// 
//        - scopeChart   : updating like an oscilloscope
//        - stripChart   : updating like a paper stripschart recorder
//        - sweepChart   : sweep updating mode
//
//  modifications
//    26-jan-2024   JM    initial version
//    23-feb-2024   JM    renamed to graphchart due to introductionn numeric display

#ifndef _GRAPHCHART_H
#define _GRAPHCHART_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
#include <QPointF>

#include "physiomon_channels.h"
#include "basechart.h"

// to speed up the updating of the graph, some defines are set. These are
//    - downsampling is performed so the max number of sample points to update the graph
//      is limited
//    - a downsample class is created iwht a buffer of a number of samples


#define MAX_POINTS_IN_GRAPH 2500
#define SIZE_DOWNSAMPLE_BUFFER 2500

// downsampling class 

class downSampler {

  public :
    downSampler();
    ~downSampler();
    void setRate(int decimateFactor);
    void getData(int *n, float *data);
    void getMaxData(int *n, float *data);
    void getMeanData(int *n, float *data);

  private :
    int m_decimateFactor = 0;
    int m_posInBuffer = 0;
    float m_buffer[SIZE_DOWNSAMPLE_BUFFER]; 

};

class graphChart : public baseChart {

  public :
  
    graphChart(int chan, int *chanlist);
    ~graphChart();

    void getYaxis(float *ymin, float *ymax);

    QValueAxis *getYaxisRef();
    QValueAxis *getXaxisRef();
  
    virtual void setYaxis(float ymin, float ymax);
    void setTimeAxis(float nsec);
    void initPlot(physiomon_channels *channels);
    void setLabels(physiomon_settings *settings);
    virtual void update(int ichan, int nsamples, float* data) {};
    virtual bool initUpdate();
    virtual void finishUpdate();
    void MouseMoveEvent(QMouseEvent *event);
    

    // these variables are about updating the screen

    int m_indx[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
    int m_pntsInGraph[MAX_CHANNELS_IN_DISPLAY] = {MAX_POINTS_IN_GRAPH, MAX_POINTS_IN_GRAPH ,MAX_POINTS_IN_GRAPH};
    float m_deltaT[MAX_CHANNELS_IN_DISPLAY] = {0.0,0.0,0.0};
    bool m_firstScreen = true;
    
    QVector<QLineSeries *> m_series;
    QVector<QPointF> m_dataBuffer[MAX_CHANNELS_IN_DISPLAY];
    downSampler m_downSampler[MAX_CHANNELS_IN_DISPLAY];
    
  
  private :
 
    QValueAxis *m_axisX = NULL;
    QValueAxis *m_axisY = NULL;
    
};

#endif