#ifndef DROPFRAME_H
#define DROPFRAME_H

#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>

namespace Ui {
class DropFrame;
}

class DropFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DropFrame(QWidget *parent = nullptr);
    ~DropFrame();

signals:
    void mediaFileDrop(QString filePath);   // drop文件信号

protected:
    void dragEnterEvent(QDragEnterEvent* event);   // drag事件函数
    void dropEvent(QDropEvent* event);             // drop事件函数

private slots:
    void onBrowseButtonClicked();                  // browse button点击事件

private:
    Ui::DropFrame *ui;

    QString orgFilePath;    // 文件路径

    void setFileNameToLabel();  // 得到文件名，然后set到label上
};

#endif // DROPFRAME_H
