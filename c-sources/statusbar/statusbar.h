//
// statusbar.h 
//
//      implementation of the <statusBar> class. This is the same <statusBar> as used in Matlab and
//      in LabView
//
//  modifications
//    12-jan-2024   JM  initial version

#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include <QStatusBar>

class statusBarNew : public QStatusBar {

  public :
  
    statusBarNew();
    void setText(QString txtToDislay, float timeToDisplay);

};

#endif


