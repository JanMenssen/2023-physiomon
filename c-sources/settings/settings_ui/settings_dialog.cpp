#include "./ui_settings_dialog.h"
#include "settings_dialog.h"

settings_dialog::settings_dialog(QWidget *parent, int numchan, channelStruct *channels,
                                                  int numdisp, displayStruct *displays) : QDialog(parent) , ui(new Ui::settings_dialog) {
  ui->setupUi(this);

  // because changes are made to the structures that can be rejected, and the interface is with pointers
  // we have to copy the structures

  int m_numchan = numchan;
  int m_numdisp = numdisp;

  m_channelPtr = channels;
  m_displayPtr = displays;

  m_channels = new channelStruct[m_numchan];
  m_displays = new displayStruct[m_numdisp];

  memcpy(m_channels,m_channelPtr,m_numchan * sizeof(channelStruct));
  memcpy(m_displays,m_displayPtr,m_numdisp * sizeof(displayStruct));

  // for a number of edit boxes, only numerics are allowed

  ui->numchan->setValidator(new QIntValidator(0,10,this));
  ui->numdisp->setValidator(new QIntValidator(0,5,this));

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

  // set the channels tab

  ui->channelSelected->setRange(1, m_numchan);
  ui->channelSelected->setValue(1);

  ui->channelName->setText(m_channels[0].name);
  ui->channelDisplaySelected->setRange(1, m_numdisp);
  ui->channelDisplaySelected->setValue(1);

  setChannelRadioButtons(m_channels[0].type);

  // set display tab

  ui->displaySelected->setRange(1, m_numdisp);
  ui->displaySelected->setValue(1);

  ui->displayTop->setText(QString::number(m_displays[0].top,'f',2));
  ui->displayLeft->setText(QString::number(m_displays[0].left,'f',2));
  ui->displayHeight->setText(QString::number(m_displays[0].height,'f',2));
  ui->displayWidth->setText(QString::number(m_displays[0].width,'f',2));

  ui->displayYmin->setText(QString::number(m_displays[0].ymin,'f',0));
  ui->displayYmax->setText(QString::number(m_displays[0].ymax,'f',0));
  ui->displayXaxis->setText(QString::number(m_displays[0].timescale,'f',0));

  setDisplayRadioButtons(m_displays[0].mode);

  // set the events 
}



settings_dialog::~settings_dialog() {
  delete ui;
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
  
    default :

        ui->displayStripChart_rb->setChecked(false);
        ui->displaySweepChart_rb->setChecked(false);
        ui->displayScopeChart_rb->setChecked(false);
        ui->displayNumeric_rb->setChecked(false);
      
      break;

  }
}

void settings_dialog::on_cancelButton_clicked() {


  reject();
}

void settings_dialog::on_okButton_clicked() {

  accept();

}


void settings_dialog::on_numchan_editingFinished()
{

}


void settings_dialog::on_numdisp_editingFinished()
{

}


void settings_dialog::on_channelName_editingFinished()
{

}


void settings_dialog::on_channelUnit_editingFinished()
{

}


void settings_dialog::on_channelColor_editingFinished()
{

}


void settings_dialog::on_channelDisplaySelected_valueChanged(int arg1)
{

}


void settings_dialog::on_channelAnalog_rb_clicked()
{

}


void settings_dialog::on_channelWaveform_rb_clicked()
{

}


void settings_dialog::on_channelNumeric_rb_clicked()
{

}


void settings_dialog::on_channelSignalSelect_currentIndexChanged(int index)
{

}


void settings_dialog::on_displaySelected_valueChanged(int arg1)
{

}


void settings_dialog::on_channelSelected_valueChanged(int arg1)
{

}


void settings_dialog::on_displayTop_editingFinished()
{

}


void settings_dialog::on_displayLeft_editingFinished()
{

}


void settings_dialog::on_displayHeight_editingFinished()
{

}


void settings_dialog::on_displayWidth_editingFinished()
{

}


void settings_dialog::on_displayYmin_editingFinished()
{

}


void settings_dialog::on_displayYmax_editingFinished()
{

}


void settings_dialog::on_displayXaxis_editingFinished()
{

}


void settings_dialog::on_displayStripChart_rb_clicked()
{

}


void settings_dialog::on_displaySweepChart_rb_clicked()
{

}


void settings_dialog::on_displayScopeChart_rb_clicked()
{

}


void settings_dialog::on_displayNumeric_rb_clicked()
{

}


void settings_dialog::on_event01_editingFinished()
{

}


void settings_dialog::on_event02_editingFinished()
{

}


void settings_dialog::on_event03_editingFinished()
{

}


void settings_dialog::on_event04_editingFinished()
{

}


void settings_dialog::on_event05_editingFinished()
{

}


void settings_dialog::on_event06_editingFinished()
{

}


void settings_dialog::on_event07_editingFinished()
{

}


void settings_dialog::on_event08_editingFinished()
{

}


void settings_dialog::on_event09_editingFinished()
{

}


void settings_dialog::on_event10_inputRejected()
{

}

