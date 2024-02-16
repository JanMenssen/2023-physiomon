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
from physiomon_settings import physiomon_settings
from physiomon_displays import physiomon_displays
from physiomon_channels import physiomon_channels
from devphysiodaq import devPhysioDaq
from devphysiodaq_dialog import devPhsyioDaq_dialog
from settings_dialog import settings_dialog
from physiomon_icons import qInitResources


MAX_CHANNELS = 5
ICON_FIXED_WIDTH = 40
ICON_SIZE = 20
TIMER_PERIOD = 100

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

    self.m_settings = physiomon_settings()
    deviceName = self.m_settings.iniRead()

    if (deviceName == "physiodaq") :    
      self.m_device = devPhysioDaq()
    
    self.m_device.iniRead(deviceName)
    self.m_device.initialise()

    # create the channels and display and configure the program

    #-jm self.m_displays = displays(self.mdi)

    self.m_displays = physiomon_displays(centralWidget)
    self.m_channels = physiomon_channels(5)

    self.onConfigure()
    
    # set the timer

    self.m_timer = QTimer()
    self.m_timer.timeout.connect(self.onTimeOut)
  
    # and set ready

    self.setWindowTitle("PhysioMon v3.01")
    self.statusBar().setText("ready ...",3.0)

  # onConfigure
  #
  #   configures the program, depending the settings read from the *.INI files or from the
  #   popup menu's
    
  def onConfigure(self) :

    self.m_device.configure(self.m_settings)
    self.m_channels.configure(self.m_settings,self.m_device)
    self.m_displays.configure(self.m_settings,self.m_channels)

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

    self.m_startMenuAction = QAction("Start",self)
    self.m_startMenuAction.triggered.connect(self.onStart)
    fileMenu.addAction(self.m_startMenuAction)

    self.m_saveMenuAction = QAction("Save",self)
    self.m_saveMenuAction.triggered.connect(self.onSave)
    fileMenu.addAction(self.m_saveMenuAction)

    self.m_generalMenuAction = QAction("General Settings ",self)
    self.m_generalMenuAction.triggered.connect(self.onGeneralSettingsChanged)
    editMenu.addAction(self.m_generalMenuAction)

    self.m_deviceMenuAction = QAction("Device Settings ",self)
    self.m_deviceMenuAction.triggered.connect(self.onDeviceSettingsChanged)
    editMenu.addAction(self.m_deviceMenuAction)

    self.m_physiomonHelpMenuAction = QAction("PhysioMon Help",self)
    self.m_physiomonHelpMenuAction.triggered.connect(self.onPhysiomonHelp)
    helpMenu.addAction(self.m_physiomonHelpMenuAction)

    return

  # createToolBar
  #
  #     In this function the toolbar is created. 
    
  def createToolBar(self) :

    toolbar = QToolBar("main toolbar")
    toolbar.setIconSize(QSize(ICON_SIZE,ICON_SIZE))
    toolbar.setFixedHeight(60)
    self.addToolBar(toolbar)

    # start

    self.m_startButtonAction = QAction(self)
    self.m_startButtonAction.setIcon(QIcon(":/icons/play_13794082.png"))
    self.m_startButtonAction.setText("start")
    self.m_startButtonAction.setToolTip("start/stop the program")
    self.m_startButtonAction.triggered.connect(self.onStart)
   
    startButton = QToolButton()
    startButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    startButton.setDefaultAction(self.m_startButtonAction)
    startButton.setFixedWidth(ICON_FIXED_WIDTH)

    toolbar.addWidget(startButton)

    # save

    self.m_saveButtonAction = QAction(self)
    self.m_saveButtonAction.setToolTip("save the measurement")
    self.m_saveButtonAction.setIcon(QIcon(":/icons/saving-content_11753556.png"))
    self.m_saveButtonAction.setText("save")
    self.m_saveButtonAction.triggered.connect(self.onSave)
    
    saveButton = QToolButton()
    saveButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    saveButton.setDefaultAction(self.m_saveButtonAction)
    saveButton.setFixedWidth(ICON_FIXED_WIDTH)

    toolbar.addWidget(saveButton)

    # change general settings

    self.m_generalButtonAction = QAction(self)
    self.m_generalButtonAction.setToolTip("change general settings")
    self.m_generalButtonAction.setIcon(QIcon(":/icons/adjust_6048035.png"))
    self.m_generalButtonAction.setText("general")
    self.m_generalButtonAction.triggered.connect(self.onGeneralSettingsChanged)
  
    generalButton = QToolButton()
    generalButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    generalButton.setDefaultAction(self.m_generalButtonAction)
    generalButton.setFixedWidth(ICON_FIXED_WIDTH) 

    toolbar.addWidget(generalButton)

    # change device settings

    self.m_deviceButtonAction = QAction(self)
    self.m_deviceButtonAction.setToolTip("change device settings")
    self.m_deviceButtonAction.setIcon(QIcon(":/icons/repair_5064596.png"))
    self.m_deviceButtonAction.setText("device")
    self.m_deviceButtonAction.triggered.connect(self.onDeviceSettingsChanged)

    deviceButton = QToolButton()
    deviceButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    deviceButton.setDefaultAction(self.m_deviceButtonAction)
    deviceButton.setFixedWidth(ICON_FIXED_WIDTH)
    
    toolbar.addWidget(deviceButton)

    # device info

    self.m_infoButtonAction = QAction(self)
    self.m_infoButtonAction.setToolTip("get device info")
    self.m_infoButtonAction.setIcon(QIcon(":/icons/report_4517968.png"))
    self.m_infoButtonAction.setText("info")
    self.m_infoButtonAction.triggered.connect(self.onDeviceInfo)
  
    infoButton = QToolButton()
    infoButton.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
    infoButton.setDefaultAction(self.m_infoButtonAction)
    infoButton.setFixedWidth(ICON_FIXED_WIDTH)  
    
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

      # start the device, change icon and disable menu and toolbar items

      self.m_startButtonAction.setIcon(QIcon(":/icons/stop_9503472.png"))
      self.m_startButtonAction.setText("stop")
      self.m_startMenuAction.setText("Stop")
                                   
      self.m_generalButtonAction.setDisabled(True)
      self.m_deviceButtonAction.setDisabled(True)
      self.m_infoButtonAction.setDisabled(True)

      self.m_generalMenuAction.setDisabled(True)
      self.m_deviceMenuAction.setDisabled(True)
 
      self.m_device.setStartStop(True)
      self.m_timer.start(TIMER_PERIOD) 

      self.statusBar().setText("device started",5)

    else :
      
      self.m_startButtonAction.setIcon(QIcon(":/icons/play_13794082.png"))
      self.m_startButtonAction.setText("tart")
      self.m_startMenuAction.setText("Start")

      self.m_generalButtonAction.setDisabled(False)
      self.m_deviceButtonAction.setDisabled(False)
      self.m_infoButtonAction.setDisabled(False)
      
      self.m_generalMenuAction.setDisabled(False)
      self.m_deviceMenuAction.setDisabled(False)

      self.m_device.setStartStop(False)
      self.m_timer.stop()

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
    
    self.statusBar().setText("edit device settings ...",3)
    
    dlgBox = devPhsyioDaq_dialog(self.m_device.m_analogIn)
    if dlgBox.exec() :
      self.m_device.m_analogIn = dlgBox.getAnalogInfo()
      self.statusBar().setText("changed settings are saved ...",3)
      self.onConfigure()
    else : 
      self.statusBar().setText("changed settings not saved ...",3)
      
  # onGeneralSettingsChanged
  #
  #     a popup is displayed which makes it possible to edit the device settings

  def onGeneralSettingsChanged(self) :
    
    self.statusBar().setText("edit general settings ... ",2)
    
    channels = self.m_settings.m_channels
    displays = self.m_settings.m_displays
    events = self.m_settings.m_events
    analog = self.m_device.m_analogIn

    dlgBox = settings_dialog(channels,displays,events,analog)
    if dlgBox.exec() :
      self.m_device.m_channels,self.m_settings.m_displays,self.m_settings.m_events = dlgBox.getModifiedValues()
      self.statusBar().setText("changed ettings are saved ...",3)
      self.onConfigure()
    else : 
      self.statusBar().setText("changed settings not saved ...",3)
   
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