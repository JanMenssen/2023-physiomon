#
# buffers.py
#
#       circular buffers for read and wirte operations in the channels and the store
#
# modifications
#   19-dec-2023   JM    initial value

class buffers() :
  
  # constructor

  def __init__(self) :
    return
  
  # getBufferLen
  #
  #   returns the buffer length

  def getBufferLen(self) :
    return
  
  # setReadIndx
  #
  #   sets the position for the first data to read

  def setReadIndx(self) :
    return
  
  # getReadIndx
  #
  #   returns the position of the first data to read

  def getReadIndx(self) :
    return
  
  # setWriteIndx
  #
  #   sets the position to write the data

  def setWriteIndx(self) :
    return
  
  # getWriteIndx
  #
  #   returns the position of the first data to write

  def getWriteIndx(self) :
    return
  
  # init
  #
  #   initialises the circular buffer

  def init(self) :
    return
  
  # read
  #
  #   reads number of samples from the buffer

  def read(self,nSamples) :
    return
  
  # write
  #
  #   writes a number of samples to the buffer

  def write(self,data) :
    return
  
  # numToRead
  #
  #   returns the number of samples that can be read, the difference between the
  #   readIndx and writeIndx

  def numToRead(self) :
    return
