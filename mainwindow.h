#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "dropframe.h"
#include "converterprocess.h"
#include "appsettingsdialog.h"

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
    void onConvertButtonClicked();    // convert button点击事件
    void closeProcessWidget();        // convert process控件cancel后，关闭process widget
    void prepareConvert(QString filePath);          // dropframe控件，文件选择后，准备convert

private:
    void addSubWidget();

    Ui::MainWindow *ui;

    QString orgFilePath = "";  // 文件路径


    // 子控件
    DropFrame* dropFrame = nullptr;
    ConverterProcess* processWidget = nullptr;
};


#endif // MAINWINDOW_H
