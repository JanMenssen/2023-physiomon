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
  m_series = getSeries();
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

  m_npoints = int(nsec * 500);

  // clear the buffer

  //-jm m_series->clear();

}

// update

void sweepChart::update(int nchan, int nsamples, float *data) {

  QPointF tmp;
  
  // ask the number of samples in the buffer, clear it if it is fileld

  int i = m_series->count();

  if (i >= m_npoints) {
    i = 0;
    m_series->clear();
  }

  // note currently we update the screen for every point, this should be disabled

  for (int isample = 0 ; isample < nsamples ; isample++) {

    tmp.setX((i + isample) * 10.00 / m_npoints);
    tmp.setY(data[isample]);

    m_series->append(tmp);
  }  

}
