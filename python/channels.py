#
# channels.py
#
#       contains the channels and buffers classes
#
#   modifications
#     18-dec-2023  JM   initial version

TYPE_ANALOG_IN = 1

class buffer() :

  def __init__(self,length) :
    
    self.m_len = length
    self.m_indxWrite = 0
    self.m_indxRead = 0
    self.m_data = [0] * length

    return

  # read
  #
  #     read the data from the buffer and update the readIndx 
   
  def read(self) :

    data = []
    while self.m_indxRead != self.m_indxWrite :

      data.append(self.m_data[self.m_indxRead])
      
      self.m_indxRead = self.m_indxRead + 1
      if self.m_indxRead >= self.m_len :
        self.m_indxRead = 0

    return data
  
  # write
  #
  #     writes the samples in the circular buffer and updates the writeIndex

  def write(self,data) :
   
    for dataSample in data :

      self.m_data[self.m_indxWrite] = dataSample   
      self.m_indxWrite = self.m_indxWrite + 1
      if self.m_indxWrite >= self.m_len :
        self.m_indxWrite = 0
        
    return
  

class channels() :

  # constructor
  #
  #     intialisation of the object, sets the length of the circular buffers

  def __init__(self,nrsec) :
    
    self.m_lengthBuffer = nrsec
    self.m_buffers = []
    return

  # configure
  #
  #     get the settings and the device info to configure the appropriate buffers
    
  def configure(self,settings,device) :

    # for every channel

    numchan = settings.m_numchan
    for i in range(numchan) :

      tmpBuffer = {"display" : [], "store" : [], "sampleRate" : 0 , "name" : ""}  
      
      # find the type and perform action depending on the type, currently analog_In is only
      # supported 

      if (settings.m_channels[i]["type"] == TYPE_ANALOG_IN) :

        for analogChan in device.m_analogIn :
          channels = analogChan["channels"]
          try :
            
            indx = channels.index(i)
            tmpBuffer["sampleRate"] = analogChan["sampleRate"]
            tmpBuffer["display"] = buffer(int(self.m_lengthBuffer / tmpBuffer["sampleRate"]))
            tmpBuffer["store"] = buffer(int(self.m_lengthBuffer / tmpBuffer["sampleRate"]))

            self.m_buffers.append(tmpBuffer.copy())

          except ValueError :
            pass

    return
  
  # getSampleRate
  #
  #     returns the sample rate

  def getSampleRate(self) :
    return
  
  # readData
  #
  #     reads the data from the internal buffers

  def readData(self,channel) :

    data = self.m_buffers[channel]["display"].read()
    return data
  
  # resetBuffers
  #
  #     resets the buffers

  def resetBuffers(self) :
    return
  
  # writeData
  #
  #     write the data to the internal buffers

  def writeData(self,channel,data) :

    # write to both buffers

    self.m_buffers[channel]["display"].write(data)
    self.m_buffers[channel]["store"].write(data)

    return
  
  