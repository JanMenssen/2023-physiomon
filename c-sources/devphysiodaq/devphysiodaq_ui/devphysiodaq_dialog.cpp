#include "devphysiodaq_dialog.h"
#include "./ui_devphysiodaq_dialog.h"

devphysiodaq_dialog::devphysiodaq_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::devphysiodaq_dialog)
{
    ui->setupUi(this);
    setWindowTitle("change channel settings");
}

devphysiodaq_dialog::~devphysiodaq_dialog() {
    delete ui;
}

void devphysiodaq_dialog::on_okButton_clicked() {

}


void devphysiodaq_dialog::on_cancelButton_clicked() {

}


void devphysiodaq_dialog::on_offsetEdit_editingFinished() {

}


void devphysiodaq_dialog::on_gainEdit_editingFinished() {

}


void devphysiodaq_dialog::on_channelComboBox_currentIndexChanged(int index) {

}

