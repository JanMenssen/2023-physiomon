//
// scopeChart
//
//    implementation ot fhe <scopeChart> class. This class updates the screen like a oscilloscope, if on 
//    the upper right part of the screen the next point overrides the points on the left 
//
// modifications
//    26-jan-2024  JM   initial version

#include "scopechart.h"

// constructor

scopeChart::scopeChart(int nchan) : baseChart(nchan) {
 
  for (int i=0;i<nchan;i++) m_buffer[i].reserve(MAX_POINTS_IN_GRAPH);

  // create a red line reference for the current position

  QValueAxis *x_axis = getXaxisRef();
  QValueAxis *y_axis = getYaxisRef();

  m_scopeLine = new QLineSeries();
  m_chart->addSeries(m_scopeLine);
  m_scopeLine->attachAxis(x_axis);
  m_scopeLine->attachAxis(y_axis);

  QPen pen = m_scopeLine->pen();
  pen.setWidth(1);
  pen.setColor("red");
  m_scopeLine->setPen(pen);
}

// destructor

scopeChart::~scopeChart() {

}
// setTimeAxis
//
//    sets the time axis and together with the sample frequency, the number of points is known
//    and the buffer can be allocated

void scopeChart::setTimeAxis(float nsec) {

  baseChart::setTimeAxis(nsec);

  // we start again, reset everything
  
  for (int i=0;i<MAX_CHANNELS_IN_DISPLAY;i++) {
 
    m_first[i] = true; 
    m_buffer[i].clear();
    m_curIndx[i] = 0;
  }
}

// setYaxis
//
//    the scope chart has a specific setYaxis function because the values should be 
//    known for the red line seperating the future and the parameters

void scopeChart::setYaxis(float ymin,float ymax) {

  baseChart::setYaxis(ymin,ymax);

  m_yLimits[0] = ymin;
  m_yLimits[1] = ymax; 
}

// update

void scopeChart::update(int nchan, int nsamples, float *data) {

  QPointF tmp;

  // locally variables are faster

  int curIndx = m_curIndx[nchan];           
  int maxIndx = m_pntsInGraph[nchan];
  double deltaT = m_deltaT[nchan];
  QVector<QPointF> *buffer = &m_buffer[nchan];

  // at display overlap, index in buffer should be 0 and not first display

  if (curIndx > maxIndx) {
    curIndx = 0;
    if (m_first[nchan]) {
      m_first[nchan] = false;
      maxIndx = m_pntsInGraph[nchan] = m_series[nchan]->count();
    }  
  } 

  // downsample the data

  m_downSampler[nchan].getData(&nsamples,data);

  // the first points differs, display is empty and buffer is empty
  
  if(m_first[nchan]) {

    for (int i = 0 ; i < nsamples ; i++) {

    tmp.setX(((curIndx++) * deltaT));
    tmp.setY(data[i]);
    
    buffer->append(tmp);
  }

  } else {
    
    for (int i = 0 ; i < nsamples ; i++) {

      tmp.setX(((curIndx) * deltaT));
      tmp.setY(data[i]);
    
      buffer->replace(curIndx++,tmp);
      curIndx = (curIndx >= maxIndx ? 0 : curIndx); 
    }
  }

  // and replace the series with the new data

  m_series[nchan]->replace(m_buffer[nchan]);
  m_curIndx[nchan] = curIndx;
 
}

// finishUpdate
//
//    performs actions on the chart, that are not series dependent

void scopeChart::finishUpdate() {

  QVector<QPointF> posline;

  if (!m_first[0]) {

    posline.append(QPointF((m_curIndx[0] * m_deltaT[0]),m_yLimits[0]));
    posline.append(QPointF((m_curIndx[0] * m_deltaT[0]),m_yLimits[1]));

    m_scopeLine->replace(posline);
  }
}
