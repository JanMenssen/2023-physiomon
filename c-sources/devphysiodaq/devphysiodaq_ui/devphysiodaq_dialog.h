#ifndef DEVPHYSIODAQ_DIALOG_H
#define DEVPHYSIODAQ_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class devphysiodaq_dialog;
}
QT_END_NAMESPACE

class devphysiodaq_dialog : public QDialog
{
    Q_OBJECT

public:
    devphysiodaq_dialog(QWidget *parent = nullptr);
    ~devphysiodaq_dialog();

private slots:

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_offsetEdit_editingFinished();
    void on_gainEdit_editingFinished();
    void on_channelComboBox_currentIndexChanged(int index);

private:
    Ui::devphysiodaq_dialog *ui;
};
#endif // DEVPHYSIODAQ_DIALOG_H
