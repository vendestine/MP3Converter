#ifndef APPSETTINGSDIALOG_H
#define APPSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class AppSettingsDialog;
}

class AppSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppSettingsDialog(QWidget *parent = nullptr);
    ~AppSettingsDialog();

private slots:
    // push button 点击事件
    void onLoadButtonClicked();
    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void onDestinationButtonClicked();

    // comboBox 变化事件
    void onThemesComboBoxChanged(QString);
    void onLanguagesComboBoxChanged(QString);
    void onBitRateComboBoxChanged(QString);
    void onSampleRateComboBoxChanged(QString);

    // checkBox 点击事件
    void onFinishSoundCheckBoxClicked();

private:
    void setCssStylesheet(const QString &style);

    Ui::AppSettingsDialog *ui;
};

#endif // APPSETTINGSDIALOG_H
