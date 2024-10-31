#include "dropframe.h"
#include "ui_dropframe.h"

DropFrame::DropFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::DropFrame)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
}

DropFrame::~DropFrame()
{
    delete ui;
}
