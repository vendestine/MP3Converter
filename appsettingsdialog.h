#ifndef APPSETTINGSDIALOG_H
#define APPSETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>

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
    void onThemesComboBoxChanged(const QString& );
    void onLanguagesComboBoxChanged(const QString& );
    void onBitRateComboBoxChanged(const QString& );
    void onSampleRateComboBoxChanged(const QString& );

    // checkBox 点击事件
    void onFinishSoundCheckBoxClicked();

private:
    // 加载settings
    void loadSettings();
    // 更换皮肤
    void setCssStylesheet(const QString &style);
    // 辅助函数：设置下拉框的当前索引
    void setComboBoxIndex(QComboBox*, const QString&);


    Ui::AppSettingsDialog *ui;
};

#endif // APPSETTINGSDIALOG_H
