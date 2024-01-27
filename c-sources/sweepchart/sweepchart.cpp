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

sweepChart::sweepChart(int nchan) : baseChart(nchan) {

  qDebug() << "--> sweepChart::sweepchart";
}

// destructor

sweepChart::~sweepChart() {
  
}

// setTimeAxis
//
//    sets the time axis and together with the sample frequency, the number of points is known
//    and the buffer can be allocated

void sweepChart::setTimeAxis(float nsec) {

  qDebug() << "-->in sweepchart::setTimexAxis";
  baseChart::setTimeAxis(nsec);

  // clear the data m_series

  m_series->clear();
}

// update

void sweepChart::update(int nchan, int nsamples, float *data) {

  int indx = m_series->count();

  // sweep back if we are on the end of the graph

  if (indx >= m_pntsInGraph[nchan]) {
    indx = 0;
    m_series->clear();
  }
  
  // downsample the data

  m_downSampler->getData(&nsamples,data);

  // and place the data in the buffer

  QPointF tmp;

  for (int i = 0 ; i < nsamples ; i++) {

    tmp.setX(((indx + i) * m_deltaT[nchan]));
    tmp.setY(data[i]);
    
    m_buffer.append(tmp);
  }

  // and append the new data to the series 

  m_series->append(m_buffer);
}
