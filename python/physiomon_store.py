#
# physiomon_store.py
#
#     this class handles the storage of the data acquired by the program. TDMS data
#     file format is used using the package npTMDS
#
#   modifications
#     18-dec-2023   JM    initial versions

class physiomon_store() :

  # constructor

  def __init__(self) :
    
    self.m_storage = False

    return
  
  # configure
  #
  # configures the storage engine using the information from the *.INI file and the 
  # channels class is used to get the samplerate

  def configure(self,settings,channels) :

    self.m_groupInfo = []

    groupInfo = {"name" : "", "sampleRate": 0 , "chanlist" : []}

    # first fill the groupname
    
    for store in settings.m_store :
      groupInfo["name"] = store.groupname
      self.m_groupInfo.append(groupInfo.copy())
    
    # now loop over the channels and add the channel to the correct storage engine
      
    for i in range(len(settings.m_channels)) :
      usedStore = settings.m_channels[i].store
      if usedStore > 0 : self.m_groupInfo[usedStore - 1].chanlist.append(i)

    # and get the sample frequency for all groups. Currently this is done by getting the sample frequency 
    # of the first channel in the list assuming the sample frequency of all channels in the list is equal
      
    for store in self.m_groupInfo : store.sampleRate = channels.getSampleRate(store.chanlist[0])

    # and return

    return
  
  
  # isStorareOn
  #
  #     returns a True or False, depending if the data is stored

  def isStorareOn(self) :
    return self.m_storage
  
  # setStorage
  #
  #     sets the storage of the data ON or off

  def setStorage(self,onoff) :
    return
  
# prepareWrite
#
#     prepares for writing, copies to data from a channel to a tempory buffer 
#     till this is done for all channels in the group

def prepareWrite(self) :
  return
  
def write(self) :
  return

# writeEvent
#
#     writes an event to disk

def writeEvent(self) :
  return