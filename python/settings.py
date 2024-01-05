#
# settings
#
#     class containing the settings for the program
#
#   modifications
#     18-dec-2023   JM    initial version

TYPE_ANALOG_IN = 1

from PySide6.QtCore import QSettings

class settings(QSettings) :

  # constructor

  def __init__(self) :
    super().__init__(QSettings.IniFormat,QSettings.UserScope,"JanSoft","fysiomon")

    self.m_general = {"numchan" : 1, "numdisp" : 1, "device" :""}
    self.m_channels = []
    self.m_displays = []
    self.m_events = []

    self.setFallbacksEnabled(False)
    
    return


  # initialise
  #
  #     sets the *.ini file
  #     Note : this is curretly an empty method in Python/C but due to compatibiltiy with
  #            labView it is kept

  def initialise(self) :
    return
  

  # iniRead
  #
  #   read the *.INI file

  def iniRead(self) :

    self._readGeneral()
    self._readChannels()
    self._readDisplaySettings()
    self._readEventSettings()

    return self.m_general["device"]
  
  # getDisplayInfo
  #
  #     returns the position and the scale setting for the display with index i

  def getDisplayInfo(self,i) :

    position = {"top" : 0,"left" : 0, "height" : 0, "width" : 0}
    scale = {"ymin" : 0, "ymax" : 0, "time" : 0}

    position["top"] = self.m_displays[i]["top"]
    position["left"] = self.m_displays[i]["left"]
    position["height"] = self.m_displays[i]["height"]
    position["width"] = self.m_displays[i]["width"]   

    scale["ymin"] = self.m_displays[i]["ymin"]
    scale["ymax"] = self.m_displays[i]["ymax"]
    scale["time"] = self.m_displays[i]["timescale"]
    
    return position,scale

  # iniWrite
  #
  #     writes the current configuration

  def iniWrite(self) :

    self.beginGroup("general")
    self.setValue("numchan",self.general["numchan"])
    self.setValue("numdisp",self.general["numdisp"])
                                         
    self.endGroup()


    return
  
  # _readGeneral
  #
  #     private method to read the general settings from the *.ini file

  def _readGeneral(self) :

    self.beginGroup("algemeen")
    self.m_general["numchan"] = int(self.value("numchan",defaultValue = 1))
    self.m_general["numdisp"] = int(self.value("numdisp",1))
    self.m_general["device"] = self.value("device","")
    self.endGroup()

    return
  
  # _readChannels
  #
  #     private method to read the settings for each channel

  def _readChannels(self) :

    channel = {"name" : "", "type" : 0, "source" : 0, "display" : 0}
    self.m_channels = []

    numchan = self.m_general["numchan"]
    for i in range(numchan) :
      
      keyName = "channel " + str(i+1)
      
      self.beginGroup(keyName)
      channel["name"] = self.value("name",1)
      typeSignal = self.value("type",defaultValue = "analog in")
      if (typeSignal == 'analog in') :
        channel["type"] = TYPE_ANALOG_IN
      channel["source"] = int(self.value("source", defaultValue = 0))
      channel["display"] = int(self.value("display",defaultValue = 0))
      self.endGroup()
      
      self.m_channels.append(channel.copy())

    return

  # _readDisplaySettings
  #
  #     private method to read the display settings

  def _readDisplaySettings(self) :

    display = {"top" : 0, "left" : 0, "width" : 0, "height" : 0, "ymin" : 0, "ymax" : 0, "timescale" : 10}
    self.m_displays = []

    numdisp = self.m_general["numdisp"]
    for i in range(numdisp) :

      name = "display " + str(i+1)

      self.beginGroup(name)
      display["top"] = float(self.value("top",0.0))
      display["left"] = float(self.value("left",0.0))
      display["width"] = float(self.value("width",0.0))
      display["height"] = float(self.value("height",0.0))
      display["ymin"] = float(self.value("ymin",0.0))
      display["ymax"] = float(self.value("ymax",0.0))
      display["timescale"] = float(self.value("timescale",10))
      self.endGroup()

      self.m_displays.append(display.copy())
    
    return  
  
  # _readEventSettings
  #
  #     private method to read the text for the events

  def _readEventSettings(self) :

    self.beginGroup("events")
    for i in range(1,10) :
      event = self.value(str(i),"")
      self.m_events.append(event)
    self.endGroup()
    return
