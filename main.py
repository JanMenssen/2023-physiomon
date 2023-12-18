#
# main.py
#
#     this is the main file for the FysioMon project. Visualisation and storage of physiological
#     signals
#
# Modifications
#     15-dec-2023  JM  initial version

import sys
from PySide6.QtWidgets import QApplication, QMainWindow,QMdiArea, QMdiSubWindow, QTextEdit, QMenu, QMessageBox, QToolBar
from PySide6.QtGui import QAction
from PySide6.QtCore import QTimer
from PySide6.QtCharts import QChartView
from PySide6.QtMultimedia import QAudioFormat, QAudioSource, QMediaDevices
from statusbar import myStatusBar
from stripchart import stripChart
from devfysiodaq import devFysioDaq

#-jm port = "cu.BLTH"
#-jm port = "tty.BLTH"
#-jm port = "cu.Bluetooth-Incoming-Port"
#-jm port = "tty.Bluetooth-Incoming-Port"
#-jm port = "cu.usbmodem14201"
port = "tty.usbmodem101"

# define the MDI class

class MDIWindow(QMainWindow) :

  # constructor
  #
  #   - windows are created
  #   - menus are created
  #   - audio device is created and coupled (should be replaced by data from arduino)
    
  def __init__(self,audiodevice,device) :
    super().__init__()

    self.count = 0
    self.m_scope = []
    self.device = device

    self.mdi = QMdiArea()
    self.setCentralWidget(self.mdi)

    # create the toolbar

    toolbar = QToolBar("main toolbar")
    self.addToolBar(toolbar)

    startButton = QAction("start",self)
    startButton.setStatusTip("start/stop the program")
    startButton.triggered.connect(self.startPressed)
    toolbar.addAction(startButton)

    saveButton = QAction("save",self)
    saveButton.setStatusTip("save the measurement")
    saveButton.triggered.connect(self.savePressed)
    toolbar.addAction(saveButton)

    displayButton = QAction("display",self)
    displayButton.setStatusTip("edit the display settings")
    displayButton.triggered.connect(self.displayPressed)
    toolbar.addAction(displayButton)

    deviceButton = QAction("device",self)
    deviceButton.setStatusTip("edit the device settings")
    deviceButton.triggered.connect(self.devicePressed)
    toolbar.addAction(deviceButton)

    deviceInfoButton = QAction("info",self)
    deviceInfoButton.setStatusTip("device info")
    deviceButton.triggered.connect(self.devInfoPressed)
    toolbar.addAction(deviceInfoButton)

    # create the menu structure

    bar = self.menuBar()
    fileMenu = QMenu("&File", self)
    deviceMenu = QMenu("&Device", self)
    bar.addMenu(fileMenu)
    bar.addMenu(deviceMenu)

    newAction = QAction("New",self)
    newAction.triggered.connect(self.newPressed)
    fileMenu.addAction(newAction)

    cascadeAction = QAction("Cascade",self)
    cascadeAction.triggered.connect(self.cascadePressed)
    fileMenu.addAction(cascadeAction)

    tiledAction = QAction("Tiled",self)
    tiledAction.triggered.connect(self.tiledPressed)
    fileMenu.addAction(tiledAction)

    startAction = QAction("start",self)
    startAction.triggered.connect(self.startPressed)
    deviceMenu.addAction(startAction)

    devInfoAction = QAction("device &Info",self)
    devInfoAction.triggered.connect(self.devInfoPressed)
    deviceMenu.addAction(devInfoAction)

    # and the statusbar

    statusbar = myStatusBar()
    self.setStatusBar(statusbar)
    statusbar.setText("ready",3)

    self.setWindowTitle("FysioMon v1.01")

    # audio device

    self.name = audiodevice.description()

    m_formatAudio = QAudioFormat()
    m_formatAudio.setSampleRate(8000)
    m_formatAudio.setChannelCount(1)
    m_formatAudio.setSampleFormat(QAudioFormat.UInt8)

    self.m_audioInput = QAudioSource(audiodevice, m_formatAudio, self)
    self.m_ioDevice = self.m_audioInput.start()
    #-jm self.m_ioDevice.readyRead.connect(self.update)


  # update
  #
  #     this function updates the windows if there is data available
    
  def update(self) :
    
    data = self.m_ioDevice.readAll()
    if self.count > 0 :
      for i in range(self.count) :
        self.m_scope[i].update(data)

  # devicePressed
  #
  #     settings of the device are changed
        
  def devicePressed(self) :
    return
  
  # savePressed
  #
  #     measurement is stored

  def savePressed(self) :
    return
  
  # displayPressed
  #
  #     display settings are changed

  def displayPressed(self) :
    return
  
  # startPressed
  #
  #     the startstop is pressed, this toggles start stop of the device

  def startPressed(self) :

    started = device.isStarted()
    
    if (not started) :
      device.setStartStop(True)
      self.statusBar().setText("device started",5)
    else :
      device.setStartStop(False)
      self.statusBar().setText("device stopped",5)
   
    return

  # devInfoPressed
  #
  #     returns the device info

  def devInfoPressed(self) :
    dataStr = self.device.isConnected()
    self.statusBar().setText(dataStr,5)
    return
       
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

  # create the device
      
  device = devFysioDaq()
  device.initialise(port,1200)

  # show the window
    
  mdiwindow = MDIWindow(input_devices[0],device)
  mdiwindow.show()

  # create the statusbar
    
  statusbar = myStatusBar()
  mdiwindow.setStatusBar(statusbar)

  # check device is connected

  devInfoStr = device.isConnected()
  print(devInfoStr)
  statusbar.setText(devInfoStr,5)
    
  # and timer

  timer = QTimer()
  timer.timeout.connect(onTimeOut)
  timer.start(100)
    
  # and return until exit

  sys.exit(app.exec())



    

    