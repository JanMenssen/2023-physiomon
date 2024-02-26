//
// numericChart.cpp
//
//      this is the implementation of the abstract class <graphChart>
//
//  modifications
//    26-jan-2024   JM  initial version
//    23-feb-2024   JM  renamed to graphchart, due to introduction numeric display

#include "numericchart.h"
#include "QGraphicsScene"
#include "QGraphicsView.h"

// constructor 

numericChart::numericChart(int nchan, int *chanlist) : baseChart(nchan,chanlist) {

  m_numchan = nchan;
  for (int i=0;i<m_numchan;i++) m_channels[i] = chanlist[i]; 
  // create pointers to the labels and the values

  m_labels = new QGraphicsSimpleTextItem *[m_numchan];
  m_text = new QGraphicsSimpleTextItem *[m_numchan];
}

// destructor

numericChart::~numericChart() {
}

// setLabels

void numericChart::setLabels(physiomon_settings *settings) {

  for(int i=0;i<m_numchan;i++) {
    int curchan = m_channels[i];
    m_labelTxt.append(settings->m_channels[curchan].name);
  }

}

// initPlot
//
//    initialises the plot, channels contains the color and the labels so set up
//    the labels 

void numericChart::initPlot(physiomon_channels *channels) {
  
  QSizeF size = this->size();
  qDebug() << "initPlot" << size;
}


// update
//
//    place the average value on the screen if nsamples > 0, else keep the
//    value on the screen


void numericChart::update(int ichan, int nsamples, float *data) {

  // calculate the average value if nsamples > 0 and convert it to a string
  
  //-jm qDebug() << "--> update";

  if (nsamples > 0) {
    m_Value[ichan] =0.0;
    for (int i=0;i<nsamples;i++) m_Value[ichan] += data[i];
    m_Value[ichan] = m_Value[ichan] / nsamples;
  }

  QString valueTxt = QString("%1").arg(m_Value[ichan],0,'f',1);
  
  // and place the value on the screen

  m_text[ichan] = new QGraphicsSimpleTextItem(valueTxt,this);
  m_text[ichan]->setFont(m_fontValues);
  m_text[ichan]->setBrush(Qt::green);

  QRectF rectangle = m_text[ichan]->boundingRect();
  m_text[ichan]->setPos((m_posValue[ichan].x() - rectangle.width()/2), (m_posValue[ichan].y() - rectangle.height()/2 ));
}

// initUpdate
//
//    clears the current value on the screen

bool numericChart::initUpdate() {

  // delete the values on the screen

  //-jm qDebug() << "--> initUpdate";

  for (int i=0;i<m_numchan;i++) {
    if (m_text[i] != nullptr) delete(m_text[i]);
    if (m_labels[i] != nullptr) delete(m_labels[i]);
  }
    
  // get the size of the display and determine the areas the information should be
  // displayed, depending on area is largest in vertical or horizontal direction

  QSizeF size = this->size();
  //-jm qDebug() << "initUpdate" << size;
  if (size.width() > size.height()) {

    // horizontal mode

    float width = size.width() / m_numchan;
    for (int i=0;i<m_numchan;i++) m_numArea[i] = QRectF(i*width,0,width,size.height()-1);

  } else {

    // vertical mode 

    float height = size.height() / m_numchan;
    for (int i=0;i<m_numchan;i++) m_numArea[i] = QRectF(0,i*height,size.width()-1,height);
  }

  // set the font 
  
  int pixelSizeLabel = int(0.2 * m_numArea[0].height());
  if ((size.width() / 10) < pixelSizeLabel) pixelSizeLabel = int(size.width()/10);
  m_fontLabels.setPixelSize(pixelSizeLabel);  
  
  int pixelSizeValue = int(0.5 * m_numArea[0].height());
  if ((size.width() / 10) < pixelSizeValue) pixelSizeValue = int(size.width()/4);
  m_fontValues.setPixelSize(pixelSizeValue);

  // now find the middle position for the label and the value

  for (int i=0;i<m_numchan;i++) {
    QPointF center = m_numArea[i].center(); 
    m_posValue[i] = QPointF(center.x(), center.y());
    m_posLabel[i] = QPointF(center.x(), center.y() - 0.6 * (pixelSizeValue + pixelSizeLabel));
  }

  // place the labels, color is light gray

  for (int i=0;i<m_numchan;i++) {

    m_labels[i] = new QGraphicsSimpleTextItem(m_labelTxt[i],this);
    m_labels[i]->setFont(m_fontLabels);
    m_labels[i]->setBrush(Qt::lightGray);

    QRectF rectangle = m_labels[i]->boundingRect();
    m_labels[i]->setPos((m_posLabel[i].x() - rectangle.width()/2), (m_posLabel[i].y() - rectangle.height()/2 ));
  }

  return true;
}

// finishUpdate

void numericChart::finishUpdate() {
}



