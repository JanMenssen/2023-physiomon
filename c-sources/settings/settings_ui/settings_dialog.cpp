#include "./ui_settings_dialog.h"
#include "settings_dialog.h"

settings_dialog::settings_dialog(QWidget *parent, int *numchan, channelStruct *channels,
        int *numdisp, displayStruct *displays, QString *events, int numanalog, const analogInStruct *analogInfo) : QDialog(parent) , ui(new Ui::settings_dialog) {
  ui->setupUi(this);

  // fixed size, not resizable

  this->setFixedSize(this->width(),this->height());

  // because changes are made to the structures that can be rejected, and the interface is with pointers
  // we have to copy the structures
  //
  // the analog structure is not modified, so there is no need to copy and it is also a const pointer

  m_numchan = *numchan;
  m_numdisp = *numdisp;

  m_nChanPtr = numchan;
  m_nDispPtr = numdisp;

  m_channelPtr = channels;
  m_displayPtr = displays;

  m_eventPtr = events;

  for (int i=0;i<MAX_CHANNELS;i++) m_channels[i] = channels[i]; 
  for (int i=0;i<MAX_DISPLAYS;i++) m_displays[i] = displays[i];

  // for a number of edit boxes, only numerics are allowed

  ui->numchan->setValidator(new QIntValidator(1,MAX_CHANNELS,this));
  ui->numdisp->setValidator(new QIntValidator(1,MAX_DISPLAYS,this));

  ui->displayTop->setValidator(new QDoubleValidator(0,1,2,this));
  ui->displayLeft->setValidator(new QDoubleValidator(0,1,2,this));
  ui->displayHeight->setValidator(new QDoubleValidator(0,1,2,this));
  ui->displayWidth->setValidator(new QDoubleValidator(0,1,2,this));

  ui->displayYmin->setValidator(new QDoubleValidator(-INFINITY,INFINITY,2,this));
  ui->displayYmax->setValidator(new QDoubleValidator(-INFINITY,INFINITY,2,this));
  ui->displayXaxis->setValidator(new QDoubleValidator(0,3600,2,this));

  // set the number of displays and channels

  ui->numchan->setText(QString::number(m_numchan));
  ui->numdisp->setText(QString::number(m_numdisp));

  // fill the allowed number of displays in the channel tab and the sources

  ui->channelDisplaySelected->setRange(1, m_numdisp);
  for (int i=0;i<numanalog;i++) ui->channelSignalSelect->addItem(analogInfo[i].name);
  
  // and fill for channel
  
  ui->channelSelected->setRange(1, m_numchan);
  ui->channelSelected->setValue(1);
  fillChannelInfo(m_channels,0);
  
  bool hidden = m_displays[m_channels[0].display-1].mode != DISPLAY_MODE_NUMERIC;
  ui->channelPrecisionSelect->setHidden(hidden);
  ui->precisionLabel->setHidden(hidden);

  // display information 

  ui->displaySelected->setRange(1, m_numdisp);
  ui->displaySelected->setValue(1);
  fillDisplayInfo(m_displays,0);

  // set the events, the contents is stored in the dialog boxes 

  ui->event01->setText(m_eventPtr[0]);
  ui->event02->setText(m_eventPtr[1]);
  ui->event03->setText(m_eventPtr[2]);
  ui->event04->setText(m_eventPtr[3]);
  ui->event05->setText(m_eventPtr[4]);
  ui->event06->setText(m_eventPtr[5]);
  ui->event07->setText(m_eventPtr[6]);
  ui->event08->setText(m_eventPtr[7]);
  ui->event09->setText(m_eventPtr[8]);
  ui->event10->setText(m_eventPtr[9]);

}

// destructor

settings_dialog::~settings_dialog() {
  
 delete ui;
}

// fillChannelInfo
//
//    fills all items belonging to the channel indx

void settings_dialog::fillChannelInfo(channelStruct *chanInfo, int indx) {

  ui->channelName->setText(chanInfo[indx].name);
  ui->channelPrecisionSelect->setValue(chanInfo[indx].precision);
  
  switch (m_channels[indx].color) {
    
    case COLOR_RED :
      ui->channelColorSelect->setCurrentIndex(0);
      break;

    case COLOR_GREEN :
      ui->channelColorSelect->setCurrentIndex(1);
      break;
  
    case COLOR_BLUE :
      ui->channelColorSelect->setCurrentIndex(2);
      break;
  
    case COLOR_CYAN :
      ui->channelColorSelect->setCurrentIndex(3);
      break;
  
    case COLOR_MAGENTA :
      ui->channelColorSelect->setCurrentIndex(4);
      break;
  
    case COLOR_YELLOW :
      ui->channelColorSelect->setCurrentIndex(5);
      break;
  
    case COLOR_BLACK :
      ui->channelColorSelect->setCurrentIndex(6);
      break;
  
    case COLOR_WHITE :
      ui->channelColorSelect->setCurrentIndex(7);
      break;
  
    default :
      ui->channelColorSelect->setCurrentIndex(0);
  }
 
  setChannelRadioButtons(chanInfo[indx].type);
  ui->channelDisplaySelected->setValue(chanInfo[indx].display);
  ui->channelSignalSelect->setCurrentIndex(chanInfo[indx].source);

}

