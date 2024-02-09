#include "devphysiodaq_dialog.h"
#include "./ui_devphysiodaq_dialog.h"

devphysiodaq_dialog::devphysiodaq_dialog(QWidget *parent, int n, analogInStruct *analogInfo) : QDialog(parent) , ui(new Ui::devphysiodaq_dialog) {
  
  ui->setupUi(this);

  // fixed size, not resizable
  
  this->setFixedSize(this->width(),this->height());
  setWindowTitle("change channel settings");

  m_numchan = n;
  m_analogPtr = analogInfo;

  // because we make changes to the analog info, a pointer doesn't work when cancel is pressed, 
  // a copy is needed. This copy is returned when OK is pressed, on Cancel it is destroyed

  m_analogInfo = new analogInStruct[m_numchan];
  if (m_analogPtr != nullptr) memcpy(m_analogInfo,m_analogPtr,m_numchan * sizeof(analogInStruct));

  // only numerics are allowed in the gain and offset edit boxes

  ui->gainEdit->setValidator(new QDoubleValidator(0, 100, 2, this));
  ui->offsetEdit->setValidator(new QDoubleValidator(-100, 100, 2, this));
  
  // set the names of the channels to the channel list, make the first channel the default
  // and set the gain and offset in the boxes

  for (int i=0;i<m_numchan;i++) ui->channelComboBox->addItem(m_analogInfo[i].name);

  ui->gainEdit->setText(QString::number(m_analogInfo[0].gain,'f',3));
  ui->offsetEdit->setText(QString::number(m_analogInfo[0].offset,'f',2));
}

devphysiodaq_dialog::~devphysiodaq_dialog() {
  delete ui;
}

// OK is pressed, copy the changed analog info to the parent structure

void devphysiodaq_dialog::on_okButton_clicked() {

  // get the last items from the dialog, (no return can be given)


  int curItem = ui->channelComboBox->currentIndex();
  m_analogInfo[curItem].offset = ui->offsetEdit->text().toDouble();
  m_analogInfo[curItem].gain = ui->gainEdit->text().toDouble();

  memcpy(m_analogPtr,m_analogInfo,m_numchan * sizeof(analogInStruct));

  accept();
}

// cancel is pressed, close 

void devphysiodaq_dialog::on_cancelButton_clicked() {
  
  reject();
}

// offset is changed, store in structure

void devphysiodaq_dialog::on_offsetEdit_editingFinished() {

  int curItem = ui->channelComboBox->currentIndex();
  m_analogInfo[curItem].offset = ui->offsetEdit->text().toDouble();
}

// edit is changed, store in structure

void devphysiodaq_dialog::on_gainEdit_editingFinished() {
  
  int curItem = ui->channelComboBox->currentIndex();
  m_analogInfo[curItem].gain = ui->gainEdit->text().toDouble();
}

// comboxbox is changed, change gain and edit

void devphysiodaq_dialog::on_channelComboBox_currentIndexChanged(int index) {

  int curItem = ui->channelComboBox->currentIndex();
  
  ui->gainEdit->setText(QString::number(m_analogInfo[curItem].gain,'f',4));
  ui->offsetEdit->setText(QString::number(m_analogInfo[curItem].offset,'f',2));
}

