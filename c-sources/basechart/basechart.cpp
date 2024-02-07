//
// baseChart.cpp
//
//      this is the implementation of the abstract class <baseChart>
//
//  modifications
//    26-jan-2024   JM  initial version

#include "basechart.h"
#include <string.h>

#include <QDebug>

// downSampler constructor

downSampler::downSampler() {

}

// downSapler setRate

void downSampler::setRate(int rate) {
  
  m_decimateFactor = rate;
}

// downSampler destructor

downSampler::~downSampler() {

}

// downSampler getMeanata
//
//    method decimates the data. Date is overwritten by the new downsamples 
//    data. If m_rate < 1, no downsampling is needed, the number of samples in the
//    graph is below the MAX_POINTS_IN_GRAPH

void downSampler::getMeanData(int *n, float *data) {

  float sum = 0.0;
  if ( m_decimateFactor > 1) {
  
    // copy the input data to the end of the buffer

    memcpy(&m_buffer[m_posInBuffer],data,*n * sizeof(float));
    m_posInBuffer += *n;

    // until the number of samples in the buffer is too small  (< m_rate)

    *n = 0;
    while(m_posInBuffer >= m_decimateFactor) {
      
      sum = 0.0;
      for(int i=0;i<m_decimateFactor;i++) sum += m_buffer[i];
      data[*n] = sum / m_decimateFactor;
      
      memmove(&m_buffer[0],&m_buffer[m_decimateFactor],m_posInBuffer * sizeof(float));
      m_posInBuffer -= m_decimateFactor;
      *n = *n + 1;
    }
  }
}
// downSampler getMaxData
//
//    method decimates the data. Date is overwritten by the new downsamples 
//    data. If m_rate < 1, no downsampling is needed, the number of samples in the
//    graph is below the MAX_POINTS_IN_GRAPH

void downSampler::getMaxData(int *n, float *data) {

  if ( m_decimateFactor > 1) {
  
    // copy the input data to the end of the buffer

    memcpy(&m_buffer[m_posInBuffer],data,*n * sizeof(float));
    m_posInBuffer += *n;

    // until the number of samples in the buffer is too small  (< m_rate)

    *n = 0;
    while(m_posInBuffer >= m_decimateFactor) {
      
      data[*n] = m_buffer[0];
      for(int i=1;i<m_decimateFactor;i++) {
        data[*n] =((m_buffer[i] > data[*n]) ? m_buffer[i] : data[*n]);
      } 
      
      memmove(&m_buffer[0],&m_buffer[m_decimateFactor],m_posInBuffer * sizeof(float));
      m_posInBuffer -= m_decimateFactor;
      *n = *n + 1;
    }
  }
}

// downSampler getData
//
//    method decimates the data. Date is overwritten by the new downsamples 
//    data. If m_rate < 1, no downsampling is needed, the number of samples in the
//    graph is below the MAX_POINTS_IN_GRAPH

void downSampler::getData(int *n, float *data) {

  if ( m_decimateFactor > 1) {
  
    // copy the input data to the end of the buffer

    memcpy(&m_buffer[m_posInBuffer],data,*n * sizeof(float));
    m_posInBuffer += *n;

    // until the number of samples in the buffer is too small  (< m_rate)

    *n = 0;
    while(m_posInBuffer >= m_decimateFactor) {
      data[*n] = m_buffer[0];
      memmove(&m_buffer[0],&m_buffer[m_decimateFactor],m_posInBuffer * sizeof(float));
      m_posInBuffer -= m_decimateFactor;
      *n = *n + 1;
    }
  }
}

// baseChart constructor 

baseChart::baseChart(int nchan) {

  m_numchan = nchan;

  // create the graphics 

  m_chart = new QChart;
  
  m_axisX = new QValueAxis();
  m_axisY = new QValueAxis();

  m_chart->addAxis(m_axisX,Qt::AlignBottom);
  m_chart->addAxis(m_axisY,Qt::AlignLeft);

  m_axisX->setGridLineVisible(false);
  m_axisX->setLabelsColor(Qt::cyan);

  m_axisY->setGridLineVisible(false);
  m_axisY->setLabelsColor(Qt::cyan);

  m_chart->legend()->hide();
  m_chart->setBackgroundVisible(false);

  // create for every channel a QlineSeries object and add the axis to it
  
  m_chart->removeAllSeries();

  //-jm for (int ichan = 0; ichan < m_numchan; ichan++) {

    m_series = new QLineSeries();
    m_chart->addSeries(m_series);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
  //-jm }
}

// baseChart destructor

baseChart::~baseChart() {

  //-jm if (m_axisY != NULL) delete m_axisY;
  //-jm if (m_axisX != NULL) delete m_axisX;
  //=jm if (m_chart != NULL) delete m_chart;

}

// baseChart setYaxis
//
//    set the scale of the Y axis 

void baseChart::setYaxis(float ymin, float ymax) {

  m_axisY->setRange(ymin,ymax);
}

// baseChart getChart
//
//    returns a reference to the used chart

QChart *baseChart::getChart() {

  return m_chart;
}

// baseChart getAxisRef
//
//    return references to the Y axis

QValueAxis *baseChart::getYaxisRef() {

  return m_axisY; 
}

// baseChart getAxisRef
//
//    return references to the X axis

QValueAxis *baseChart::getXaxisRef() {

  return m_axisX; 
}

// baseChart setTimeAxis
//
//    set the X-axis (= time) from 0 to <nsec> seconds 

void baseChart::setTimeAxis(float nsec) {

  // set the axis

  m_axisX->setRange(0,nsec);

  // create a downsampler and set the actual number of points for each channel

  for (int i = 0;i < m_numchan; i++) {

    int rate = round((nsec * m_sampleRate[i]) / MAX_POINTS_IN_GRAPH);
    if (rate == 0) rate = 1;
    m_pntsInGraph[i] = round(nsec * m_sampleRate[i] / rate);
    m_deltaT[i] = double(rate) / m_sampleRate[i];

    m_downSampler[i].setRate(rate);   
  }

  // clear the data series

  m_series->clear();

//-jm  for (int i=0;i<MAX_CHANNELS_IN_DISPLAY;i++) m_series[i].clear();

}
