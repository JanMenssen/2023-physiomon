#
# devphsyiodaq_dialog
#
#     this class handles the device settings for the physiodaq device. A dialog box is 
#     popped up to let the user change gain and offset from the cnannels


from PySide6.QtWidgets import QDialog
from PySide6.QtGui import QDoubleValidator
from devphysiodaq_ui import Ui_devphysiodaq_dialog

class devPhsyioDaq_dialog(QDialog) :

  # constructor
  #
  #   the UI is loaded

  def __init__(self,analogInfo):

    super().__init__()
    self.ui = Ui_devphysiodaq_dialog()
    self.ui.setupUi(self)

    self.m_analogInfo = analogInfo

    # set the validation for the edit and gain box, only numerics are allowed

    self.ui.gainEdit.setValidator(QDoubleValidator(-5,5,2))
    self.ui.offsetEdit.setValidator(QDoubleValidator(-100,100,2))

    # fill the channel select box with the names of the channels and set the gain and
    # offset in the edit boxes
    
    for analogChannel in self.m_analogInfo :
      self.ui.channelComboBox.addItem(analogChannel["name"])

    self.ui.gainEdit.setText("%6.4f" % self.m_analogInfo[0]["gain"])
    self.ui.offsetEdit.setText("%5.3f" % self.m_analogInfo[0]["offset"])

    # connect to slots

    self.ui.okButton.clicked.connect(self.onOK)
    self.ui.cancelButton.clicked.connect(self.onCancel)
    self.ui.gainEdit.editingFinished.connect(self.onGain)
    self.ui.offsetEdit.editingFinished.connect(self.onOffset)
    self.ui.channelComboBox.currentIndexChanged.connect(self.onSelectChannel)
 
  # OK button
  #
  #   return with accept
         
  def onOK(self) :

    self.accept()

  # cancel button
  #
  #   reject
    
  def onCancel(self) :

    self.reject()

  # gain edit
  #
  #   get the current selected channel and modify the gain of it
    
  def onGain(self) :

    curItem = self.ui.channelComboBox.currentIndex()
    self.m_analogInfo[curItem]["gain"] = float(self.ui.gainEdit.text())

  # offset edit
  #
  #   get the current selected channel and modify the offset of it
    
  def onOffset(self) :

    curItem = self.ui.channelComboBox.currentIndex()
    self.m_analogInfo[curItem]["offset"] = float(self.ui.offsetEdit.text())

  # combobox select channel
  #
  #   retrieve the gain and offset for the selected channel and place this in the 
  #   edit boxes
    
  def onSelectChannel(self) :
    
    curItem = self.ui.channelComboBox.currentIndex()
    self.ui.gainEdit.setText("%6.4f" % self.m_analogInfo[curItem]["gain"])
    self.ui.offsetEdit.setText("%5.2f" % self.m_analogInfo[curItem]["offset"])  

  # getAnalogInfo
  #
  #   returns the (modified) analog structure
    
    def getAnalogInfo(self) :

      return self.m_analogInfo