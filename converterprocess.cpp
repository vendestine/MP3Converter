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

void ConverterProcess::onCancelButtonClicked()
{
    emit convertProcessCancelButtonClicked();
}
