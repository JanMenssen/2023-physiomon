# 
# devFysioDaq
#
#     driver for the <FysioDaq> device, an Arduino that samples analog ports and transfers the raw value
#     using the serial port
#
#   modifications
#     15-dec-2023   JM    initial version

from PySide6.QtCore import QSettings

from mydevice import myDevice
from arduinocomm import arduinoComm

class devFysioDaq(myDevice) :

  # constructor

  def __init__(self) :
    
    super().__init__()
    self.m_arduino = arduinoComm()
    self.m_portName = []

  # intialise
  #
  #     intialises the device, seperate routine is used to be compatible with LabView

  def initialise(self) :
    
    self.m_arduino.initialise(self.m_portName,1200)
    return

  # isConnected
  #
  #     check if the device is connected and returns the device information

  def isConnected(self) :

    devInfo = self.m_arduino.isConnected()
    return devInfo
  
  # setSampleRate
  #
  #     sets the sample rate of the device

  def setSampleRate(self) :
    return
  
  # isStarted
  #
  #     returns the current start/stop state of the device

  def isStarted(self) :
    return self.m_arduino.isStarted()
  
  # setStartStop
  #
  #     start or stops the device

  def setStartStop(self,startstop) :

    super().setStartStop(startstop)
    self.m_arduino.startstop(startstop)
    return
  
  # iniRead
  #
  #     reads the settings for the device from the specific file

  def iniRead(self,name) :

    settings = QSettings(QSettings.IniFormat,QSettings.UserScope,"JanSoft",name)

    settings.beginGroup("algemeen")
    self.m_portName = settings.value("address")
    settings.endGroup()

    return
  
  # read
  #
  #     reads the availabled data from the device

  def read(self) :
    return

  # edit
  #
  #     graphical interface to edit the settings of the device

  def edit(self) :
    return

    