// fillDisplayInfo
//
//    fill the display items belonging to item indx

void settings_dialog::fillDisplayInfo(displayStruct *dispInfo, int indx) {

  ui->displayTop->setText(QString::number(dispInfo[indx].top,'f',2));
  ui->displayLeft->setText(QString::number(dispInfo[indx].left,'f',2));
  ui->displayHeight->setText(QString::number(dispInfo[indx].height,'f',2));
  ui->displayWidth->setText(QString::number(dispInfo[indx].width,'f',2));

  ui->displayYmin->setText(QString::number(dispInfo[indx].ymin,'f',0));
  ui->displayYmax->setText(QString::number(dispInfo[indx].ymax,'f',0));
  ui->displayXaxis->setText(QString::number(dispInfo[indx].timescale,'f',0));

  setDisplayRadioButtons(dispInfo[indx].mode);

}

// setChannelRadioButtons
//
//    depending of the kind of signal, the right radiobutton is set

void settings_dialog::setChannelRadioButtons(typeSignal kindSignal) {

  switch (kindSignal) {

    case TYPE_ANALOG_IN :

      ui->channelAnalog_rb->setChecked(true);
      ui->channelNumeric_rb->setChecked(false);
      ui->channelWaveform_rb->setChecked(false);

      break;
    
    case TYPE_NUMERIC_IN :

        ui->channelAnalog_rb->setChecked(false);
        ui->channelNumeric_rb->setChecked(true);
        ui->channelWaveform_rb->setChecked(false);
    
      break;

    default :

        ui->channelAnalog_rb->setChecked(false);
        ui->channelNumeric_rb->setChecked(false);
        ui->channelWaveform_rb->setChecked(false);
      
      break;
  }   
   
}

void settings_dialog::setDisplayRadioButtons(viewMode kindChart) {

  switch (kindChart) {

    case DISPLAY_MODE_STRIP :

      ui->displayStripChart_rb->setChecked(true);
      ui->displaySweepChart_rb->setChecked(false);
      ui->displayScopeChart_rb->setChecked(false);
      ui->displayNumeric_rb->setChecked(false);
      
      break;

    case DISPLAY_MODE_SWEEP :

        ui->displayStripChart_rb->setChecked(false);
        ui->displaySweepChart_rb->setChecked(true);
        ui->displayScopeChart_rb->setChecked(false);
        ui->displayNumeric_rb->setChecked(false);

      break;
      
    case DISPLAY_MODE_SCOPE :

        ui->displayStripChart_rb->setChecked(false);
        ui->displaySweepChart_rb->setChecked(false);
        ui->displayScopeChart_rb->setChecked(true);
        ui->displayNumeric_rb->setChecked(false);
      
      break;
      
      case DISPLAY_MODE_NUMERIC :

        ui->displayStripChart_rb->setChecked(false);
        ui->displaySweepChart_rb->setChecked(false);
        ui->displayScopeChart_rb->setChecked(false);
        ui->displayNumeric_rb->setChecked(true);
      
      break;


    default :

        ui->displayStripChart_rb->setChecked(false);
        ui->displaySweepChart_rb->setChecked(false);
        ui->displayScopeChart_rb->setChecked(false);
        ui->displayNumeric_rb->setChecked(false);
      
      break;
  }

}

// on_cancelButton_clicked
//
//    cancel is clicked, close the dialog without accepting changes

void settings_dialog::on_cancelButton_clicked() {

  reject();
}

// on_okButton_clicked
//
//  current settings of the dialog box are copied to the caller 

void settings_dialog::on_okButton_clicked() {

  // channels info

  *m_nChanPtr = m_numchan;
  for (int i=0;i<MAX_CHANNELS;i++) m_channelPtr[i] = m_channels[i];

  // display info
  
  *m_nDispPtr = m_numdisp;
  for (int i=0;i<MAX_DISPLAYS;i++) m_displayPtr[i] = m_displays[i];

  // events, data is obtained from the event text boxes

  m_eventPtr[0] = ui->event01->text();
  m_eventPtr[1] = ui->event02->text();
  m_eventPtr[2] = ui->event03->text();
  m_eventPtr[3] = ui->event04->text();
  m_eventPtr[4] = ui->event05->text();
  m_eventPtr[5] = ui->event06->text();
  m_eventPtr[6] = ui->event07->text();
  m_eventPtr[7] = ui->event08->text();
  m_eventPtr[8] = ui->event09->text();
  m_eventPtr[9] = ui->event10->text();

  // and done

  accept();

}

