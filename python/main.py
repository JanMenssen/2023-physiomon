#
# main.py
#
#     this is the main file for the FysioMon project. Visualisation and storage of physiological
#     signals
#
# Modifications
#     15-dec-2023  JM  initial version

import sys
from PySide6.QtWidgets import QApplication, QMainWindow,QMdiArea, QMenu, QToolBar
from PySide6.QtGui import QAction
from PySide6.QtCore import QTimer
from statusbar import StatusBar
from devfysiodaq import devFysioDaq
from measuredevice import measureDevice
from settings import settings
from displays import displays
from channels import channels

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
    
  def __init__(self,device) :
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
    deviceInfoButton.triggered.connect(self.devInfoPressed)
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

    startAction = QAction("start",self)
    startAction.triggered.connect(self.startPressed)
    deviceMenu.addAction(startAction)

    devInfoAction = QAction("device &Info",self)
    devInfoAction.triggered.connect(self.devInfoPressed)
    deviceMenu.addAction(devInfoAction)

    # and the statusbar

    myStatusbar = StatusBar()
    self.setStatusBar(myStatusbar)
    myStatusbar.setText("ready",3)

    self.setWindowTitle("FysioMon v1.01")

  # init
  #
  #     this is the initialisation part of the mainWindow
    
  def init(self) :
    print("in init")
    return
  

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

    started = myDevice.isStarted()
    
    if (not started) :
      myDevice.setStartStop(True)
      self.statusBar().setText("device started",5)
    else :
      myDevice.setStartStop(False)
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
        
  def newPressed(self) :
    return

# configure
#
#     configures the whole setup
    
def init(settings) :
  
  myDisplay.configure(settings)
  myDevice.configure(settings)
  myChannels.configure(settings,myDevice)

  return

# onTimeOut
#
#     callback wich is called on time outs of the timer
#     NOTE : mdiwindow is known ?
    
def onTimeOut() :
 
  # get the data and write to display and data store         
  
  myDevice.read(myChannels)    
  myDisplay.plot(myChannels)
  
  #-jm datastore.write(data)
  
  return

# main loop
      
if __name__ == '__main__' :

  app = QApplication(sys.argv)

  # read the settings 
  
  settings = settings()
  settings.initialise()
  deviceName = settings.iniRead()

  # create the device
  
  myDevice = measureDevice()
  if (deviceName == "fysiodaq") :    
    myDevice = devFysioDaq()
    
  myDevice.iniRead(deviceName)
  myDevice.initialise()
  myDevice.setSampleRate(25)

  # create the graphical structure

  mdiwindow = MDIWindow(myDevice)
  myDisplay = displays(mdiwindow.mdi)
  
  # create the channels

  myChannels = channels(5)
  
  # and configure

  init(settings)

  # and show

  mdiwindow.show()

  # create the statusbar
    
  myStatusbar = StatusBar()
  mdiwindow.setStatusBar(myStatusbar)
  
  # check device is connected

  #-jm devInfoStr = device.isConnected()
  #-jm print(devInfoStr)
  #-jm statusbar.setText(devInfoStr,5)
    
  # and timer

  timer = QTimer()
  timer.timeout.connect(onTimeOut)
  timer.start(100)
    
  # and return until exit

  sys.exit(app.exec())



    

    