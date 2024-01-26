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

// we use a 20x20 grid this means a resolution of 0.05

#define RESOLUTION 0.05

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

  if (m_layout != NULL) delete m_layout;
  if (m_dispContents != NULL) delete m_dispContents;

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

    viewMode mode = MODE_STRIP;
    switch (mode) {

      case MODE_STRIP :
        m_dispContents[iDisp].chart = new stripChart(numchan);
        break;

      case MODE_SWEEP :
        m_dispContents[iDisp].chart = new sweepChart(numchan);
        break;

      case MODE_SCOPE :
        m_dispContents[iDisp].chart = new scopeChart(numchan);
        break;

      default :
        m_dispContents[iDisp].chart = new stripChart(numchan);
        break;
    }

    // calculate the position. we use a gridview of RESOLUTION * RESOLUTION, calculate the column and rows
    // of thc current display

    displayStruct curDisplay = settings->m_displays[iDisp];
    
    int irow = round(curDisplay.top / RESOLUTION);
    int icol = round(curDisplay.left / RESOLUTION);
    int nrow = round(curDisplay.height / RESOLUTION);
    int ncol = round(curDisplay.width / RESOLUTION);

    maxrow = (nrow > maxrow ? nrow : maxrow);
    maxcol = (ncol > maxcol ? ncol : maxcol);

    QChartView *chartView = new QChartView(m_dispContents[iDisp].chart->getChart());
    m_layout->addWidget(chartView);

  }

  // check there is space left in the grid and fill it up with an empty
       
  irow = maxrow;
  icol = maxcol;
  nrow = 1/RESOLUTION - irow;
  ncol = 1/RESOLUTION - icol;
     
  //-jm if (nrow > 0) m_layout->addWidget(QWidget(),irow,nrow,0,int(1/RESOLUTION));
  //-jm if (ncol > 0) m_layout->addWidget(QWidget(),0,int(1/RESOLUTION),icol,ncol);
}

// plot
//
//    plots the new data

void displays::plot(channels *channels) {

  return;
}