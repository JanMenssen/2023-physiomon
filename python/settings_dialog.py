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


