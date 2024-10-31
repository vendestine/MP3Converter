#ifndef DROPFRAME_H
#define DROPFRAME_H

#include <QFrame>

namespace Ui {
class DropFrame;
}

class DropFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DropFrame(QWidget *parent = nullptr);
    ~DropFrame();

private:
    Ui::DropFrame *ui;
};

#endif // DROPFRAME_H