// on_numchan_editingFinished
//
//    the number of channels is changed. Because in C we use a static list of MAX_CHANNELS
//    elements and <m_cnumchan> contains the number of channels, we only have to change
//    <m_numchan> and adapt the channelSelected spinbox

void settings_dialog::on_numchan_editingFinished() {

  m_numchan = ui->numchan->text().toInt();
  ui->channelSelected->setRange(1,m_numchan);

}

// on_numdisp_editingFinished
//
//    the number of displays is changed. Because in C, with static arrays used, we only have to
//    change the number of displays and update the display selecged spinner and the displays
//    selection box in the channel tab

void settings_dialog::on_numdisp_editingFinished() {

  m_numdisp = ui->numdisp->text().toInt();

  ui->channelDisplaySelected->setRange(1, m_numdisp);
  ui->displaySelected->setRange(1, m_numdisp);

}

// on_channelName_editingFinished
//
//    name of the current channel is modified, store the new name in <m_channels> with the 
//    current index

void settings_dialog::on_channelName_textChanged(const QString &name) {

  int curItem = ui->channelSelected->value() - 1;
  m_channels[curItem].name = name;

}

// on_channelDisplaySelected_valueChanged
//
//    the current channel must be on another display, store the value in the <m_channels>
//    structure

void settings_dialog::on_channelDisplaySelected_valueChanged(int value) {

  int curItem = ui->channelSelected->value() - 1;
  m_channels[curItem].display = value;

  bool hidden = m_displays[value-1].mode != DISPLAY_MODE_NUMERIC;
  ui->channelPrecisionSelect->setHidden(hidden);
  ui->precisionLabel->setHidden(hidden);

}

// on_chanColorSelect_currentIndxChanged
//
//    the color is changed, store this in the channel structure
void settings_dialog::on_channelColorSelect_currentIndexChanged(int index) {

  int curItem = ui->channelSelected->value() - 1;
  switch(index) {

    case 0 : 
      m_channels[curItem].color = COLOR_RED;
      break;
    
    case 1 :
      m_channels[curItem].color = COLOR_GREEN;
      break;

    case 2 :
      m_channels[curItem].color = COLOR_BLUE;
      break;

    case 3 :
      m_channels[curItem].color = COLOR_CYAN;
      break;

    case 4 :
      m_channels[curItem].color = COLOR_MAGENTA;
      break;

    case 5 :
      m_channels[curItem].color = COLOR_YELLOW;
      break;

    case 6 :
      m_channels[curItem].color = COLOR_BLACK;
      break;
    
    case 7 :
      m_channels[curItem].color = COLOR_WHITE;
      break;

    default :
      m_channels[curItem].color = COLOR_GREEN;
  } 
}

// on_channelPrecisionSelect_valueChanged
//
//    the number of digts for the decimal displays are set

void settings_dialog::on_channelPrecisionSelect_valueChanged(int value) {

  int curItem = ui->channelSelected->value() - 1;
  m_channels[curItem].precision = value;

}

// on_channelAnalog_rb_clicked
//
//    the current channel is changed to an TYPE_ANALOG_IN signal

void settings_dialog::on_channelAnalog_rb_clicked() {

  int curItem = ui->channelSelected->value() - 1;
  m_channels[curItem].type = TYPE_ANALOG_IN;

}

// on_channelWaveform_rb_clicked
//
//    the current signal is changed to a TYPE_WAVEFORM signal (currently not supported)

void settings_dialog::on_channelWaveform_rb_clicked() {

  int curItem = ui->channelSelected->value() - 1;
  //-jm m_channels[curItem].type = TYPE_WAVEFORM_IN;

}

// on_channelNumeric_rb_clicked
//
//    the current signal in the channel is a numeric one. Modify the structure

void settings_dialog::on_channelNumeric_rb_clicked() {
  
  int curItem = ui->channelSelected->value() - 1;
  //-jm m_channels[curItem].type = TYPE_NUMERIC_IN;

}

// on_channelSignalSelect_currentIndexChanged
//
//    for the current channel we want another source, adapt the <m_channels> structure with the
//    new information
//    
//    Note: a check is done on curItem > 0, during creating this routine is called and then it r
//    returns a value of 0 ?

void settings_dialog::on_channelSignalSelect_currentIndexChanged(int index) {

  int curItem = ui->channelSelected->value()-1;
  if (curItem > 0) m_channels[curItem].source = index;

}

// on_displaySelected_valueChanged
//
//    we have selected another diplay to modify the values for it, be sure the correct values 
//    are in the dialog box

