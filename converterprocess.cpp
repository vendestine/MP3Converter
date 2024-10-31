#include "converterprocess.h"
#include "ui_converterprocess.h"

ConverterProcess::ConverterProcess(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConverterProcess)
{
    ui->setupUi(this);
}

ConverterProcess::~ConverterProcess()
{
    delete ui;
}
