#
# measuredevice.py
#
#     abstract class for the devices used. This class should be used as superclass for the specific
#     devices
#
#   modifications
#     15-dec-2023   JM    initial version

from PySide6.QtCore import QSettings

TYPE_ANALOG = 1

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
    
    print("--> In measureDevice.iniRead")
     
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
      fields["gain"] = settings.value("gain",defaultValue = 1.0)
      fields["offset"] = settings.value("offset",defaultValue = 0.0)
      settings.endGroup()

      self.m_analogIn.append(fields.copy())

    # read the waveforms

    # read the numeric channels
    
    return
  

  # getSignalInfo
  #
  #   returns the necessary information for the data for the device. This is
  #     - gain
  #     - offset
  #     - channels that are used to store the data

  def getSignalInfo(self,type) :

    if type == TYPE_ANALOG :
      fields = self.m_analogIn
    
    return fields
  