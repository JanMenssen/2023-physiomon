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
  
  for (int i=0;i<nchan;i++) m_buffer[i].reserve(SIZE_DOWNSAMPLE_BUFFER);

  // create a red line reference for the current position

  QChart *chart = getChart();
  QValueAxis *x_axis = getXaxisRef();
  QValueAxis *y_axis = getYaxisRef();

  //-jm m_chart->addSeries(m_curPositionLine);
  //-jm m_curPositionLine->attachAxis(x_axis);
  //-jm m_curPositionLine->attachAxis(y_axis);
  
  
  //-jm m_yLimit[0] = y_axis->min();
  //-jm m_yLimit[1] = y_axis->max();

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

// update

void scopeChart::update(int nchan, int nsamples, float *data) {

  QPointF tmp;

  // locally variables are faster

  int curIndx = m_curIndx[nchan];           
  int maxIndx = m_pntsInGraph[nchan];
  double deltaT = m_deltaT[nchan];
  QVector<QPointF> *buffer = &m_buffer[nchan];

  // at display overlap, index in buffer should be 0 and not first display

  if (curIndx >= maxIndx) {
    curIndx = 0;
    m_first[nchan] = false;
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
      curIndx = (curIndx > maxIndx ? 0 : curIndx); 
    }
  }

  // and replace the series with the new data

  m_series[nchan].replace(m_buffer[nchan]);
  m_curIndx[nchan] = curIndx;
}

// finishUpdate
//
//    performs actions on the chart, that are not series dependent

void scopeChart::finishUpdate() {

  QVector<QPointF> posline;

  posline.append(QPointF(m_curIndx[0],m_yLimit[0]));
  posline.append(QPointF(m_curIndx[0],m_yLimit[1]));

//=jm  m_curPositionLine->replace(posline);

}
