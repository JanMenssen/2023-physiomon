#
# measuredevice.py
#
#     abstract class for the devices used. This class should be used as superclass for the specific
#     devices
#
#   modifications
#     15-dec-2023   JM    initial version

from PySide6.QtCore import QSettings

TYPE_ANALOG_IN = 1

class measureDevice() :

  # constructor

  def __init__(self) :
    self.m_started = False
    return
  
  # initialise
  #
  #   initialises this dummy device, nothing is done

  def initialise(self) :
    return
  
  
  # isStarted
  #
  #   this function returns the started state

  def isStarted(self) :
    return self.m_started
  

  # setStartStop
  #
  #   this function sets the start/stop state of the device

  def setStartStop(self,mode) :
    self.m_started = mode
    return
  

  # iniRead
  #
  #   read the standard values 
  #     - analog in
  #     - numeric in
  #     - waveform in 

  def iniRead(self,name) :
        
    settings = QSettings(QSettings.IniFormat,QSettings.UserScope,"JanSoft",name)

    settings.beginGroup("algemeen")
    nrAnalogIn = int(settings.value("numAnalogIn",defaultValue = 0))
    nrWaveIn = int(settings.value("numWaveformIn",defaultValue = 0))
    nrNumericIn = int(settings.value("numNumericIn",defaultValue = 0))
    settings.endGroup()

    fields = {"name" :"", "gain" : 1.0, "offset" : 0.0, "channels" : []}
    self.m_analogIn = []

    # read the analog channels

    for i in range(nrAnalogIn) :

      keyName = "analog_in " + str(i+1)
      
      settings.beginGroup(keyName)
      fields["name"] = settings.value("name",1)
      fields["sampleRate"] = float(settings.value("frequency",defaultValue = 1.0))
      fields["gain"] = float(settings.value("gain",defaultValue = 1.0))
      fields["offset"] = float(settings.value("offset",defaultValue = 0.0))
      settings.endGroup()

      self.m_analogIn.append(fields.copy())

    # read the waveforms

    # read the numeric channels
    
    return
  
  # configure
  #
  #   configures the device, using values from settings

  def configure(self,settings) :
    
    # first clear the channels

    for analog in self.m_analogIn : analog["channels"] = []

    # and then build up a new list
    
    numchan = settings.m_numchan
    for i in range(numchan) :

      source = settings.m_channels[i]["source"]
      
      # tmp is needed, else channels for all analog inpunt is updated
      
      if (settings.m_channels[i]["type"] == TYPE_ANALOG_IN) :
        tmp = self.m_analogIn[source]["channels"].copy()
        tmp.append(i)
        self.m_analogIn[source]["channels"] = tmp
      
      #-jm NOTE, should be implemented
      #-jm   
      #-jm if (settings.m_channels[i]["type"] == TYPE_NUMERIC) :
      #-jm  self.m_analogIn[source]["channels"].append(i)

    return

  