#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QDebug>
#include <QApplication>
#include <QFileInfo>
#include <QDesktopServices>

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

    // 创建process对象，设置读取通道，然后处理process的事件
    process = new QProcess(this);
    process->setReadChannel(QProcess::StandardOutput);
    connect(process,SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessReadyReadStandardOutput()));
    connect(process,SIGNAL(readyReadStandardError()), this, SLOT(onProcessReadyReadStandardError()));
    connect(process,SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessErrorOccured(QProcess::ProcessError)));


    setWindowTitle(tr("MP3 Converter"));
    addSubWidget();


    // mainwindow捕获settings button的clicked信号
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
    // mainwindow捕获convert button的clicked信号
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onConvertButtonClicked()));
    // mainwindow捕获showfile button的clicked信号
    connect(ui->showFileButton, SIGNAL(clicked()), this, SLOT(onShowFileButton()));
    // mainwindow捕获help button的clicked信号
    connect(ui->helpButton, SIGNAL(clicked()), this, SLOT(onHelpButtonClicked()));

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

void MainWindow::onHelpButtonClicked()
{
    const QUrl url("https://convertio.co/zh/audio-converter/");
    QDesktopServices::openUrl(url);
}

void MainWindow::onConvertButtonClicked()
{
    // 异常处理
    if (orgFilePath.isEmpty()) return;
    if (dropFrame == nullptr) return;
    if (isProcessRunning) return;


    //ffmpeg可执行文件路径
    QString ffmpegPath = QApplication::applicationDirPath()+"/../../../Resources/ffmpeg.exe";

    // 转换后的MP3文件路径
    QString mp3Path = "";

    // 得到mp3文件路径
    QFileInfo fileInfo = QFileInfo(orgFilePath);
    if(fileInfo.exists())
    {
        mp3Path=fileInfo.path()+"/"+fileInfo.completeBaseName()+".mp3";

        int count = 1; // 用于生成唯一名称的计数器
        while (QFileInfo::exists(mp3Path)) {
            mp3Path = fileInfo.path() + "/" + fileInfo.completeBaseName() + "-" + QString::number(count++) + ".mp3";
        }
    }
    qDebug()<< "MP3 PATH: " << mp3Path;

    // 如果mp3路径为空，直接返回
    if(mp3Path.isEmpty())return;

    // 拼接ffmpeg命令
    QStringList execStrList;
    execStrList<<"-i"<<orgFilePath<<"-b:a"<<"192000"<<"-acodec"<<"libmp3lame"<<"-ar"<<"44100"<<"-y"<<mp3Path;
    qDebug()<<"EXEC CMD:::::"<<ffmpegPath<<" "<<execStrList;

    // 执行命令
    process->start(ffmpegPath,execStrList);

    // 设置convert process界面
    processWidget->setConvertFileName(fileInfo.fileName());
    processWidget->updateProgress(0);

    // 设置process相关
    isProcessRunning = true;
    videoLength = 0;
    previousPercentDone=0;

    processWidget->setHidden(false);  // 显示convert process控件

}

void MainWindow::onShowFileButton()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ventu/Videos/Desktop"));
}

void MainWindow::closeProcessWidget()
{
    if (process->state() == QProcess::Running) {
        process->kill();
        process->waitForFinished(-1); // wait indefinitely
    }

    isProcessRunning = false;
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

void MainWindow::onProcessReadyReadStandardOutput()
{
    QByteArray output=process->readAllStandardOutput();
    qDebug()<<"Standard Output: "<<output;
}

void MainWindow::onProcessReadyReadStandardError()
{
    // 解析标准错误流里的内容
    QByteArray output= process->readAllStandardError();

    qDebug()<<"StandardError: "<<output;

    char buf[output.length()+1];

    int usedLength=output.length();

    if(usedLength == 0){
        return;
    }
    buf[usedLength] = 0;

    memcpy(buf,output.data(),output.length());
    char *p = 0;

    if(videoLength == 0)
    {
        char durStr[256];
        strcpy(durStr,"Duration:");

        if(strlen(buf) >= strlen(durStr))
        {
            p = strstr(buf,durStr);
            if(p && strlen(p) >= strlen(durStr) + 9)
            {
                p += strlen(durStr) + 1;
                videoLength = 0;

                float components[3];
                sscanf(p,"%f:%f:%f",components,components+1, components+2);
                for(int i=2, mult=1; i>=0; i--, mult *= 60)
                    videoLength += components[i]  * mult;

            }
        }
    }

    float curTime = 0;
    if(strlen(buf) > strlen("time=00:00:00.00")+1 && (p=strstr(buf,"time="))) {
        float hours, minutes, seconds;
        sscanf(p+strlen("time="),"%f:%f:%f", &hours, &minutes, &seconds);//sscanf 读取格式化的字符串中的数据,支持正则表达式。
        curTime = hours*3600+minutes*60+seconds;
    }

    if(strlen(buf) > strlen("\"position\":")+1 && (p=strstr(buf,"\"position\":")))
    {
        sscanf(p+strlen("\"position\":"),"%f", &curTime);
    }

    if(videoLength)
    {
        if(curTime)
        {
            float percent = curTime / videoLength * 100;
            if(previousPercentDone && percent - previousPercentDone > 50)
            {
                percent = previousPercentDone;
            }
            if(percent > 100)
            {
                percent = 100;
            }
            previousPercentDone = percent;

            //qDebug()<<"Percent: "<<(int)percent;

            processWidget->updateProgress((int)percent);
        }
    }

    // 转化完成以后 将其他控件show出来
    if(strlen(buf)>strlen("muxing overhead") &&(p=strstr(buf,"muxing overhead")))
    {
        processWidget->setHidden(true);
        ui->showFileButton->setHidden(false);
        ui->titleLB->setText(tr("Finished Convertring!"));
        isProcessRunning = false;
    }
}

void MainWindow::onProcessErrorOccured(QProcess::ProcessError error)
{
    qDebug()<<"Error:"<<error;
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


    // 添加process控件
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
