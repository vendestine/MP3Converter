#ifndef CONVERTERPROCESS_H
#define CONVERTERPROCESS_H

#include <QWidget>

namespace Ui {
class ConverterProcess;
}

class ConverterProcess : public QWidget
{
    Q_OBJECT

public:
    explicit ConverterProcess(QWidget *parent = nullptr);
    ~ConverterProcess();

    void setConvertFileName(QString fileName);   // 设置转换后的文件名
    void updateProgress(int value);   // 更新进度条和进度label

signals:
    void convertProcessCancelButtonClicked();

private slots:
    void onCancelButtonClicked();

private:
    Ui::ConverterProcess *ui;
};

#endif // CONVERTERPROCESS_H
