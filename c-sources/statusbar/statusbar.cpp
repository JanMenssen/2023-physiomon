//
// statusbar.cpp
//
//    implementation for the <statusBar> class as used in LabView and Matlab
//
//  modifications
//    12-jan-2024   JM  initial version

#include "statusbar.h"
#include <QString>
#include <Qtime>

#include <stdio.h>

// constructore

statusBarNew::statusBarNew() {
}

// setText
//
//      displays <txtToDisplay> for <timeToDisplay> seconds in the statusbar. The message is 
//      prefixed with the current time

void statusBarNew::setText(QString txtToDisplay, float timeToDisplay) {

  // get the current time in a format hh:mm:ss

  QTime time = QTime::currentTime();
  QString formattedTime = time.toString("hh:mm:ss");
  
  // and display
  
  txtToDisplay = formattedTime + QString(" >>> ") + txtToDisplay;
  showMessage(txtToDisplay,int(timeToDisplay * 1000));
}

    