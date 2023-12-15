#
# main.py
#
#     this is the main file for the FysioMon project. Visualisation and storage of physiological
#     signals
#
# Modifications
#     15-dec-2023  JM  initial version

import sys
from PySide6.QtWidgets import QApplication, QMainWindow,QMdiArea, QMdiSubWindow, QTextEdit, QMenu, QStatusBar
from PySide6.QtGui import QAction
from statusbar import myStatusBar

# define the MDI class

class MDIWindow(QMainWindow) :

  # constructor

  def __init__(self) :
    super().__init__()

    self.count = 0

    self.mdi = QMdiArea()
    self.setCentralWidget(self.mdi)

    # create the menu structure

    bar = self.menuBar()
    fileMenu = QMenu("&File", self)
    bar.addMenu(fileMenu)

    newAction = QAction("New",self)
    newAction.triggered.connect(self.newPressed)
    fileMenu.addAction(newAction)

    cascadeAction = QAction("Cascade",self)
    cascadeAction.triggered.connect(self.cascadePressed)
    fileMenu.addAction(cascadeAction)

    tiledAction = QAction("Tiled",self)
    tiledAction.triggered.connect(self.tiledPressed)
    fileMenu.addAction(tiledAction)

    # and the statusbar

    statusbar = myStatusBar()
    self.setStatusBar(statusbar)
    statusbar.setText("ready",3)

    self.setWindowTitle("MDI Application")


  def newPressed(self) :

    self.count = self.count + 1
      
    sub = QMdiSubWindow()
    sub.setWidget(QTextEdit())
    sub.setWindowTitle("Sub Windows " + str(self.count))

    self.mdi.addSubWindow(sub)
    sub.show()

  def cascadePressed(self) :
  
    self.mdi.cascadeSubWindows()

  def tiledPressed(self) :
      
    self.mdi.tileSubWindows()

# main loop
      
if __name__ == '__main__' :

  app = QApplication(sys.argv)
  mdiwindow = MDIWindow()
  mdiwindow.show()
  sys.exit(app.exec())



    

    