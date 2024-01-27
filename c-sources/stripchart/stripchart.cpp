//
// stripChart
//
//    implementation ot fhe <stripChart> class. This class updates the screen like a paper scrip chart recorder,
//    if on the upper right part of the screen data is shifted to the left and the new data is added on the right  
//
// modifications
//    26-jan-2024  JM   initial version

#include "stripchart.h"
#include <QDebug>

// constructor

stripChart::stripChart(int nchan) : baseChart(nchan) {

  qDebug() << "--> stripChart::stripChart";
}

// destructor

stripChart::~stripChart() {

}

// setTimeAxis
//
//    sets the time axis and together with the sample frequency, the number of points is known
//    and the buffer can be allocated

void stripChart::setTimeAxis(float nsec) {

  qDebug() << "-->in stripchart::setTimexAxis";
  baseChart::setTimeAxis(nsec);

  m_npoints = nsec * m_sampleRate;

  // tempory fill the buffer

  float x = 0;
  float y = 0;
  
  m_buffer.clear();

  m_npoints = 1000;
  
  m_dataValues = new float[m_npoints];

  for (long i=0;i<m_npoints;i++) {
    
    x = 10.0 * i / (float(m_npoints));
    y = i / (float(m_npoints));
    m_dataValues[i] = y;

    m_buffer.append(QPointF(x,y));
  }

  m_series->append(m_buffer);

}

// update

void stripChart::update(int nchan, int nsamples, float *data) {

  // store first value

  float firstValue = m_dataValues[0];
  long n = m_npoints - 1;

  // and shift all samples one position

  for (long i = 0; i < n; i++) {
    m_dataValues[i] = m_dataValues[i+1];
    m_buffer[i].setY(m_dataValues[i]);
  }
  
  // add first value at the end of the buffer

  m_dataValues[n] = firstValue;
  m_buffer[n].setY(firstValue);

  // and replace the buffer

  m_series->replace(m_buffer);
  
}
