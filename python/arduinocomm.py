#
# arduinocomm.py
#
#   this is the python implementation of the <arduinoComm> class, a class for communication with the
#   arduino
#
# modifications
#   07-nov-2023  JM   initial version

from PySide6.QtSerialPort import QSerialPort
from PySide6.QtCore import QByteArray, QIODevice
import struct

class arduinoComm :

  # constructor, nothing is done

  def __init__(self,port,baudrate = 230400) :
    
    self.rcvBuffer = QByteArray()
    self.m_started = False

    self.m_port = QSerialPort()

    self.m_port.setPortName(port)
    self.m_port.open(QIODevice.ReadWrite)
  
    self.m_port.setBaudRate(baudrate)
    self.m_port.setDataBits(QSerialPort.Data8)
    self.m_port.setFlowControl(QSerialPort.NoFlowControl)
    self.m_port.setParity(QSerialPort.NoParity)
    self.m_port.setStopBits(QSerialPort.OneStop)
    
    self.m_port.flush()
    
    return
  
  # destructor

  def destroy(self) :
  
    if self.m_port.isOpen() :
      self.m_port.close()
    self.m_started = False
    return
  
  # startstop
  # 
  # start or stop the module

  def startstop(self,onoff) :

    if onoff :
      self.m_started = True
      self.sendMsg("x",[0x01])
    else :
      self.m_started = False
      self.sendMsg("x",[0x00])

    # and clear everything, write, read and receive buffer

    self.m_port.flush()  
    self.m_port.readAll()

    self.rcvBuffer = QByteArray()

    return
  
  # isConneected

  def isConnected(self) :

    msgOK = False
    cmd = ""
    i = 0 
    
    # because there could be data into the buffer, we flush the port before getting
    # the info (NOTE: this doesn't work)

    self.m_port.flush()
    self.rcvBuffer = QByteArray()

    self.sendMsg('v',[])
    while ( i < 5) & (cmd != 'V') :
      msgOK,cmd,data = self.rcvMsg()
      print(cmd)

      i = i + 1

    dataStr = ''
    for f in data :
      dataStr = dataStr + chr(f)
    
    return dataStr
  
  # isStarted

  def isStarted(self) :
    
    return self.m_started
    
  # sendMsg
  #
  #   sends a command with data to the serial port after encoding it
  
  def sendMsg(self,cmd,data) :

    outputData = encode(cmd,data)
    self.m_port.write(outputData)
    
    return

  # rcvMsg
  #
  # read the message, returns TRUE is a message is received

  def rcvMsg(self) :
  
    msgOK = False
    cmd = ''
    data = []
    
    # read the incoming bytes to the buffer
    
    nbytes = self.m_port.bytesAvailable()
    self.rcvBuffer += self.m_port.read(nbytes)

    # find the STX message, remove data from buffer until found
    # Note : there should be at least one byte in the buffer
    
    if (len(self.rcvBuffer) > 0 ) : 
      
      while ((self.rcvBuffer[0] != b'\x02') and (len(self.rcvBuffer) > 1)) :
        self.rcvBuffer = self.rcvBuffer[1:]

      # STX found, then decode message
        
      if ((self.rcvBuffer[0] == b'\x02') and (len(self.rcvBuffer) > 3)) :

        lenMsg = 2 * ord(self.rcvBuffer[2].decode()) + 5
        if (len(self.rcvBuffer) >= lenMsg) :
        
          cmd,data,msgOK = decode(self.rcvBuffer[0:lenMsg])
          if msgOK : self.rcvBuffer = self.rcvBuffer[(lenMsg-1):]

    return msgOK,cmd,data


# encode
#
#   this routine encodes the command and the data to a byte array that can be send to the arduino

def encode(cmd,data) :

  STX = 0x02
  EOT = 0x00

  outputData = bytearray()
  
  outputData += STX.to_bytes(1,'big')
  outputData += bytes(cmd,'ascii')
  outputData += len(data).to_bytes(1,'big')

  for num in data :
    outputData += num.to_bytes(2,'big')

  checksum = sum(data) & 0x00FF
  outputData += checksum.to_bytes(1,'big')
  outputData += EOT.to_bytes(1,'big')

  return outputData

# decode
#
#    decodes a message

def decode(inputData) :

  # get command and lenght of the message

  cmd = inputData[1].decode()
  lenMsg = ord(inputData[2].decode())
  
  # get the data

  dataSlice = inputData[3:-2]
  data = [int.from_bytes(dataSlice[i:i+2], byteorder = "big",signed = True) for i in range(0, len(dataSlice), 2)]
  
  # checksum OK ?
  
  checksum = inputData[-2:-1]
  msgOK = (checksum == (sum(data) & 0x00FF).to_bytes(1,'big'))

  return cmd,data,msgOK