#
# settings
#
#     class containing the settings for the program
#
#   modifications
#     18-dec-2023   JM    initial version

from PySide6.QtCore import QSettings

class settings(QSettings) :

  # constructor

  def __init__(self) :
    super().__init__("FysioMon","main")

    self.general = {"numchan" : 1, "numdisp" : 1, "device" :""}
    self.channels = []
    self.displays = []
    self.events = []
    
    self.setDefaultFormat()
    
    return
  
  # iniRead
  #
  #   read the *.INI file

  def iniRead(self) :

    self._readGeneral(self)
    self._readChannels(self)
    self._readDisplaySettings(self)
    self._readEventSettings(self)

    return
  
  # _readGeneral
  #
  #     private method to read the general settings from the *.ini file

  def _readGeneral(self) :

    self.beginGroup('general')
    self.general["numchan"] = self.value("numchan",1).toInt()
    self.general["numdisp"] = self.value("numdisp",1).toInit()
    self.general["device"] = self.value("device","")
    self.endGroup()

    return
  
  # _readChannels
  #
  #     private method to read the settings for each channel

  def _readChannels(self) :

    channel = {"name" : "", "type" : 0, "source" : 0, "display" : 0}

    for i in range(self.numchan) :
      
      name = "channel" + str(i+1)

      self.beginGroup(name)
      channel["name"] = self.value("name",1)
      type = self.value("type","analog")
      if (type == "analog") :
        channel["type"] = 1
      if (type == "numeric") :
        channel["type"] = 2
      channel["source"] = self.value("source", 0)
      channel["display"] = self.value("display")
      self.endGroup()
      
      self.channels.append(channel)

    return

  # _readDisplaySettings
  #
  #     private method to read the display settings

  def _readDisplaySettings(self) :

    display = {"top" : 0, "left" : 0, "width" : 0, "height" : 0, "ymin" : 0, "ymax" : 0, "timescale" : 10}

    for i in range(self.numdisp) :

      name = "display" + str(i+1)

      self.beginGroup(name)
      display["top"] = self.value("top",0).toFloat()
      display["left"] = self.value("left",0).toFloat()
      display["widht"] = self.value("width",0).toFloat()
      display["height"] = self.value("height",0).toFloat()
      display["ymin"] = self.value("ymin",0).toFloat()
      display["ymax"] = self.value("ymax",0).toFloat()
      display["timescale"] = self.value("timescale",10).toInt()
      self.endGroup()

      self.displays.append(display)

    return  
  
  # _readEventSettings
  #
  #     private method to read the text for the events

  def _readEventSettings(self) :

    self.beginGroup("events")
    for i in range(1,10) :
      event = self.value(str(i),"")
      self.events.append(event)
    self.endGroup()
    return
