#include "converterprocess.h"
#include "ui_converterprocess.h"

ConverterProcess::ConverterProcess(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConverterProcess)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);


    // converProcess widget捕获了cancel button的clicked信号
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
}

ConverterProcess::~ConverterProcess()
{
    delete ui;
}

void ConverterProcess::setConvertFileName(QString fileName)
{
    if (fileName.isEmpty()) return; // 文件为空直接返回

    ui->fileNameLB->setText(fileName);  // 设置转换后的文件名
}

void ConverterProcess::updateProgress(int value)
{
    if (value < 0 || value > 100) return;  // 非法value直接返回

    // 更新进度条和进度label
    ui->progressBar->setValue(value);
    ui->progressLB->setText(QString("%1%").arg(value) + tr("converted"));
}

void ConverterProcess::onCancelButtonClicked()
{
    emit convertProcessCancelButtonClicked();
}
