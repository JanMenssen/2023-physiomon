#
# arduinocomm.py
#
#   this is the python implementation of the <arduinoComm> class, a class for communication with the
#   arduino
#
# modifications
#   07-nov-2023  JM   initial version

from PySide6.QtSerialPort import QSerialPort, QSerialPortInfo 
from PySide6.QtCore import QByteArray, QIODevice

BAUDRATE = 115200

class arduinoComm :

  # constructor, nothing is done

  def __init__(self) :
    
    self.rcvBuffer = QByteArray()
    self.m_started = False
    return

  # initialise the port

  def initialise(self,port) :
  
    self.m_port = QSerialPort()

    self.m_port.setPortName(port)
    self.m_port.open(QIODevice.ReadWrite)
  
    self.m_port.setBaudRate(BAUDRATE)
    self.m_port.setDataBits(QSerialPort.Data8)
    self.m_port.setFlowControl(QSerialPort.NoFlowControl)
    self.m_port.setParity(QSerialPort.NoParity)
    self.m_port.setStopBits(QSerialPort.OneStop)
    
    self.m_port.flush()
    
    self.m_started = False
    
    return
  
  # destructor

  def destroy(self) :
  
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

    self.rcvBuffer = QByteArray()
    return
  
  # isConneected

  def isConnected(self) :

    msgOK = False
    i = 0 
    
    self.sendMsg('v',[])
    while (msgOK == False) & ( i < 5) :
      msgOK,cmd,data = self.rcvMsg()
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
    
    # if there are more than 7 bytes received, we know the length of the message
    
    if (len(self.rcvBuffer) >= 7) :
    
      # get the position of the STX message and remove the bytes before

      i = 0
      while self.rcvBuffer[i] == 0x02 :
        i = i + 1

      self.rcvBuffer = self.rcvBuffer[i:]
      
      # check the whole message is received and decode> Keep the extra bytes in the buffer

      lenMsg = 2 * ord(self.rcvBuffer[2].decode()) + 5
      if (len(self.rcvBuffer) >= lenMsg) :
        cmd,data,msgOK = decode(self.rcvBuffer)
        if msgOK :
          self.rcvBuffer = self.rcvBuffer[lenMsg:]

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

  data = []

  # get command and lenght of the message

  cmd = inputData[1].decode()
  lenMsg = ord(inputData[2].decode())
  
  for i in range(lenMsg) :
   value = int.from_bytes(inputData[4+(2*i)],byteorder = 'big',signed = False)
   data.append(value)

  # checksum ok ?

  checksum = inputData[-2:-1]
  msgOK = (checksum == (sum(data) & 0x00FF).to_bytes(1,'big'))

  return cmd,data,msgOK