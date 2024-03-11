#
# settings_dialog
#
#     class handles the general settings. A dialog is popped up in which teh user can make changes
#     which are passed to the main program to modify the cumber of channels, the number of displays
#     and the information what is in this channels and on this displays
#
#     Note, the UI is created in Qt Creator and compiled ot a *.py class
#
# modfications
#     09-feb-2024   JM    initial version

from PySide6.QtWidgets import QDialog
from PySide6.QtGui import QDoubleValidator,QIntValidator
from settings_ui import Ui_settings_dialog

COLOR_RED = 0
COLOR_GREEN = 1
COLOR_BLUE = 2
COLOR_CYAN = 3
COLOR_MAGENTA = 4
COLOR_YELLOW = 5
COLOR_BLACK = 6
COLOR_WHITE = 7

class settings_dialog(QDialog) :

  # constructor
  #
  #   the UI is loaded and filled with information from the structures

  def __init__(self,channels,displays,events,analog) :

    super().__init__()
    self.ui = Ui_settings_dialog()
    self.ui.setupUi(self)
    self.setFixedSize(self.width(),self.height())

    # copy the data to local structure

    self.m_channels = channels
    self.m_numchan = len(channels)

    self.m_displays = displays
    self.m_numdisp = len(displays)

    # set the validator items, for the numeric edit boxes

    self.ui.numchan.setValidator(QIntValidator(1,10))
    self.ui.numdisp.setValidator(QIntValidator(1,10))

    self.ui.displayTop.setValidator(QDoubleValidator(0,1,2))
    self.ui.displayLeft.setValidator(QDoubleValidator(0,1,2))
    self.ui.displayHeight.setValidator(QDoubleValidator(0,1,2))
    self.ui.displayLeft.setValidator(QDoubleValidator(0,1,2))

    self.ui.displayYmin.setValidator(QDoubleValidator(-1000,1000,2))
    self.ui.displayYmax.setValidator(QDoubleValidator(-1000,1000,2))
    self.ui.displayXaxis.setValidator(QDoubleValidator(0,3600,2))

    # set the number of displays and channels

    self.ui.numchan.setText("%d" % self.m_numchan)
    self.ui.numdisp.setText("%d" % self.m_numdisp)
    
    self.ui.channelPrecisionSelect.setRange(0,3)
    self.ui.channelDisplaySelected.setRange(1,self.m_numdisp)
    for i in analog : self.ui.channelSignalSelect.addItem(i["name"])
  
    # and fill for channels

    self.ui.channelSelected.setRange(1,self.m_numchan)
    self.ui.channelSelected.setValue(1)
    self.fillChannelInfo(self.m_channels,0)
  
    if self.m_displays[self.m_channels[0]["display"]-1]["mode"] != "numeric" :
      hidden = True
    else :
      hidden = False
    self.ui.channelPrecisionSelect.setHidden(hidden)
    self.ui.precisionLabel.setHidden(hidden)

    # display tab

    self.ui.displaySelected.setRange(1,self.m_numdisp)
    self.ui.displaySelected.setValue(1)
    self.fillDisplayInfo(self.m_displays,0)

    # events tab

    self.ui.event01.setText(events[0])
    self.ui.event02.setText(events[1])
    self.ui.event03.setText(events[2])
    self.ui.event04.setText(events[3])
    self.ui.event05.setText(events[4])
    self.ui.event06.setText(events[5])
    self.ui.event07.setText(events[6])
    self.ui.event08.setText(events[7])
    self.ui.event09.setText(events[8])
    self.ui.event10.setText(events[9])
 
    # and make the connects

    self.ui.okButton.clicked.connect(self.onOK)
    self.ui.cancelButton.clicked.connect(self.onCancel)
    self.ui.numchan.editingFinished.connect(self.onNumChannelsChanged)
    self.ui.numdisp.editingFinished.connect(self.onNumDisplaysChanged)
                                            
    self.ui.channelSelected.valueChanged.connect(self.onChannelSelected)
    self.ui.channelName.editingFinished.connect(self.onChannelNameChanged)
    self.ui.channelSignalSelect.currentIndexChanged.connect(self.onChannelSourceChanged)
    self.ui.channelDisplaySelected.valueChanged.connect(self.onChannelDisplayChanged)
    self.ui.channelColorSelect.currentIndexChanged.connect(self.onChannelColorChanged)
    self.ui.channelPrecisionSelect.valueChanged.connect(self.onChannelPrecisionChanged)
    self.ui.channelAnalog_rb.clicked.connect(self.onChannelTypeChanged)
    self.ui.channelWaveform_rb.clicked.connect(self.onChannelTypeChanged)
    self.ui.channelNumeric_rb.clicked.connect(self.onChannelTypeChanged)

    self.ui.displaySelected.valueChanged.connect(self.onDisplaySelected)
    self.ui.displayTop.editingFinished.connect(self.onDisplayPositionChanged)
    self.ui.displayLeft.editingFinished.connect(self.onDisplayPositionChanged)
    self.ui.displayHeight.editingFinished.connect(self.onDisplayPositionChanged)
    self.ui.displayWidth.editingFinished.connect(self.onDisplayPositionChanged)
    self.ui.displayYmin.editingFinished.connect(self.onDisplayScaleChanged)
    self.ui.displayYmax.editingFinished.connect(self.onDisplayScaleChanged)
    self.ui.displayXaxis.editingFinished.connect(self.onDisplayScaleChanged)
    self.ui.displaySweepChart_rb.clicked.connect(self.onDisplayModeChanged)
    self.ui.displayScopeChart_rb.clicked.connect(self.onDisplayModeChanged)
    self.ui.displayStripChart_rb.clicked.connect(self.onDisplayModeChanged)
    self.ui.displayNumeric_rb.clicked.connect(self.onDisplayModeChanged)  
    
  # fillChannels
  #
  #   fills the channel info

  def fillChannelInfo(self,chanInfo,indx) :
  
    self.ui.channelName.setText(chanInfo[indx]["name"])
    self.ui.channelSignalSelect.setCurrentIndex(chanInfo[indx]["source"])
    self.ui.channelDisplaySelected.setValue(chanInfo[indx]["display"])

    if chanInfo[indx]["color"] == COLOR_RED : self.ui.channelColorSelect.setCurrentIndex(0)
    if chanInfo[indx]["color"] == COLOR_GREEN : self.ui.channelColorSelect.setCurrentIndex(1)
    if chanInfo[indx]["color"] == COLOR_BLUE : self.ui.channelColorSelect.setCurrentIndex(2)
    if chanInfo[indx]["color"] == COLOR_CYAN : self.ui.channelColorSelect.setCurrentIndex(3)
    if chanInfo[indx]["color"] == COLOR_MAGENTA : self.ui.channelColorSelect.setCurrentIndex(4)
    if chanInfo[indx]["color"] == COLOR_YELLOW : self.ui.channelColorSelect.setCurrentIndex(5)
    if chanInfo[indx]["color"] == COLOR_BLACK : self.ui.channelColorSelect.setCurrentIndex(6)
    if chanInfo[indx]["color"] == COLOR_WHITE  : self.ui.channelColorSelect.setCurrentIndex(7)

    self.ui.channelPrecisionSelect.setValue(chanInfo[indx]["precision"])
    self.setChannelRadioButtons(chanInfo[indx]['type'])

  # fillDisplayInfo
  #
  #   fills the information for the displays

  def fillDisplayInfo(self,dispInfo,indx) :

    self.ui.displayTop.setText("%3.2f" % dispInfo[indx]["top"])
    self.ui.displayLeft.setText("%3.2f" % dispInfo[indx]["left"])
    self.ui.displayHeight.setText("%3.2f" % dispInfo[indx]["height"])
    self.ui.displayWidth.setText("%3.2f" % dispInfo[indx]["width"])

    self.ui.displayYmin.setText("%3.1f" % dispInfo[indx]["ymin"])
    self.ui.displayYmax.setText("%3.1f" % dispInfo[indx]["ymax"])
    self.ui.displayXaxis.setText("%3.1f" % dispInfo[indx]["timescale"])
 
    self.setDisplayRadioButtons(dispInfo[indx]["mode"].lower())
   
  # onOK
  #
  #   handles the OK button, and accept is returned

  def onOK(self) :
    self.accept()  

  # onCancel
  #
  #   handles the Cancel button, rejeccted

  def onCancel(self) :
    self.reject()  

  # onNumChannelsChanged
  #
  #   this callback is executed with the number of channels changed. 
    
  def onNumChannelsChanged(self) :
    
    newNumChan = int(self.ui.numchan.text())
    
    if (newNumChan > self.m_numchan) :

      newChannels = [ {"name" : "", "type" : 1, "source" : 0, "display" : 0, "color" : 0, "precision" :1 } for k in range(newNumChan-self.m_numchan)]
      self.m_channels.extend(newChannels)

    if (newNumChan < self.m_numchan) : self.m_channels = self.m_channels[:newNumChan]
    self.m_numchan = newNumChan
    self.ui.channelSelected.setRange(1,self.m_numchan)

  # onNumDisplayChanged
  #
  #   the number of displays is changed. Add or remove displays to or from <m_displays> and update
  #   the spinner box in the display tab and the display spinner box in the channels tab
    
  def onNumDisplaysChanged(self) :

    newNumDisp = int(self.ui.numdisp.text())

    if newNumDisp > self.m_numdisp :

      newDisplays = [{"top" : 0.0, "left" : 0.0, "width" : 0.1, "height" : 0.1, "ymin" : -1, "ymax" : 1, "timescale" : 10, "mode" : "sweep"} for k in range(newNumDisp-self.m_numdisp)]
      self.m_displays.extend(newDisplays)

    if newNumDisp < self.m_numdisp :

      self.m_displays = self.m_displays[:newNumDisp]

    self.m_numdisp = newNumDisp  
    self.ui.displaySelected.setRange(1,self.m_numdisp)
    self.ui.channelDisplaySelected.setRange(1,self.m_numdisp)

  # onDisplaySelected
  #
  #   anaother display is selected, update the display field with information for the
  #   current display
    
  def onDisplaySelected(self) :

    curDisplay = self.ui.displaySelected.value() - 1
    self.fillDisplayInfo(self.m_displays,curDisplay)

  # onDisplayPositionChanged
  #
  #   the position of the display (top,left,height or width) is changed, pass the new values to
  #   the <m_displays> structure
    
  def onDisplayPositionChanged(self) :

    curDisplay = self.ui.displaySelected.value() - 1

    self.m_displays[curDisplay]["top"] = float(self.ui.displayTop.text())
    self.m_displays[curDisplay]["left"] = float(self.ui.displayLeft.text())
    self.m_displays[curDisplay]["height"] = float(self.ui.displayHeight.text())
    self.m_displays[curDisplay]["width"] = float(self.ui.displayWidth.text())
    
  # onDisplayScaleChanged
  #
  #   the y-axis or x-axis is changed, pass the new parameters to the <m_display> structure
  
  def onDisplayScaleChanged(self) :
    
    curDisplay = self.ui.displaySelected.value() - 1
    
    self.m_displays[curDisplay]["ymin"] = float(self.ui.displayYmin.text())
    self.m_displays[curDisplay]["ymax"] = float(self.ui.displayYmax.text())
    self.m_displays[curDisplay]["timescale"] = float(self.ui.displayXaxis.text())
 
  # onDisplayModeChanged
  #
  #   another mode of displaying the signals is choosen, update the structure
    
  def onDisplayModeChanged(self) :
    
    curDisplay = self.ui.displaySelected.value() - 1

    if self.ui.displaySweepChart_rb.isChecked() :
      self.m_displays[curDisplay]["mode"] = "sweep"
      hidden = True
    if self.ui.displayScopeChart_rb.isChecked() :
       self.m_displays[curDisplay]["mode"] = "scope"
       hidden = True
    if self.ui.displayStripChart_rb.isChecked() :
       self.m_displays[curDisplay]["mode"] = "strip"
       hidden = True
    if self.ui.displayNumeric_rb.isChecked() :
       self.m_displays[curDisplay]["mode"] = "numeric"
       hidden = False

    self.ui.channelPrecisionSelect.setHidden(hidden)
    self.ui.precisionLabel.setHidden(hidden)  
  
  # onChannelSelected
  #   
  #   another channel is selected, update the channel pareameters
    
  def onChannelSelected(self) :

    curChannel = self.ui.channelSelected.value() - 1
    self.fillChannelInfo(self.m_channels,curChannel)
    
    if self.m_displays[self.m_channels[curChannel]["display"]-1]["mode"] != "numeric" :
      hidden = True
    else :
      hidden = False
    self.ui.channelPrecisionSelect.setHidden(hidden)
    self.ui.precisionLabel.setHidden(hidden)

  # onChannelNameChanged
  #
  #   the channel name is modified, pass it into the <m__channels> structure
    
  def onChannelNameChanged(self) :

    curChannel = self.ui.channelSelected.value() - 1   
    self.m_channels[curChannel]["name"] = self.ui.channelName.text()

  # onChannelColorChanged
  #
  #    the color is changed

  def onChannelColorChanged(self) :

    curChannel = self.ui.channelSelected.value() - 1
    indx = self.ui.channelColorSelect.currentIndex()

    if indx == 0 : self.m_channels[curChannel]["color"] = COLOR_RED
    if indx == 1 : self.m_channels[curChannel]["color"] = COLOR_GREEN
    if indx == 2 : self.m_channels[curChannel]["color"] = COLOR_BLUE
    if indx == 3 : self.m_channels[curChannel]["color"] = COLOR_CYAN
    if indx == 4 : self.m_channels[curChannel]["color"] = COLOR_MAGENTA
    if indx == 5 : self.m_channels[curChannel]["color"] = COLOR_YELLOW
    if indx == 6 : self.m_channels[curChannel]["color"] = COLOR_BLACK
    if indx == 7 : self.m_channels[curChannel]["color"] = COLOR_WHITE

  # onChannelPrecisionChanged
  #
  #     precicsion is changed

  def onChannelPrecisionChanged(self) :

    curChannel = self.ui.channelSelected.value() - 1
    value = self.ui.channelPrecisionSelect.value()
    self.m_channels[curChannel]["precision"] = value
  
  # onChannelSourceCHanged  
  #
  #    the source of the current channel is changed

  def onChannelSourceChanged(self) :

    curChannel = self.ui.channelSelected.value() - 1
    self.m_channels[curChannel]["source"] = self.ui.channelSignalSelect.currentIndex()

  # onChannelDisplayChanged
  #
  #     the current display is changed
    
  def onChannelDisplayChanged(self) :

    curChannel = self.ui.channelSelected.value() - 1
    self.m_channels[curChannel]["display"] = self.ui.channelDisplaySelected.value()

    if self.m_displays[self.m_channels[curChannel]["display"]-1]["mode"] != "numeric" :
      hidden = True
    else :
      hidden = False
    self.ui.channelPrecisionSelect.setHidden(hidden)
    self.ui.precisionLabel.setHidden(hidden) 

  # onChannelTypeChanged
  #
  #   this callback is called when one of the radio buttons is pressed
    
  def onChannelTypeChanged(self) :
    
    curChannel = self.ui.channelSelected.value() - 1

    if self.ui.channelAnalog_rb.isChecked() :
      self.m_channels[curChannel]["type"] = 1
    if self.ui.channelWaveform_rb.isChecked() :
      self.m_channels[curChannel]["type"] = 2
    if self.ui.channelNumeric_rb.isChecked() :
      self.m_channels[curChannel]["type"] = 3

  # getModifiedValues
  #
  #   this routine returns the modified values for channels, displays and events
    
  def getModifiedValues(self) :

    events = []
    events.append(self.ui.event01.text())
    events.append(self.ui.event02.text())
    events.append(self.ui.event03.text())
    events.append(self.ui.event04.text())
    events.append(self.ui.event05.text())
    events.append(self.ui.event06.text())
    events.append(self.ui.event07.text())
    events.append(self.ui.event08.text())
    events.append(self.ui.event09.text())
    events.append(self.ui.event10.text())

    return self.m_channels,self.m_displays,events
  
  # setChannelRadioButtons
  #
  #   sets the radio buttons depending on type channel
    
  def setChannelRadioButtons(self,type) :

    if (type == 1) :
      self.ui.channelAnalog_rb.setChecked(True)
      self.ui.channelWaveform_rb.setChecked(False)
      self.ui.channelNumeric_rb.setChecked(False)
    
    if (type == 2) :
      self.ui.channelAnalog_rb.setChecked(False)
      self.ui.channelWaveform_rb.setChecked(True)
      self.ui.channelNumeric_rb.setChecked(False)
    
    if (type == 3) :
      self.ui.channelAnalog_rb.setChecked(False)
      self.ui.channelWaveform_rb.setChecked(False)
      self.ui.channelNumeric_rb.setChecked(True)

  # setDisplayRadioButtons
  #
  #   sets the radiobuttons depending on the kind of display choosen for the selected
  #   displays
      
  def setDisplayRadioButtons(self,mode) :

    if (mode == "sweep") :
      self.ui.displayStripChart_rb.setChecked(False)
      self.ui.displayScopeChart_rb.setChecked(False)
      self.ui.displaySweepChart_rb.setChecked(True)
      self.ui.displayNumeric_rb.setChecked(False)

    if (mode == "scope") :
      self.ui.displayStripChart_rb.setChecked(False)
      self.ui.displayScopeChart_rb.setChecked(True)
      self.ui.displaySweepChart_rb.setChecked(False)
      self.ui.displayNumeric_rb.setChecked(False)

    if (mode == "strip") :
      self.ui.displayStripChart_rb.setChecked(True)
      self.ui.displayScopeChart_rb.setChecked(False)
      self.ui.displaySweepChart_rb.setChecked(False)
      self.ui.displayNumeric_rb.setChecked(False)

    if (mode == "numeric") :
      self.ui.displayStripChart_rb.setChecked(False)
      self.ui.displayScopeChart_rb.setChecked(False)
      self.ui.displaySweepChart_rb.setChecked(False)
      self.ui.displayNumeric_rb.setChecked(True)