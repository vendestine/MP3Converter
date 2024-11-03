#include "dropframe.h"
#include "ui_dropframe.h"
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QUrl>
#include <QStandardPaths>

DropFrame::DropFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::DropFrame)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);

    //dropdrame捕获 browsebutton的clicked信号
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(onBrowseButtonClicked()));
}

DropFrame::~DropFrame()
{
    delete ui;
}

void DropFrame::dragEnterEvent(QDragEnterEvent * event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }

    qDebug() << "dragEnterEvent: ";
}

void DropFrame::dropEvent(QDropEvent * event)
{
    // 从拖放事件的 MIME 数据中获取第一个 URL
    QUrl url = event->mimeData()->urls().first();
    if (url.isEmpty()) return;

    // 先将url转化为utf-8字节数组，再编码成url，为了支持中文
    QUrl encodedUrl = QUrl::fromEncoded(url.toString().toUtf8());

    // 得到路径名，然后显示名称到nameLabel上
    orgFilePath=encodedUrl.toLocalFile();

    // qDebug() << orgFilePath;
    setFileNameToLabel();
}

void DropFrame::onBrowseButtonClicked()
{
    // 打开文件选择对话框
    QString filepath = QFileDialog::getOpenFileName(
        this,                                // 父窗口
        tr("Open Music file"),               // 对话框标题
        QStandardPaths::writableLocation(QStandardPaths::MoviesLocation), // 默认目录
        tr("Music Files (*.mp4 *.mp3)")      // 文件过滤器
        );

    // 检查是否有选择的文件
    if (!filepath.isEmpty())
    {
        orgFilePath = filepath; // 储存用户选择的文件路径
        setFileNameToLabel();
    }
    // 没有选择文件则什么都不做
}


void DropFrame::setFileNameToLabel()
{
    QFileInfo fileInfo(orgFilePath);

    if (fileInfo.exists()) {
        QString fileName = fileInfo.fileName();     // 获取文件名

        if (!fileName.isEmpty()) {                  // 使用 isEmpty() 方法检查字符串是否为空
            ui->fileNameLB->setText(fileName);      // 设置标签文本
            emit mediaFileDrop(orgFilePath);        // 发送drop信号
        }
    }
}
