#
# physiomon_settings
#
#     class containing the settings for the program
#
#   modifications
#     18-dec-2023   JM    initial version
#     11-feb-2024   JM    renamed to <physiomon_settings>

TYPE_ANALOG_IN = 1

COLOR_RED = 0
COLOR_GREEN = 1
COLOR_BLUE = 2
COLOR_CYAN = 3
COLOR_MAGENTA = 4
COLOR_YELLOW = 5
COLOR_BLACK = 6
COLOR_WHITE = 7

from PySide6.QtCore import QSettings

class physiomon_settings() :

  # constructor

  def __init__(self) :
    
    self.m_settings = QSettings(QSettings.IniFormat,QSettings.UserScope,"JanSoft","physiomon")

    #-jm self.m_general = {"numchan" : 1, "numdisp" : 1, "device" :""}

    self.m_numchan = 0
    self.m_numdisp = 0
    self.m_numstore = 0
    self.m_device = ""

    self.m_channels = []
    self.m_displays = []
    self.m_stores = []
    self.m_events = []

    self.m_settings.setFallbacksEnabled(False)
    
    return

  # getEventString
  #
  #   returns the event string belonging to the event

  def getEventString(self,key) :
  
    return self.m_events[key] 
  
  # iniRead
  #
  #   read the *.INI file

  def iniRead(self) :

    self._readGeneral()
    self._readChannels()
    self._readDisplaySettings()
    self._readStoreSettings()
    self._readEventSettings()

  #-jm  return self.m_general["device"]
    return self.m_device
  
  # iniWrite
  #
  #     writes the current configuration

  def iniWrite(self) :

    self.m_settings.beginGroup("general")
    self.m_settings.setValue("numchan",self.m_numchan)
    self.m_settings.setValue("numdisp",self.m_numdisp)
                                         
    self.endGroup()


    return
  
  # _readGeneral
  #
  #     private method to read the general settings from the *.ini file

  def _readGeneral(self) :

    self.m_settings.beginGroup("algemeen")
    self.m_numchan = int(self.m_settings.value("numchan",defaultValue = 1))
    self.m_numdisp = int(self.m_settings.value("numdisp",1))
    self.m_numstore = int(self.m_settings.value("numstore",1))
    self.m_device = self.m_settings.value("device","")
    self.m_settings.endGroup()
    
    return
  
  # _readChannels
  #
  #     private method to read the settings for each channel

  def _readChannels(self) :

    channel = {"name" : "", "type" : 0, "source" : 0, "display" : 0, "precision" : 1, "color" : COLOR_GREEN}
    self.m_channels = []

    for i in range(self.m_numchan) :  
      keyName = "channel " + str(i+1)
      
      self.m_settings.beginGroup(keyName)
      channel["name"] = self.m_settings.value("name",1)
      channel["source"] = int(self.m_settings.value("source", defaultValue = 0))
      channel["display"] = int(self.m_settings.value("display",defaultValue = 0))
      channel["precision"] = int(self.m_settings.value("precision",defaultValue = 1))
      
      typeSignal = self.m_settings.value("type",defaultValue = "analog in")
      if (typeSignal == 'analog in') : channel["type"] = TYPE_ANALOG_IN
   
      color = self.m_settings.value("color", defaultValue = "green")
      if (color.lower() == "red") : channel["color"] = COLOR_RED
      if (color.lower() == "green") : channel["color"] = COLOR_GREEN
      if (color.lower() == "blue") : channel["color"] = COLOR_BLUE
      if (color.lower() == "cyan") : channel["color"] = COLOR_CYAN
      if (color.lower() == "magenta") : channel["color"] = COLOR_MAGENTA
      if (color.lower() == "yellow") : channel["color"] = COLOR_YELLOW
      if (color.lower() == "black") : channel["color"] = COLOR_BLACK
      if (color.lower() == "white") : channel["color"] = COLOR_WHITE
      
      self.m_settings.endGroup()
      
      self.m_channels.append(channel.copy())

    return

  # _readDisplaySettings
  #
  #     private method to read the display settings

  def _readDisplaySettings(self) :

    display = {"top" : 0, "left" : 0, "width" : 0, "height" : 0, "ymin" : 0, "ymax" : 0, "timescale" : 10, "mode" : ""}
    self.m_displays = []

    for i in range(self.m_numdisp) :

      name = "display " + str(i+1)

      self.m_settings.beginGroup(name)
      display["top"] = float(self.m_settings.value("top",0.0))
      display["left"] = float(self.m_settings.value("left",0.0))
      display["width"] = float(self.m_settings.value("width",0.0))
      display["height"] = float(self.m_settings.value("height",0.0))
      display["ymin"] = float(self.m_settings.value("ymin",0.0))
      display["ymax"] = float(self.m_settings.value("ymax",0.0))
      display["timescale"] = float(self.m_settings.value("timescale",10))
      display["mode"] = self.m_settings.value("update mode","scope")
      self.m_settings.endGroup()

      self.m_displays.append(display.copy())
    
    return  
  
  # readStoreSettings
  #
  #     read the store information (name of groups)

  def _readStoreSettings(self) :

    store = {"groupname" : ""}
    self.m_stores = []

    for i in range(self.m_numstore) :  
      
      keyName = "store " + str(i+1)
      
      self.m_settings.beginGroup(keyName)
      store["groupname"] = self.m_settings.value("groupname",1)
      self.m_settings.endGroup()
      
      self.m_stores.append(store.copy())

    return
  
  #  readEventSettings
  #
  #     private method to read the text for the events

  def _readEventSettings(self) :

    self.m_settings.beginGroup("events")
    for i in range(1,11) :
      event = self.m_settings.value(str(i),"event " + str(i))
      self.m_events.append(event)
    self.m_settings.endGroup()
    return
