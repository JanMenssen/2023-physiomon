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

downSampler::downSampler(int rate) {

  m_decimateFactor = rate;
}

// downSampler destructor

downSampler::~downSampler() {

}

// downSampler getData
//
//    method downsamples the data. Date is overwritten by the new downsamples 
//    data. If m_rate < 1, no downsampling is needed, the number of samples in the
//    graph is below the MAX_POINTS_IN_GRAPH

void downSampler::getData(int *n, float *data) {

  if ( m_decimateFactor > 1) {
  
    // copy the input data to the end of the buffer

    memcpy(&m_buffer[m_posInBuffer],data,*n * sizeof(float));
    m_posInBuffer += *n;

    // until the number of samples in the buffer is too small  (< m_rate)

    *n = 0;
    while(m_posInBuffer > m_decimateFactor) {

      data[*n++] = m_buffer[0];
      memmove(&m_buffer[0],&m_buffer[m_decimateFactor],m_decimateFactor * sizeof(float));
      m_posInBuffer -= m_decimateFactor;
    }
  }
}


// baseChart constructor 

baseChart::baseChart(int nchan) {

  qDebug() << "--> baseChart::baseChart";

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
  
  m_numchan = nchan;
  m_series = new QLineSeries;
  for (int ichan = 0; ichan < m_numchan; ichan++) {

    m_chart->addSeries(&m_series[ichan]);

    m_series[ichan].attachAxis(m_axisX);
    m_series[ichan].attachAxis(m_axisY);
  }
}



// baseChart destructor

baseChart::~baseChart() {

  if (m_axisY != NULL) delete m_axisY;
  if (m_axisX != NULL) delete m_axisX;
  if (m_series != NULL) delete m_series;
  if (m_chart != NULL) delete m_chart;

}

// baseChart setYaxis
//
//    set the scale of the Y axis 

void baseChart::setYaxis(float ymin, float ymax) {

  m_axisY->setRange(ymin,ymax);
}

// baseChart getChart
//
//    returns a reference to the chart

QChart *baseChart::getChart() {

  return m_chart;
}

// baseChart setTimeAxis
//
//    set the X-axis (= time) from 0 to <nsec> seconds 

void baseChart::setTimeAxis(float nsec) {

  qDebug() << "-->in basechart::setTimexAxis";

  // set the axis

  m_axisX->setRange(0,nsec);

  // create a downsampler and set the actual number of points for each channel

  for (int i = 1;i < m_numchan; i++) {

    int rate = round((nsec * m_sampleRate[i]) / MAX_POINTS_IN_GRAPH);
    m_pntsInGraph[i] = round(nsec * m_sampleRate[i] / rate);
    m_deltaT[i] = m_sampleRate[i] / rate;

    if (m_downSampler != NULL) delete m_downSampler;
    m_downSampler = new downSampler(rate);
  }
}
