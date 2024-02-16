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

stripChart::stripChart(int nchan, int *chanlist) : baseChart(nchan, chanlist) {

}

// destructor

stripChart::~stripChart() {

}

// update

void stripChart::update(int ichan, int nsamples, float *data) {

  // locally variables are faster

  int indx = m_indx[ichan];
  int maxindx = m_pntsInGraph[ichan];
  float deltaT = m_deltaT[ichan];

  QVector<QPointF> *buffer = &m_dataBuffer[ichan];
  
  // downsample the data

  m_downSampler[ichan].getData(&nsamples,data);

  if (m_firstScreen) {

    // add samples to the buffer until the size of the buffer is reachdd, then shift

    int shift = nsamples - (maxindx - indx);

    if (shift > 0) {
    
      for (int i=shift;i<indx;i++) buffer->replace((i-shift),QPointF(buffer->at(i-shift).x(),buffer->at(i).y()));
      for (int i=indx-shift;i<indx;i++) buffer->replace(i,QPointF(buffer->at(i).x(),data[i-indx+shift]));
      for (int i=indx;i<maxindx;i++) buffer->append(QPointF(i * deltaT,data[i-indx+shift]));
      indx += nsamples - shift;

    }  else { 

      for (int i=0;i<nsamples;i++) buffer->append(QPointF((indx+i) * deltaT, data[i]));
      indx += nsamples;
    }

  } else {
    
    // shift samples and add new samples

    int shift = maxindx - nsamples;
    for (int i = 0 ; i < shift ; i++) buffer->replace(i,QPointF(buffer->at(i).x(),buffer->at(i+nsamples).y()));
    for (int i = 0 ; i < nsamples ; i++) buffer->replace(i+shift,QPointF(buffer->at(i+shift).x(),data[i]));

  }

  // done, update the current positipm 
  
  m_indx[ichan] = indx; 
}

