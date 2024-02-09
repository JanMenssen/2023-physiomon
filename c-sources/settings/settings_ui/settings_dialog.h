#ifndef _SETTINGS_DIALOG_H
#define _SETTINGS_DIALOG_H

#include "settings.h"
#include "physiomon.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class settings_dialog;
}
QT_END_NAMESPACE

class settings_dialog : public QDialog
{
    Q_OBJECT

public:
    settings_dialog(QWidget *parent = nullptr, int numchan = 0,channelStruct *m_channels = nullptr, int numdisp = 0, displayStruct *m_displays = nullptr);
    ~settings_dialog();

private slots:

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_numchan_editingFinished();
    void on_numdisp_editingFinished();
    void on_channelSelected_valueChanged(int arg1);
    void on_channelName_editingFinished();
    void on_channelUnit_editingFinished();
    void on_channelColor_editingFinished();
    void on_channelDisplaySelected_valueChanged(int arg1);
    void on_channelAnalog_rb_clicked();
    void on_channelWaveform_rb_clicked();
    void on_channelNumeric_rb_clicked();
    void on_channelSignalSelect_currentIndexChanged(int index);
    void on_displaySelected_valueChanged(int arg1);
    void on_displayTop_editingFinished();
    void on_displayLeft_editingFinished();
    void on_displayHeight_editingFinished();
    void on_displayWidth_editingFinished();
    void on_displayYmin_editingFinished();
    void on_displayYmax_editingFinished();
    void on_displayXaxis_editingFinished();
    void on_displayStripChart_rb_clicked();
    void on_displaySweepChart_rb_clicked();
    void on_displayScopeChart_rb_clicked();
    void on_displayNumeric_rb_clicked();
    void on_event01_editingFinished();
    void on_event02_editingFinished();
    void on_event03_editingFinished();
    void on_event04_editingFinished();
    void on_event05_editingFinished();
    void on_event06_editingFinished();
    void on_event07_editingFinished();
    void on_event08_editingFinished();
    void on_event09_editingFinished();
    void on_event10_inputRejected();

private:
    Ui::settings_dialog *ui;

    void setChannelRadioButtons(typeSignal typeSignal);
    void setDisplayRadioButtons(viewMode typeDisplay);

    int m_numchan = 0;
    int m_numdisp = 0;

    channelStruct *m_channelPtr = nullptr;
    channelStruct *m_channels = nullptr;
    displayStruct *m_displayPtr = nullptr;
    displayStruct *m_displays = nullptr;

};
#endif // DIALOG_H
