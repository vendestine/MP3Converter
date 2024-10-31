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


    // mainwidnow捕获settings button的clicked信号
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
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

void MainWindow::addSubWidget()
{
    // 添加dropframe控件
    if (dropFrame == nullptr) {
        dropFrame = new DropFrame(ui->dropWidget);
        dropFrame->setAutoFillBackground(true);
    }

    // dropframe控件填充进dropwidget
    QHBoxLayout* layout = new QHBoxLayout(ui->dropWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(dropFrame);
    ui->dropWidget->setLayout(layout);

    // 添加progress控件
    if (processWidget == nullptr) {
        processWidget = new ConverterProcess(ui->centralwidget);
        processWidget->setAutoFillBackground(true);
        processWidget->setHidden(true);
    }


}
