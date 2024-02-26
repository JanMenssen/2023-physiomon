//
// graphChart.cpp
//
//      this is the implementation of the abstract class <graphChart>
//
//  modifications
//    26-jan-2024   JM  initial version
//    23-feb-2024   JM  renamed to graphchart, due to introduction numeric display

#include "graphchart.h"
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

// constructor 

graphChart::graphChart(int nchan, int *chanlist) : baseChart(nchan,chanlist) {

  m_numchan = nchan;
  for (int i=0;i<m_numchan;i++) m_channels[i] = chanlist[i]; 
  
  // create the graphics

  m_axisX = new QValueAxis();
  m_axisY = new QValueAxis();

  addAxis(m_axisX,Qt::AlignBottom);
  addAxis(m_axisY,Qt::AlignLeft);

  m_axisX->setGridLineVisible(false);
  m_axisX->setLabelsColor(Qt::lightGray);

  m_axisY->setGridLineVisible(false);
  m_axisY->setLabelsColor(Qt::lightGray);

  // create for every channel a QlineSeries object and add the axis to it. Reserve space 
  // for the samples
  
  this->removeAllSeries();

  for (int ichan = 0; ichan < m_numchan; ichan++) {

    m_series << new QLineSeries();

    this->addSeries(m_series[ichan]);
    m_series[ichan]->attachAxis(m_axisX);
    m_series[ichan]->attachAxis(m_axisY);
    //-jm m_series[ichan]->setUseOpenGL(true);

    m_dataBuffer[ichan].reserve(MAX_POINTS_IN_GRAPH);
  }   
}

// destructor

graphChart::~graphChart() {

  if (m_axisY != NULL) delete m_axisY;
  if (m_axisX != NULL) delete m_axisX;
}

// setYaxis
//
//    set the scale of the Y axis 

void graphChart::setYaxis(float ymin, float ymax) {

  m_axisY->setRange(ymin,ymax);
  //-jm m_axisY->applyNiceNumbers();
}

// setTimeAxis
//  
//    set the X-axis (= time) from 0 to <nsec> seconds 

void graphChart::setTimeAxis(float nsec) {

  // set the axis

  m_axisX->setRange(0,nsec);
  //-jm m_axisX->applyNiceNumbers();
}


// getYaxisRef
//
//    return references to the Y axis

QValueAxis *graphChart::getYaxisRef() {

  return m_axisY; 
}

// getXaxisRef
//
//    return references to the X axis

QValueAxis *graphChart::getXaxisRef() {

  return m_axisX; 
}

// setLabels
//
// sets the labels on the channels

void graphChart::setLabels(physiomon_settings *settings) {

  for (int i=0;i<m_numchan;i++) {
    int curchan = m_channels[i];
    m_series[i]->setName(settings->m_channels[curchan].name);
  }
  this->legend()->show();
  this->legend()->setLabelBrush(Qt::lightGray);
  this->legend()->detachFromChart();
  this->legend()->setBackgroundVisible(false);
  this->legend()->setBorderColor(Qt::lightGray);
  this->legend()->setGeometry(500,100,150,40);
  this->legend()->update();
  //-jm m_chart->legend()->attachToChart();
  this->legend()->setInteractive(true);
    
  //-jm m_chart->legend()->setGeometry(pos.x(),pos.y(),150,40);
}


// initPlot
//
// configures the x-data using time on the x-axis and the sampleRate. To speed up the
// process, we limit the number of points in the graph and use a downsampler if the
// needed
 
void graphChart::initPlot(physiomon_channels *channels) {

  float nsec = m_axisX->max();
  
  for (int ichan = 0;ichan < m_numchan;ichan++) {
  
    // get the sample rate

    int curchan = m_channels[ichan];
    int sampleRate = channels->getSampleRate(curchan);

    // calculate the rate after downsampling
    
    int rate = round(nsec * sampleRate / MAX_POINTS_IN_GRAPH);
    if (rate == 0) rate = 1;
    m_pntsInGraph[ichan] = round(nsec * sampleRate / rate);
    m_downSampler[ichan].setRate(rate);  
  
    m_deltaT[ichan] = float(rate) / sampleRate;
    
    // and clear the series

    m_series[ichan]->clear();
  } 
}

// initUpdate

bool graphChart::initUpdate() {

  // check if end is reached for all channels and if this is the case reset the current index, and update the 
  // points in the graph (in stripchart this check is only needed once)
  
  bool endReached = true;    
  for (int i=0;i<m_numchan;i++) endReached = endReached && (m_indx[i] >= m_pntsInGraph[i]);
  if (endReached) {
    for (int i=0;i<m_numchan;i++) m_indx[i] = 0;
    m_firstScreen = false;
  }

  return endReached;
}


// finishUpdate

void graphChart::finishUpdate() {

  // move the data in th databuffers to the axis

  for (int i = 0; i < m_numchan ; i++) m_series[i]->replace(m_dataBuffer[i]);

  QPointF pos = this->mapToPosition(QPointF(12,4.5));
  //-jm qDebug() << "finishUpdate " << pos;
  this->legend()->setGeometry(pos.x(),pos.y(),150,40);
}




