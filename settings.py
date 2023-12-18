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
    super().__init__(QSettings.IniFormat,QSettings.UserScope,"JanSoft","fysiomon")

    self.general = {"numchan" : 1, "numdisp" : 1, "device" :""}
    self.channels = []
    self.displays = []
    self.events = []

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

    return self.general["device"]
  
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
    self.general["numchan"] = int(self.value("numchan",defaultValue = 1))
    self.general["numdisp"] = int(self.value("numdisp",1))
    self.general["device"] = self.value("device","")
    self.endGroup()

    return
  
  # _readChannels
  #
  #     private method to read the settings for each channel

  def _readChannels(self) :

    channel = {"name" : "", "type" : 0, "source" : 0, "display" : 0}

    numchan = self.general["numchan"]
    for i in range(numchan) :
      
      keyName = "channel " + str(i+1)
      
      self.beginGroup(keyName)
      channel["name"] = self.value("name",1)
      channel["type"] = self.value("type",defaultValue = "analog in")
      channel["source"] = int(self.value("source", defaultValue = 0))
      channel["display"] = int(self.value("display",defaultValue = 0))
      self.endGroup()
      
      self.channels.append(channel)

    return

  # _readDisplaySettings
  #
  #     private method to read the display settings

  def _readDisplaySettings(self) :

    display = {"top" : 0, "left" : 0, "width" : 0, "height" : 0, "ymin" : 0, "ymax" : 0, "timescale" : 10}

    numdisp = self.general["numdisp"]
    for i in range(numdisp) :

      name = "display " + str(i+1)

      self.beginGroup(name)
      display["top"] = self.value("top",0.0)
      display["left"] = self.value("left",0.0)
      display["width"] = self.value("width",0.0)
      display["height"] = self.value("height",0.0)
      display["ymin"] = self.value("ymin",0.0)
      display["ymax"] = self.value("ymax",0.0)
      display["timescale"] = self.value("timescale",10)
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
