#
# main.py
#
#     this is the main file for the FysioMon project. Visualisation and storage of physiological
#     signals
#
# Modifications
#     15-dec-2023  JM  initial version

import sys
from PySide6.QtWidgets import QApplication, QMainWindow,QMdiArea, QMdiSubWindow, QTextEdit, QMenu, QMessageBox
from PySide6.QtGui import QAction
from PySide6.QtCore import QTimer
from PySide6.QtCharts import QChartView
from PySide6.QtMultimedia import QAudioFormat, QAudioSource, QMediaDevices
from statusbar import myStatusBar
from stripchart import stripChart

# define the MDI class

class MDIWindow(QMainWindow) :

  # constructor
  #
  #   - windows are created
  #   - menus are created
  #   - audio device is created and coupled (should be replaced by data from arduino)
    
  def __init__(self,device) :
    super().__init__()

    self.count = 0
    self.m_scope = []

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

    # audio device

    self.name = device.description()

    m_formatAudio = QAudioFormat()
    m_formatAudio.setSampleRate(8000)
    m_formatAudio.setChannelCount(1)
    m_formatAudio.setSampleFormat(QAudioFormat.UInt8)

    self.m_audioInput = QAudioSource(device, m_formatAudio, self)
    self.m_ioDevice = self.m_audioInput.start()
    #-jm self.m_ioDevice.readyRead.connect(self.update)

  # update
  #
  #     this function updates the windows if there is data available
    
  def update(self) :
    
    data = self.m_ioDevice.readAll()
    print(data.size())
    if self.count > 0 :
      for i in range(self.count) :
        self.m_scope[i].update(data)

  # newPressed
  #
  #     callback which is called when a new window should be created. The subwindow is created
  #     containing a stripchart. Number of windows is incremented
        
  def newPressed(self) :

    scope = stripChart(f"Data from the microphone ({self.name})")
    self.m_scope.append(scope)

    self.m_chartView = QChartView(self.m_scope[self.count].m_chart)

    sub = QMdiSubWindow()
    sub.setWidget(self.m_chartView)
    sub.setWindowTitle("Sub Windows " + str(self.count))

    self.mdi.addSubWindow(sub)
    sub.show()

    self.count = self.count + 1

  # cascadePressed
  #
  #     callback which is called when the cascade menu item is pressed. All windows are placed
  #     in a cascade way
    
  def cascadePressed(self) :
  
    self.mdi.cascadeSubWindows()

  # tiledPressed
  #
  #     function which is called from the menu item <tiled>. Windows are placed tiled on the screen
    
  def tiledPressed(self) :
      
    self.mdi.tileSubWindows()

# onTimeOut
#
#     callback wich is called on time outs of the timer
#     NOTE : mdiwindow is known ?
    
def onTimeOut() :
  mdiwindow.update()
  return

# main loop
      
if __name__ == '__main__' :

  app = QApplication(sys.argv)

  # try to connect to the media device
  
  input_devices = QMediaDevices.audioInputs()
  if not input_devices :
    QMessageBox.warning(None,"audio","Ther is no audio input device available.")

  # show the window
    
  mdiwindow = MDIWindow(input_devices[0])
  mdiwindow.show()

  # check device is connected
    
  # and timer

  timer = QTimer()
  timer.timeout.connect(onTimeOut)
  timer.start(100)
    
  # and return until exit

  sys.exit(app.exec())



    

    