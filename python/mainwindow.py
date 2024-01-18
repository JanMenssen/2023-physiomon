#
# mainwindow.py
#
#     this class is the mainWindow. it handles the graphical user interface and all other
#     functionality is included
#
#  modifications
#     12-jan-2024   JM    initial version

from PySide6.QtWidgets import QMainWindow,QMdiArea, QMenu, QToolBar, QWidget, QGridLayout, QPushButton, QLabel, QLineEdit
from PySide6.QtGui import QAction
from PySide6.QtCore import QTimer

from statusbar import statusBarNew
from settings import settings
#-jm from displays_mdi import displays
from displays_grid import displays
from channels import channels
from devPhysioDaq import devPhysioDaq

class mainWindow(QMainWindow) :

  # constructor
  #
  #   - windows are created
  #   - menus are created

    
  def __init__(self) :
    
    super().__init__()

    # create the MDU subwindows, this is only needed for the MDI implementation
    
    #-jm self.mdi = QMdiArea()
    #-jm self.setCentralWidget(self.mdi)

    # there is also a central widget implementation

    centralWidget = QWidget()
    self.setCentralWidget(centralWidget)
    
    # create the toolbar and the menu

    self.createToolBar()
    self.createMenu()
    
    # and the statusbar

    myStatusBar = statusBarNew()
    self.setStatusBar(myStatusBar)

    # read the general and specific settings

    self.m_settings = settings()
    deviceName = self.m_settings.iniRead()

    if (deviceName == "physiodaq") :    
      self.m_device = devPhysioDaq()
    
    self.m_device.iniRead(deviceName)
    self.m_device.initialise()

    # create the channels and display and configure the program

    #-jm self.m_displays = displays(self.mdi)

    self.m_displays = displays(centralWidget)
    self.m_channels = channels(5)

    self.configure()
    
    # set the timer

    self.m_timer = QTimer()
    self.m_timer.timeout.connect(self.onTimeOut)
    self.m_timer.start(100) 

    # and set ready

    self.setWindowTitle("PhysioMon v0.1")
    self.statusBar().setText("ready ...",5.0)

  # configure
  #
  #   configures the program, depending the settings read from the *.INI files or from the
  #   popup menu's
    
  def configure(self) :

    self.m_displays.configure(self.m_settings)
    self.m_device.configure(self.m_settings)
    self.m_channels.configure(self.m_settings,self.m_device)
  
    return
  
  # createMenu
  #
  #     the menu items are created
  
  def createMenu(self) :
    
    bar = self.menuBar()
    
    fileMenu = QMenu("&File", self)
    editMenu = QMenu("&Edit", self)
    helpMenu = QMenu("&Help", self)
 
    bar.addMenu(fileMenu)
    bar.addMenu(editMenu)
    bar.addMenu(helpMenu)

    startAction = QAction("Start",self)
    startAction.triggered.connect(self.onStart)
    fileMenu.addAction(startAction)

    saveAction = QAction("Save",self)
    saveAction.triggered.connect(self.onSave)
    fileMenu.addAction(saveAction)

    dispSettingsChangeAction = QAction("Display",self)
    dispSettingsChangeAction.triggered.connect(self.onDispSettingsChanged)
    editMenu.addAction(dispSettingsChangeAction)

    deviceSettingsChangeAction = QAction("Device",self)
    deviceSettingsChangeAction.triggered.connect(self.onDeviceSettingsChanged)
    editMenu.addAction(deviceSettingsChangeAction)

    PhysiomonHelpAction = QAction("PhysioMon Help",self)
    deviceSettingsChangeAction.triggered.connect(self.onPhysiomonHelp)
    helpMenu.addAction(PhysiomonHelpAction)

    return

  # createToolBar
  #
  #     In this function the toolbar is created. 
    
  def createToolBar(self) :

    toolbar = QToolBar("main toolbar")
    self.addToolBar(toolbar)

    # start

    startButton = QAction("start",self)
    startButton.setToolTip("start/stop the program")
    startButton.triggered.connect(self.onStart)
    toolbar.addAction(startButton)

    # save

    saveButton = QAction("save",self)
    saveButton.setToolTip("save the measurement")
    saveButton.triggered.connect(self.onSave)
    toolbar.addAction(saveButton)

    # device info

    deviceInfoButton = QAction("info",self)
    deviceInfoButton.setToolTip("get device info")
    deviceInfoButton.triggered.connect(self.onDeviceInfo)
    toolbar.addAction(deviceInfoButton)

    return
  
  # onTimeOut
  #
  #     is called when a timeout occurs at the timer

  def onTimeOut(self) :
    
    self.m_device.read(self.m_channels)
    self.m_displays.plot(self.m_channels) 
     
    return
  
  # devicePressed
  #
  #     settings of the device are changed
        
  def devicePressed(self) :
    return
  
  # onSave
  #
  #     measurement is stored

  def onSave(self) :
    return
  
  # onStart
  #
  #     the startstop is pressed, this toggles start stop of the device

  def onStart(self) :

    started = self.m_device.isStarted()

    if (not started) :
      self.m_device.setStartStop(True)
      self.statusBar().setText("device started",5)
    else :
      self.m_device.setStartStop(False)
      self.statusBar().setText("device stopped",5)
   
    return

  # onDeviceInfo
  #
  #     returns the device info

  def onDeviceInfo(self) :

    dataStr = self.m_device.isConnected()
    self.statusBar().setText(dataStr,5)
    return
       
  # onSave
  #
        
  def onSave(self) :
    
    return

  # onDeviceSettingsChanged
  #
  #     a popup is displayed which makes it possible to edit the device settings

  def onDeviceSettingsChanged(self) :
    
    return
  
  # onDispSettingsChanged
  #
  #     a popup is displayed which makes it possible to edit the device settings

  def onDispSettingsChanged(self) :
    
    return
  
  # onFysiomonHelp
  #
  #     help fpr fysiomon

  def onPhysiomonHelp(self) :
    
    return