void settings_dialog::on_displaySelected_valueChanged(int value) {

  int curItem = value - 1;
  fillDisplayInfo(m_displays,curItem);

}

// on_channelSelected_valueChanged
//
//    we have selected another channel, so update the name, coloar, display and
//    radio buttons

void settings_dialog::on_channelSelected_valueChanged(int value) {

  int curItem = value - 1;
  fillChannelInfo(m_channels,curItem);
  
  bool hidden = m_displays[m_channels[curItem].display-1].mode != DISPLAY_MODE_NUMERIC;
  ui->channelPrecisionSelect->setHidden(hidden); 
  ui->precisionLabel->setHidden(hidden);

}

// on_displayTop_editingFinished
//
//    the top position of the curent display is changed, modify the <m_display> structure
//    so it can be affected 

void settings_dialog::on_displayTop_editingFinished() {
 
  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].top = ui->displayTop->text().toDouble();

}

// on_displayLeft_editingFinished
//
//    the left position of the curent display is changed, modify the <m_display> structure
//    so it can be affected 

void settings_dialog::on_displayLeft_editingFinished() {

  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].left = ui->displayLeft->text().toDouble();

}

// on_displayHeight_editingFinished
//
//    the current display must be larger in height, modify the <m_displays> structure so
//    it can be affected

void settings_dialog::on_displayHeight_editingFinished() {

  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].height = ui->displayHeight->text().toDouble();

}

// on_displayHeight_editingFinished
//
//    the current display must be larger in width, modify the <m_displays> structure so
//    it can be affected

void settings_dialog::on_displayWidth_editingFinished() {

  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].width = ui->displayWidth->text().toDouble();

}

// on_displayYmin_editingFinished
//
//    the y-axis is modified for the current display. Affect to by passing the new
//    values in the <m_displays> structure

void settings_dialog::on_displayYmin_editingFinished() {

  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].ymin = ui->displayYmin->text().toDouble();

}

// on_displayYmax_editingFinished
//
//    the y-axis is modified for the current display. Affect to by passing the new
//    values in the <m_displays> structure

void settings_dialog::on_displayYmax_editingFinished() {

  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].ymax = ui->displayYmax->text().toDouble();

}

// on_displayXaxis_editingFinished
//
//    the x-axis is modified for the current display. Affect to by passing the new
//    values in the <m_displays> structure

void settings_dialog::on_displayXaxis_editingFinished() {

  int curItem = ui->displaySelected->value() - 1;
  m_displays[curItem].timescale = ui->displayXaxis->text().toDouble();

}

// on_displayStripChart_rb_clicked
//
//    the current display is changed to a strip chart, like an old paper
//    recorder. Pass the new value into the <m_displays> structure

void settings_dialog::on_displayStripChart_rb_clicked() {

  int curDisplay = ui->displaySelected->value() - 1;
  int curChannel = ui->channelSelected->value() - 1;

  m_displays[curDisplay].mode = DISPLAY_MODE_STRIP;

  if ((curDisplay + 1) == m_channels[curChannel].display) ui->channelPrecisionSelect->setHidden(true); 

}

// on_displaySweepChart_rb_clicked
//
//    the current display is changed to a sweep chart, If the right of the display
//    is reached the display is cleared and continued on the left

void settings_dialog::on_displaySweepChart_rb_clicked() {

  int curDisplay = ui->displaySelected->value() - 1;
  int curChannel = ui->channelSelected->value() - 1;

  m_displays[curDisplay].mode = DISPLAY_MODE_SWEEP;
  
  if ((curDisplay + 1) == m_channels[curChannel].display) ui->channelPrecisionSelect->setHidden(true); 

}

// on_displayScopeChart_rb_clicked
//
//    the current display is changed to a scope chart like an oscilloscope. Pass
//    the value in the <m_display> structure

void settings_dialog::on_displayScopeChart_rb_clicked() {
 
  int curDisplay = ui->displaySelected->value() - 1;
  int curChannel = ui->channelSelected->value() - 1;

  m_displays[curDisplay].mode = DISPLAY_MODE_SCOPE;
  
  if ((curDisplay + 1) == m_channels[curChannel].display) ui->channelPrecisionSelect->setHidden(true); 

}

// on_displayNumeric_rb_clicked
//
//    we change the current display to a numeric one. Only numerics are 
//    displayed. Note, this mode is currently not implemented

void settings_dialog::on_displayNumeric_rb_clicked() {
 
  int curDisplay = ui->displaySelected->value() - 1;
  int curChannel = ui->channelSelected->value() - 1;

  m_displays[curDisplay].mode = DISPLAY_MODE_NUMERIC;
  
  if ((curDisplay + 1) == m_channels[curChannel].display) ui->channelPrecisionSelect->setHidden(false); 
  
}




