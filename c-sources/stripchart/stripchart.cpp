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

  for (int i=0;i<nchan;i++) m_buffer[i].reserve(MAX_POINTS_IN_GRAPH);
}

// destructor

stripChart::~stripChart() {

}

// setTimeAxis
//
//    sets the time axis and together with the sample frequency, the number of points is known
//    and the buffer can be allocated

void stripChart::setTimeAxis(float nsec) {

  baseChart::setTimeAxis(nsec);

  for (int i=0;i<MAX_CHANNELS_IN_DISPLAY;i++) {
   
    m_first[i] = true; 
    m_buffer[i].clear();
    m_curIndx[i] = 0;

  }
}

// update

void stripChart::update(int nchan, int nsamples, float *data) {

  QPointF tmp;

  // locally variables are faster

  int curIndx = m_curIndx[nchan];           
  int maxIndx = m_pntsInGraph[nchan];
  double deltaT = m_deltaT[nchan];
  QVector<QPointF> *buffer = &m_buffer[nchan];

  // at display overlap, index in buffer should be 0 and not first display

  if (curIndx >= maxIndx) {
    maxIndx = m_pntsInGraph[nchan] = buffer->count();
    m_first[nchan] = false;
  }

  // downsample the data

  m_downSampler[nchan].getData(&nsamples,data);

  // the first points differs, display is empty and buffer is empty
  
  if(m_first[nchan]) {

    for (int i = 0 ; i < nsamples ; i++) {

      tmp.setX(((curIndx++) *deltaT));
      tmp.setY(data[i]);
    
      buffer->append(tmp);
  }

  } else {
    
    // shift samples

    for (int i = 0 ; i < (maxIndx - nsamples) ; i++) {

      tmp = buffer->at(i+nsamples);
      tmp.setX(i * deltaT);
      
      buffer->replace(i,tmp);
    }
    curIndx = maxIndx - nsamples;
    
    // and add new samples

    for (int i = 0 ; i < nsamples ; i++) {

      tmp.setX(((curIndx) * deltaT));
      tmp.setY(data[i]);
    
      buffer->replace(curIndx++,tmp);
      curIndx = (curIndx > maxIndx ? 0 : curIndx); 
    }
  }

  // and replace the series with the new data

  m_series[nchan].replace(m_buffer[nchan]);
  m_curIndx[nchan] = curIndx;
}