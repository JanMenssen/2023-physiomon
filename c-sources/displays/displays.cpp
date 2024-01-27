//
// displays.cpp
//
//    implementation of the <displays> class. This class is responsible for the plotting
//    of the data.
//
//  modifications
//    14-jan-2024   JM  initial version

#include "displays.h"
#include "stripchart.h"
#include "sweepchart.h"
#include "scopechart.h"

#include <QDebug>


// we use a 20x20 grid this means a resolution of 0.05

#define RESOLUTION 0.05F

// constructor

displays::displays(QWidget *centralWidget) {

  m_numDisplays = 0;
  
  m_layout = new QGridLayout();
  m_layout->setHorizontalSpacing(0);
  m_layout->setVerticalSpacing(0);
  centralWidget->setLayout(m_layout);

}

// destructor

displays::~displays() {
/*
  if (m_layout != NULL) delete m_layout;
  if (m_dispContents != NULL) delete m_dispContents;
*/
}

// initialise

void displays::initialise() {

}
// configure

void displays::configure(settings *settings) {
  
  // these parameters are needed to calculate the position in the grid

  int irow = 0, nrow = 0, maxrow = 0;         
  int icol = 0, ncol = 9, maxcol = 0;         

  // first remove the current layout

  int count = m_layout->count();
  for (int i = 0 ; i < count ; i++) m_layout->removeItem(m_layout->itemAt(i));
  if (m_dispContents != NULL) delete m_dispContents;

  int numchan = settings->m_numchan;
  m_numDisplays = settings->m_numdisp;
  m_dispContents = new dispSettingStruct[m_numDisplays];

  for (int iDisp = 0; iDisp < m_numDisplays ; iDisp++) {
  
    // find the channels for the current display

    for (int iChan = 0 ; iChan < numchan ; iChan++) {
    
      if ((settings->m_channels[iChan].display-1) == iDisp) {
        m_dispContents[iDisp].chanlist[m_dispContents[iDisp].nchan++] = iChan;
      }   
    }
   
    // tempory code because there is no mode set in the structure
    //-jm viewMode mode = settings->m_displays(iDisp).viewMode;

    viewMode mode = MODE_SWEEP;
    switch (mode) {

      case MODE_STRIP :
        m_dispContents[iDisp].chart = new stripChart(m_dispContents[iDisp].nchan);
        break;

      case MODE_SWEEP :
        m_dispContents[iDisp].chart = new sweepChart(m_dispContents[iDisp].nchan);
        break;

      case MODE_SCOPE :
        m_dispContents[iDisp].chart = new scopeChart(m_dispContents[iDisp].nchan);
        break;

      default :
        m_dispContents[iDisp].chart = new stripChart(m_dispContents[iDisp].nchan);
        break;
    }

    // calculate the position. we use a gridview of RESOLUTION * RESOLUTION, calculate the column and rows
    // of thc current display

    displayStruct curDisplay = settings->m_displays[iDisp];
    
    irow = round(curDisplay.top / RESOLUTION);
    icol = round(curDisplay.left / RESOLUTION);
    nrow = round(curDisplay.height / RESOLUTION);
    ncol = round(curDisplay.width / RESOLUTION);

    maxrow = (nrow > maxrow ? nrow : maxrow);
    maxcol = (ncol > maxcol ? ncol : maxcol);

    QChartView *chartView = new QChartView(m_dispContents[iDisp].chart->getChart());
    m_layout->addWidget(chartView,irow,icol,nrow,ncol);

    // and set the graphic

    m_dispContents[iDisp].chart->setYaxis(-500, 500);
    m_dispContents[iDisp].chart->setTimeAxis(10.0);

  }

  // check there is space left in the grid and fill it up with an empty
       
  irow = maxrow;
  icol = maxcol;
  nrow = 1/RESOLUTION - irow;
  ncol = 1/RESOLUTION - icol;
  
  QWidget *tmp = new QWidget();
  if (nrow > 0) m_layout->addWidget(tmp,irow,0,nrow,int(1/RESOLUTION));
  if (ncol > 0) m_layout->addWidget(tmp,0,icol,int(1/RESOLUTION),ncol);
  
}

// plot
//
//    plots the new data

void displays::plot(channels *channels) {

  float data[100];          // max 100 samples can be read
  int nSamples = 0;       

  for (int iDisp = 0; iDisp < m_numDisplays ; iDisp++) {

    // a display can have more channels, do it for all channels

    int numchan = m_dispContents[iDisp].nchan;
    for (int ichan=0;ichan < numchan; ichan++) {

      int curchan = m_dispContents[iDisp].chanlist[ichan];
      
      channels->readDisplay(curchan,&nSamples,data);
      m_dispContents[iDisp].chart->update(curchan,nSamples,data);
    }   
  }  

  return;
}