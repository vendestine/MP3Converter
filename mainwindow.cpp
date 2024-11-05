#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取屏幕对象
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        // 获取屏幕的可用尺寸
        QRect screenGeometry = screen->availableGeometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();

        // 设置主窗口的大小
        int windowWidth = 470;  // 你可以根据需要设置窗口的宽度
        int windowHeight = 540; // 你可以根据需要设置窗口的高度
        this->resize(windowWidth, windowHeight);

        // 计算窗口的位置，使其居中
        int x = (screenWidth - windowWidth) / 2;
        int y = (screenHeight - windowHeight) / 2;
        this->move(x, y);
    }


    addSubWidget();

    setWindowTitle(tr("MP3 Converter"));


    // mainwindow捕获settings button的clicked信号
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
    // mainwindow捕获convert button的clicked信号
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onConvertButtonClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    int width=event->size().width();
    int height=event->size().height();
    ui->centralwidget->setGeometry((width - 470)/2, (height - 540) / 2, 470, 540);
}

void MainWindow::onSettingsButtonClicked()
{
    AppSettingsDialog settingsDialog;
    settingsDialog.exec();
}

void MainWindow::onConvertButtonClicked()
{
    processWidget->setHidden(false);  // 显示process控件

    // 测试convert process的两个public函数
    processWidget->setConvertFileName("mp3 file name");
    processWidget->updateProgress(50);
}

void MainWindow::closeProcessWidget()
{
    processWidget->setHidden(true);  // 隐藏process控件
}

void MainWindow::prepareConvert(QString filePath)
{
    orgFilePath = filePath;
    ui->titleLB->setText("Ready to Convert!");

    // 隐藏showFilebutton，startbutton不可用
    ui->startButton->setEnabled(true);
    ui->showFileButton->setHidden(true);
}

void MainWindow::addSubWidget()
{
    // 添加dropframe控件
    if (dropFrame == nullptr) {
        dropFrame = new DropFrame(ui->dropWidget);
        dropFrame->setAutoFillBackground(true);

        // dropframe控件填充进dropwidget
        QHBoxLayout* layout = new QHBoxLayout(ui->dropWidget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(dropFrame);
        ui->dropWidget->setLayout(layout);

        // mainwindow捕获dropframe的mediaFileSelect信号
        connect(dropFrame, SIGNAL(mediaFileSelect(QString)), this, SLOT(prepareConvert(QString)));
    }


    // 添加progress控件
    if (processWidget == nullptr) {
        processWidget = new ConverterProcess(ui->centralwidget);
        processWidget->setAutoFillBackground(true);
        processWidget->setHidden(true);  // 隐藏控件

        // mainwindow捕获convert process的convertProcessCancelButtonClicked信号
        connect(processWidget, SIGNAL(convertProcessCancelButtonClicked()), this, SLOT(closeProcessWidget()));
    }

    // 隐藏showFilebutton，startbutton可用
    ui->startButton->setEnabled(false);
    ui->showFileButton->setHidden(true);
}
