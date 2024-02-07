//
// sweepChart.cpp
//
//    implementation of the <sweepChart> class. This class updates the screen like a oscilloscope in sweep 
//    mode. If on the end of ths screen, the scteen is cleared and the next pixel is on the levt 
//
//  modifications
//    26-jan-2025   JM    initial version

#include "sweepchart.h"

// constructor
// 
//    allocate memory for the points buffer -> faster

sweepChart::sweepChart(int nchan) : baseChart(nchan) {
  
  for (int i=0;i<nchan;i++) m_buffer[i].reserve(MAX_POINTS_IN_GRAPH);
}

// destructor

sweepChart::~sweepChart() {
  
}

// setTimeAxis
//
//    sets the time axis and together with the sample frequency, the number of points is known
//    and the buffer can be allocated

void sweepChart::setTimeAxis(float nsec) {

  baseChart::setTimeAxis(nsec);
  for (int i=0;i<MAX_CHANNELS_IN_DISPLAY;i++) m_curIndx[i] = 0;
 
}

// update

void sweepChart::update(int nchan, int nsamples, float *data) {

  // faster

  int curIndx = m_curIndx[nchan];           
  int maxIndx = m_pntsInGraph[nchan];
  double deltaT = m_deltaT[nchan];
  QVector<QPointF> *buffer = &m_buffer[nchan];

  // sweep back if we are on the end of the graph

  if (curIndx >= maxIndx) {
    curIndx = 0;
    m_series[nchan]->clear();
  }
  
  // downsample the data
 
  m_downSampler[nchan].getData(&nsamples,data);
 
  // and place the data in the (cleared) buffer

  QPointF tmp;
  buffer->clear();

  for (int i = 0 ; i < nsamples ; i++) {

    tmp.setX(((curIndx++) * deltaT));
    tmp.setY(data[i]);
    
    buffer->append(tmp);
  }

  // and append the new data to the series, this is not faster as append point for point
  // so m_buffer is in fact not needed. However, in stripchart and scopechart 

  m_series[nchan]->append(buffer[nchan]);
  m_curIndx[nchan] = curIndx;
}
