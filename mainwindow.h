#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QProcess>
#include <QSound>
#include <QTranslator>
#include "dropframe.h"
#include "converterprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void onSettingsButtonClicked();   // settings button点击事件
    void onHelpButtonClicked();       // help button点击事件
    void onConvertButtonClicked();    // convert button点击事件
    void onShowFileButton();           // showfile button点击事件
    void closeProcessWidget();        // convert process控件cancel后，关闭process widget
    void prepareConvert(QString filePath);          // dropframe控件，文件选择后，准备convert

    // process相关事件
    void onProcessReadyReadStandardOutput();
    void onProcessReadyReadStandardError();
    void onProcessErrorOccured(QProcess::ProcessError error);

private:
    void addSubWidget();  // 添加子控件
    void playFinishedSound();  // 播放完成后的声音
    void setTheme(const QString&);     // 设置主题
    void setCssSytle(const QString&);  // set theme的help function
    void setLanguage(const QString&);  // 设置语言

    Ui::MainWindow *ui;

    QString orgFilePath = "";  // 文件路径

    // 子控件
    DropFrame* dropFrame = nullptr;
    ConverterProcess* processWidget = nullptr;

    // process相关
    QProcess* process = nullptr;
    bool isProcessRunning = false;
    int videoLength {};
    float previousPercentDone {};

    // sound
    QSound* sound = nullptr;

    // translator
    QTranslator* translator = nullptr;
};


#endif // MAINWINDOW_H
