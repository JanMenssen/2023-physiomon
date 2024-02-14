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

  for (int i=0;i<m_numchan;i++) m_curIndx[i] = 0;
  m_firstScreen = true;
}

// destructor

stripChart::~stripChart() {

}

// update

void stripChart::update(int ichan, int nsamples, float *data) {

  // locally variables are faster

  int indx = m_curIndx[ichan];
  int maxindx = m_pntsInGraph[ichan];
  float deltaT = m_deltaT[ichan];

  QVector<QPointF> *buffer = &m_dataBuffer[ichan];
  
  // downsample the data

  m_downSampler[ichan].getData(&nsamples,data);

  // the first points differs, display is empty and buffer is empty
  
  if (m_firstScreen) {

    // first screen append to the buffer

    for (int i = 0 ; i < nsamples ; i++) buffer->append(QPointF((indx+i) * deltaT, data[i]));
    m_curIndx[ichan] += nsamples;
    
  } else {
    
    // shift samples and add new samples

    indx = maxindx - nsamples;
    for (int i = 0 ; i < (indx) ; i++) buffer->replace(i,QPointF(buffer->at(i).x(),buffer->at(i+nsamples).y()));
    for (int i = 0 ; i < nsamples ; i++) buffer->replace(i+indx,QPointF(buffer->at(i+indx).x(),data[i]));

  }

  // and place the data into the series
  
  m_series[ichan]->replace(m_dataBuffer[ichan]);
}

// finishUpdate
//
//    performs actions on the chart, that are not series dependent

void stripChart::initUpdate() {

  if (m_firstScreen) {

    bool endReached = true;
    
    // check if end is reached for all channels and if this is the case reset the current index, and update the 
    // points in the graph (in stripchart this check is only needed once)

    for (int i=0;i<m_numchan;i++) endReached = endReached && (m_curIndx[i] >= m_pntsInGraph[i]);
    
    if (endReached) {
      for (int i=0;i<m_numchan;i++) m_pntsInGraph[i] = m_dataBuffer[i].count();
      m_firstScreen = false;
    }
  } 
}
