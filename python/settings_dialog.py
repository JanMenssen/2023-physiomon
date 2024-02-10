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

    # set the channels tab

    self.ui.channelSelected.setRange(1,self.m_numchan)
    self.ui.channelSelected.setValue(1)

    self.ui.channelDisplaySelected.setRange(1,self.m_numdisp)
    self.ui.channelDisplaySelected.setValue(self.m_channels[0]["display"])

    self.ui.channelName.setText(self.m_channels[0]["name"])
    for i in analog :
      self.ui.channelSignalSelect.addItem(i["name"])
    self.ui.channelSignalSelect.setCurrentIndex(self.m_channels[0]["source"])

    self.setChannelRadioButtons(self.m_channels[0]['type'])

    # display tab

    self.ui.displaySelected.setRange(1,self.m_numdisp)
    self.ui.displaySelected.setValue(1)

    self.ui.displayTop.setText("%3.2f" % self.m_displays[0]["top"])
    self.ui.displayLeft.setText("%3.2f" % self.m_displays[0]["left"])
    self.ui.displayHeight.setText("%3.2f" % self.m_displays[0]["height"])
    self.ui.displayWidth.setText("%3.2f" % self.m_displays[0]["width"])

    self.ui.displayYmin.setText("%3.1f" % self.m_displays[0]["ymin"])
    self.ui.displayYmax.setText("%3.1f" % self.m_displays[0]["ymax"])
    self.ui.displayXaxis.setText("%3.1f" % self.m_displays[0]["timescale"])
 
    self.setDisplayRadioButtons(self.m_displays[0]["mode"].lower())

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

      newChannels = [ {"name" : "", "type" : 0, "source" : 0, "display" : 0} for k in range(newNumChan-self.m_numchan)]
      self.m_channels.extend(newChannels)

    if (newNumChan < self.m_numchan) :
      
      self.m_channels = self.m_channels[:newNumChan]

    self.m_numchan = newNumChan
    self.ui.channelSelected.setRange(1,self.m_numchan)

  # onNuMDisplayChanged
  #
  #   the number of displays is changed. Add or remove displays to or from <m_displays> and update
  #   the spinner box in the display tab and the display spinner box in the channels tab
    
  def onNumDisplaysChanged(self) :

    newNumDisp = int(self.ui.numdisp.text())

    if newNumDisp > self.m_numdisp :

      newDisplays = [{"top" : 0, "left" : 0, "width" : 0, "height" : 0, "ymin" : 0, "ymax" : 0, "timescale" : 10, "mode" : ""} for k in range(newNumDisp-self.m_numdisp)]
      self.m_channels.extend(newDisplays)

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
    
    self.ui.displayTop.setText("%3.2f" % self.m_displays[curDisplay]["top"])
    self.ui.displayLeft.setText("%3.2f" % self.m_displays[curDisplay]["left"])
    self.ui.displayHeight.setText("%3.2f" % self.m_displays[curDisplay]["height"])
    self.ui.displayWidth.setText("%3.2f" % self.m_displays[curDisplay]["width"])

    self.ui.displayYmin.setText("%3.1f" % self.m_displays[curDisplay]["ymin"])
    self.ui.displayYmax.setText("%3.1f" % self.m_displays[curDisplay]["ymax"])
    self.ui.displayXaxis.setText("%3.1f" % self.m_displays[curDisplay]["timescale"])
 
    self.setDisplayRadioButtons(self.m_displays[curDisplay]["mode"].lower())

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
    self.m_displays[curDisplay]["timecale"] = float(self.ui.displayXaxis.text())
 
  # onDisplayModeChanged
  #
  #   another mode of displaying the signals is choosen, update the structure
    
  def onDisplayModeChanged(self) :
    
    curDisplay = self.ui.displaySelected.value() - 1

    if self.ui.displaySweepChart_rb.isChecked() :
      self.m_displays[curDisplay]["mode"] = "sweep"
    if self.ui.displayScopeChart_rb.isChecked() :
       self.m_displays[curDisplay]["mode"] = "scope"
    if self.ui.displayStripChart_rb.isChecked() :
       self.m_displays[curDisplay]["mode"] = "strip"
    if self.ui.displayNumeric_rb.isChecked() :
       self.m_displays[curDisplay]["mode"] = "numeric"
  
  # onChannelSelected
  #   
  #   another channel is selected, update the channel pareameters
    
  def onChannelSelected(self) :

    curChannel = self.ui.channelSelected.value() - 1

    self.ui.channelDisplaySelected.setValue(self.m_channels[curChannel]["display"])
    self.ui.channelName.setText(self.m_channels[curChannel]["name"])
    self.ui.channelSignalSelect.setCurrentIndex(self.m_channels[curChannel]["source"])
    
    self.setChannelRadioButtons(self.m_channels[curChannel]["type"])

  # onChannelNameChanged
  #
  #   the channel name is modified, pass it into the <m__channels> structure
    
  def onChannelNameChanged(self) :

    curChannel = self.ui.channelSelected.value() - 1   
    self.m_channels[curChannel]["name"] = self.ui.channelName.text()
    
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

  # onChannelTypeChanged
  #
  #   this callback is called when one of the radio buttons is pressed
    
  def onChannelTypeChanged(self) :
    
    curChannel = self.ui.channelSelected.value()

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
    
    if (type == 1) :
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