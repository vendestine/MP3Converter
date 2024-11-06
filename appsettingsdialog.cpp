#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

AppSettingsDialog::AppSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppSettingsDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Settings dialog"));

    // appsettings dialog捕获push button的clicked信号
    connect(ui->loadPB, SIGNAL(clicked()), this, SLOT(onLoadButtonClicked()));
    connect(ui->cancelPB, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    connect(ui->savePB, SIGNAL(clicked()), this, SLOT(onSaveButtonClicked()));
    connect(ui->destinationPB, SIGNAL(clicked()), this, SLOT(onDestinationButtonClicked()));

    // appsettings dialog捕获 comboBox的index changed信号
    connect(ui->themesCB, SIGNAL(currentIndexChanged(QString)), this, SLOT(onThemesComboBoxChanged(QString)));
    connect(ui->languageCB,SIGNAL(currentIndexChanged(QString)), this, SLOT(onLanguagesComboBoxChanged(QString)));
    connect(ui->bitrateCB,SIGNAL(currentIndexChanged(QString)), this, SLOT(onBitRateComboBoxChanged(QString)));
    connect(ui->samplerateCB,SIGNAL(currentIndexChanged(QString)), this, SLOT(onSampleRateComboBoxChanged(QString)));

    // appsettings dialog捕获 checkbox的clicked信号
    connect(ui->finishsoundCHB, SIGNAL(clicked()), this, SLOT(onFinishSoundCheckBoxClicked()));
}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}

void AppSettingsDialog::onLoadButtonClicked()
{

}

void AppSettingsDialog::onCancelButtonClicked()
{
    reject();
    qDebug() << "cancel";
}

void AppSettingsDialog::onSaveButtonClicked()
{
    reject();
    qDebug() << "save";
}

void AppSettingsDialog::onDestinationButtonClicked()
{
    QString path = QFileDialog::getExistingDirectory(
        this,
        tr("Open Music file"),
        QStandardPaths::writableLocation(QStandardPaths::MoviesLocation),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (!path.isEmpty()) {
        ui->destinationLE->setText(path);
        qDebug() << "destination set";
    }
}

void AppSettingsDialog::onThemesComboBoxChanged(QString str)
{
    if (str.isEmpty()) return;

    if(str == "default-yellow") setCssStylesheet(":/style/app_settings_yellow.css");
    else if(str == "blue-style")  setCssStylesheet(":/style/app_settings_blue.css");
    else if(str == "black-style") setCssStylesheet(":/style/app_settings_black.css");
}

void AppSettingsDialog::onLanguagesComboBoxChanged(QString str)
{
    if (str.isEmpty()) return;
}

void AppSettingsDialog::onBitRateComboBoxChanged(QString str)
{
    if (str.isEmpty()) return;
}

void AppSettingsDialog::onSampleRateComboBoxChanged(QString str)
{
    if (str.isEmpty()) return;
}

void AppSettingsDialog::onFinishSoundCheckBoxClicked()
{
    if (ui->finishsoundCHB->isChecked()) {

    }
    else {

    }
}

void AppSettingsDialog::setCssStylesheet(const QString &style)
{
    QFile qss(style);

    // 检查文件是否存在
    if (!qss.exists()) {
        qWarning() << "Stylesheet file does not exist:" << style;
        return;
    }

    // 尝试打开文件
    if (!qss.open(QFile::ReadOnly)) {
        qWarning() << "Failed to open stylesheet file:" << style;
        return;
    }

    // 设置样式表
    qApp->setStyleSheet(qss.readAll());
}
