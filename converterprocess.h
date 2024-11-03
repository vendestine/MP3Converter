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

signals:
    void convertProcessCancelButtonClicked();

private slots:
    void onCancelButtonClicked();

private:
    Ui::ConverterProcess *ui;
};

#endif // CONVERTERPROCESS_H
