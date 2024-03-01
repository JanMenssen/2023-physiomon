#
# physiomon_channels.py
#
#       contains the channels and buffers classes
#
#   modifications
#     18-dec-2023  JM   initial version
#     11-feb-2024  JM   renamed to <physiomon_channels>
#     16-feb-2024  JM   fater implementation of cyclic buffer 

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
    
    if (self.m_indxWrite > self.m_indxRead) :
      data = self.m_data[self.m_indxRead:self.m_indxWrite]

    if (self.m_indxWrite < self.m_indxRead) :  
      data = self.m_data[self.m_indxRead:] + self.m_data[:self.m_indxWrite]
    
    self.m_indxRead = self.m_indxWrite
  
    #-jm data = []
    #-jm print(" indices old  : %d %d" % (self.m_indxWrite,self.m_indxRead))
    #-jm 
    #-jm while self.m_indxRead != self.m_indxWrite :
    #-jm 
    #-jm  data.append(self.m_data[self.m_indxRead])
    #-jm  
    #-jm  self.m_indxRead = self.m_indxRead + 1
    #-jm  if self.m_indxRead >= self.m_len :
    #-jm    self.m_indxRead = 0
 
    return data
  
  # write
  #
  #     writes the samples in the circular buffer and updates the writeIndex

  def write(self,data) :
   
    ntal = len(data)

    if self.m_indxWrite + ntal <= self.m_len :
      self.m_data[self.m_indxWrite:(self.m_indxWrite + ntal)] = data
      self.m_indxWrite += ntal
    
    else :
      split = self.m_len - self.m_indxWrite
      self.m_data[self.m_indxWrite:] = data[:split]
      self.m_data[:(ntal-split)] = data[split:]
      self.m_indxWrite = ntal - split

    # for dataSample in data :
    #
    #  self.m_data[self.m_indxWrite] = dataSample   
    #  self.m_indxWrite = self.m_indxWrite + 1
    #  if self.m_indxWrite >= self.m_len :
    #    self.m_indxWrite = 0
        
    return
  

class physiomon_channels() :

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
    
    for i in range(len(settings.m_channels)) :

      tmpBuffer = {"display" : [], "store" : [], "sampleRate" : 0}  
      
      # find the type and perform action depending on the type, currently analog_In is only
      # supported 

      if (settings.m_channels[i]["type"] == TYPE_ANALOG_IN) :

        for analogChan in device.m_analogIn :
          channels = analogChan["channels"]
          try :
            
            indx = channels.index(i)
            tmpBuffer["sampleRate"] = analogChan["sampleRate"]
            tmpBuffer["display"] = buffer(int(self.m_lengthBuffer * tmpBuffer["sampleRate"]))
            tmpBuffer["store"] = buffer(int(self.m_lengthBuffer  * tmpBuffer["sampleRate"]))

            self.m_buffers.append(tmpBuffer.copy())

          except ValueError :
            pass

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
  
  # getSampleRate
  #
  #     returns the sampleRate for the desired channel

  def getSampleRate(self,channel) :

    return self.m_buffers[channel]["sampleRate"]
  
  