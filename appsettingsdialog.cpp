#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QMessageBox>
#include "appsettingsmanager.h"

AppSettingsDialog::AppSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppSettingsDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Settings dialog"));
    loadSettings();

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
    AppSettingsManager::getInstance().setAppDefaultSettings();
    loadSettings();
}

void AppSettingsDialog::onCancelButtonClicked()
{
    reject();
}

void AppSettingsDialog::onSaveButtonClicked()
{
    // 数据落盘
    AppSettingsManager::getInstance().writeRecords();
    reject();

    // 弹窗
    QMessageBox::information(this,tr("Information"),tr("Note: The language change will take effect after restart this App."),QMessageBox::Ok);
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
        // 设置settings的destination的内容
        AppSettingsManager::getInstance().setDestinitionString(path);
    }
}

void AppSettingsDialog::onThemesComboBoxChanged(const QString& str)
{
    if (str.isEmpty()) return;

    // 加载不同皮肤
    if(str == "default-yellow") setCssStylesheet(":/style/app_settings_yellow.css");
    else if(str == "blue-style")  setCssStylesheet(":/style/app_settings_blue.css");
    else if(str == "black-style") setCssStylesheet(":/style/app_settings_black.css");

    // 设置settings的theme内容
    AppSettingsManager::getInstance().setThememsString(str);
}

void AppSettingsDialog::onLanguagesComboBoxChanged(const QString& str)
{
    if (str.isEmpty()) return;

    // 设置settings的language
    AppSettingsManager::getInstance().setLanguageString(str);
}

void AppSettingsDialog::onBitRateComboBoxChanged(const QString& str)
{
    if (str.isEmpty()) return;

    // 设置settings的bitrate
    AppSettingsManager::getInstance().setBitrateString(str);
}

void AppSettingsDialog::onSampleRateComboBoxChanged(const QString& str)
{
    if (str.isEmpty()) return;

    // 设置settings的sample rate
    AppSettingsManager::getInstance().setSamplerateString(str);
}

void AppSettingsDialog::onFinishSoundCheckBoxClicked()
{
    // 设置settings的sound switch
    if (ui->finishsoundCHB->isChecked()) {
        AppSettingsManager::getInstance().setFinishSoundStr("YES");
    }
    else {
        AppSettingsManager::getInstance().setFinishSoundStr("NO");
    }
}

void AppSettingsDialog::loadSettings()
{
    // 从 AppSettingsManager 中读取设置记录
    AppSettingsManager::getInstance().readRecords();

    // 获取各项设置的值
    QString themesStr       = AppSettingsManager::getInstance().getThememsString();
    QString languagesStr    = AppSettingsManager::getInstance().getLanguageString();
    QString destinitionStr  = AppSettingsManager::getInstance().getDestinitionString();
    QString bitRateStr      = AppSettingsManager::getInstance().getBitrateString();
    QString sampleRateStr   = AppSettingsManager::getInstance().getSamplerateString();
    QString finishSoundStr  = AppSettingsManager::getInstance().getFinishSoundStr();

    // 检查是否有任何设置项为空，如果有则直接返回
    if (themesStr.isEmpty() || languagesStr.isEmpty() || destinitionStr.isEmpty() ||
        bitRateStr.isEmpty() || sampleRateStr.isEmpty() || finishSoundStr.isEmpty()) {
        return;
    }

    // settings dialog填入信息
    ui->destinationLE->setText(destinitionStr);
    setComboBoxIndex(ui->themesCB, themesStr);
    setComboBoxIndex(ui->languageCB, languagesStr);
    setComboBoxIndex(ui->bitrateCB, bitRateStr);
    setComboBoxIndex(ui->samplerateCB, sampleRateStr);
    ui->finishsoundCHB->setChecked(finishSoundStr == "YES");
}

void AppSettingsDialog::setComboBoxIndex(QComboBox* comboBox, const QString& text) {
    int index = comboBox->findText(text);
    if (index >= 0 && index < 20) {
        // 设置comboBox的选项
        comboBox->setCurrentIndex(index);
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
