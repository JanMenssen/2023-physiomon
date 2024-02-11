#
# mainwindow.py
#
#     this class is the mainWindow. it handles the graphical user interface and all other
#     functionality is included
#
#  modifications
#     12-jan-2024   JM    initial version

from PySide6.QtWidgets import QMainWindow, QMenu, QToolBar, QWidget, QToolButton
from PySide6.QtGui import QAction, QShortcut, QKeySequence, QIcon
from PySide6.QtCore import QTimer, Qt, QObject, QSize

from statusbar import statusBarNew
from settings import settings
from displays import displays
from channels import channels
from devphysiodaq import devPhysioDaq
from devphysiodaq_dialog import devPhsyioDaq_dialog
from settings_dialog import settings_dialog
from physiomon_icons import qInitResources


MAX_CHANNELS = 5

class mainWindow(QMainWindow) :

  # constructor
  #
  #   - windows are created
  #   - menus are created

    
  def __init__(self,width,height) :
    
    super().__init__()
    self.resize(width,height)

    # create the MDU subwindows, this is only needed for the MDI implementation
    
    #-jm self.mdi = QMdiArea()
    #-jm self.setCentralWidget(self.mdi)

    # there is also a central widget implementation

    centralWidget = QWidget()
    self.setCentralWidget(centralWidget)
    
    # create the toolbar and the menu

    self.createToolBar()
    self.createMenu()
    self.createEventKeys()

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
    self.m_channels = channels(MAX_CHANNELS)

    self.onConfigure()
    
    # set the timer

    self.m_timer = QTimer()
    self.m_timer.timeout.connect(self.onTimeOut)
    self.m_timer.start(100) 

    # and set ready

    self.setWindowTitle("PhysioMon v3.01")
    self.statusBar().setText("ready ...",5.0)

  # onConfigure
  #
  #   configures the program, depending the settings read from the *.INI files or from the
  #   popup menu's
    
  def onConfigure(self) :

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

    settingsChangeAction = QAction("General Settings ",self)
    settingsChangeAction.triggered.connect(self.onGeneralSettingsChanged)
    editMenu.addAction(settingsChangeAction)

    deviceSettingsChangeAction = QAction("Device Settings ",self)
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
    toolbar.setIconSize(QSize(24,24))
    toolbar.setFixedHeight(60)
    self.addToolBar(toolbar)

    # start

    startAction = QAction(self)
    startAction.setIcon(QIcon(":/icons/play_13794082.png"))
    startAction.setText("start")
    startAction.setToolTip("start/stop the program")
    startAction.triggered.connect(self.onStart)
   
    startButton = QToolButton()
    startButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    startButton.setDefaultAction(startAction)
    
    toolbar.addWidget(startButton)

    # save

    saveAction = QAction(self)
    saveAction.setToolTip("save the measurement")
    saveAction.setIcon(QIcon(":/icons/adjust_6048035.png"))
    saveAction.setText("save")
    saveAction.triggered.connect(self.onSave)
    
    saveButton = QToolButton()
    saveButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    saveButton.setDefaultAction(saveAction)

    toolbar.addWidget(saveButton)

    # change general settings

    generalAction = QAction(self)
    generalAction.setToolTip("change general settings")
    generalAction.setIcon(QIcon(":/icons/adjust_6048035.png"))
    generalAction.setText("general")
    generalAction.triggered.connect(self.onGeneralSettingsChanged)
  
    generalButton = QToolButton()
    generalButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    generalButton.setDefaultAction(generalAction)
    
    toolbar.addWidget(generalButton)

    # change device settings

    deviceAction = QAction(self)
    deviceAction.setToolTip("change device settings")
    deviceAction.setIcon(QIcon(":/icons/repair_5064596.png"))
    deviceAction.setText("device")
    deviceAction.triggered.connect(self.onDeviceSettingsChanged)

    deviceButton = QToolButton()
    deviceButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    deviceButton.setDefaultAction(deviceAction)
    
    toolbar.addWidget(deviceButton)

    # device info

    infoAction = QAction(self)
    infoAction.setToolTip("get device info")
    infoAction.setIcon(QIcon(":/icons/stop_9503472.png"))
    infoAction.setText("info")
    infoAction.triggered.connect(self.onDeviceInfo)
  
    infoButton = QToolButton()
    infoButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    infoButton.setDefaultAction(infoAction)
    
    toolbar.addWidget(infoButton)

    return
  
  # createEventKeys
  #
  #     sets the function kesy F1-F10 for an event


  def createEventKeys(self) :

    self.keyF1 = QShortcut(QKeySequence(Qt.Key_F1),self)
    self.keyF1.activated.connect(self.onEvent)

    self.keyF2 = QShortcut(QKeySequence(Qt.Key_F2),self)
    self.keyF2.activated.connect(self.onEvent)

    self.keyF3 = QShortcut(QKeySequence(Qt.Key_F3),self)
    self.keyF3.activated.connect(self.onEvent)

    self.keyF4 = QShortcut(QKeySequence(Qt.Key_F4),self)
    self.keyF4.activated.connect(self.onEvent)

    self.keyF5 = QShortcut(QKeySequence(Qt.Key_F5),self)
    self.keyF5.activated.connect(self.onEvent)

    self.keyF6 = QShortcut(QKeySequence(Qt.Key_F6),self)
    self.keyF6.activated.connect(self.onEvent)

    self.keyF7 = QShortcut(QKeySequence(Qt.Key_F7),self)
    self.keyF7.activated.connect(self.onEvent)

    self.keyF8 = QShortcut(QKeySequence(Qt.Key_F8),self)
    self.keyF8.activated.connect(self.onEvent)

    self.keyF9 = QShortcut(QKeySequence(Qt.Key_F9),self)
    self.keyF9.activated.connect(self.onEvent)

    self.keyF10 = QShortcut(QKeySequence(Qt.Key_F10),self)
    self.keyF10.activated.connect(self.onEvent)
    
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
    
    self.statusBar().setText("device settings modified ...",3)
    
    dlgBox = devPhsyioDaq_dialog(self.m_device.m_analogIn)
    if dlgBox.exec() :
      self.m_device.m_analogIn = dlgBox.getAnalogInfo()
      self.statusBar().setText("display settings are modified ...",3)
    else : 
      self.statusBar().setText("display settings not modified ...",3)
      
  # onGeneralSettingsChanged
  #
  #     a popup is displayed which makes it possible to edit the device settings

  def onGeneralSettingsChanged(self) :
    
    self.statusBar().setText("general settings are modified changed",2)
    
    channels = self.m_settings.m_channels
    displays = self.m_settings.m_displays
    events = self.m_settings.m_events
    analog = self.m_device.m_analogIn

    dlgBox = settings_dialog(channels,displays,events,analog)
    if dlgBox.exec() :
      self.m_device.m_channels,self.m_settings.m_displays,self.m_settings.m_events = dlgBox.getModifiedValues()
      self.statusBar().setText("general settings are modified ...",3)
    else : 
      self.statusBar().setText("general settings not modified ...",3)
   
  # onEvent
  #
  #     function is called when an event key is pressed

  def onEvent(self) :
    
    eventStr = "no event found"
    # get the event string

    if (QObject.sender(self) == self.keyF1) :
      eventStr = self.m_settings.getEventString(0)
    if (QObject.sender(self) == self.keyF2) :
      eventStr = self.m_settings.getEventString(1)
    if (QObject.sender(self) == self.keyF3) :
      eventStr = self.m_settings.getEventString(2)
    if (QObject.sender(self) == self.keyF4) :
      eventStr = self.m_settings.getEventString(3)
    if (QObject.sender(self) == self.keyF5) :
      eventStr = self.m_settings.getEventString(4)
    if (QObject.sender(self) == self.keyF6) :
      eventStr = self.m_settings.getEventString(5)
    if (QObject.sender(self) == self.keyF7) :
      eventStr = self.m_settings.getEventString(6)
    if (QObject.sender(self) == self.keyF8) :
      eventStr = self.m_settings.getEventString(7)
    if (QObject.sender(self) == self.keyF9) :
      eventStr = self.m_settings.getEventString(8)
    if (QObject.sender(self) == self.keyF10) :
      eventStr = self.m_settings.getEventString(9)

    # and display it andd store the event

    self.statusBar().setText(eventStr,5)
    return

  # onFysiomonHelp
  #
  #     help fpr fysiomon

  def onPhysiomonHelp(self) :
    
    return