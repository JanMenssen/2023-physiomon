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

// to speed up the updating of the graph, some defines are set. These are
//    - the maxumum number of channels for each display is set
//    - downsampling is performed so the max number of sample points to update the graph
//      is limited
//    - a downsample class is created iwht a buffer of a number of samples

#define MAX_CHANNELS_IN_DISPLAY 3
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

class baseChart {

  public :
  
    baseChart(int chan, int *chanlist);
    ~baseChart();

    void getYaxis(float *ymin, float *ymax);

    QValueAxis *getYaxisRef();
    QValueAxis *getXaxisRef();
    QChart *getChart();

    virtual void setYaxis(float ymin, float ymax);
    void setTimeAxis(float nsec);
    void initPlot(physiomon_channels *channels);
    virtual void update(int ichan, int nsamples, float* data) {};
    virtual bool initUpdate();
    virtual void finishUpdate();

    // some members are set to public, so they can be easy accessed by th child classes

    int m_channels[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
    int m_numchan = 0;

    // these variables are about updating the screen

    int m_indx[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
    int m_pntsInGraph[MAX_CHANNELS_IN_DISPLAY] = {MAX_POINTS_IN_GRAPH, MAX_POINTS_IN_GRAPH ,MAX_POINTS_IN_GRAPH};
    float m_deltaT[MAX_CHANNELS_IN_DISPLAY] = {0.0,0.0,0.0};
    bool m_firstScreen = true;
    
    QChart *m_chart = NULL;   
    QVector<QLineSeries *> m_series;
    QVector<QPointF> m_dataBuffer[MAX_CHANNELS_IN_DISPLAY];
    downSampler m_downSampler[MAX_CHANNELS_IN_DISPLAY];
    
  
  private :
 
    QValueAxis *m_axisX = NULL;
    QValueAxis *m_axisY = NULL;
    
};

#endif