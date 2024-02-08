#
# devphsyiodaq_dialog
#
#     this class handles the device settings for the physiodaq device. A dialog box is 
#     popped up to let the user change gain and offset from the cnannels


from PySide6.QtWidgets import QDialog,QDialogButtonBox,QVBoxLayout,QLabel
from PySide6.QtCore import QFile
from PySide6.QtUiTools import QUiLoader
from devphysiodaq_ui import Ui_devphysiodaq_dialog

class devPhsyioDaq_dialog(QDialog) :

  # constructor
  #
  #   the UI is loaded

  def __init__(self):

    super().__init__()
    self.ui = Ui_devphysiodaq_dialog()
    self.ui.setupUi(self)

    # set the validation for the edit and gain box, only numerics are allowed

    # fill the channel select box with the names of the channels and set the gain and
    # offset in the edit boxes
    
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
    print("accepted")
    self.accept()

  # cancel button
  #
  #   reject
    
  def onCancel(self) :
    print("on cancel")
    self.reject()

  # gain edit
  #
  #   get the current selected channel and modify the gain of it
    
  def onGain(self) :
    print("on gain")

  # offset edit
  #
  #   get the current selected channel and modify the offset of it
    
  def onOffset(self) :
    print("on offset")

  # combobox select channel
  #
  #   retrieve the gain and offset for the selected channel and place this in the 
  #   edit boxes
    
  def onSelectChannel(self) :
    print ("channel selected")
