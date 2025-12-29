#include "mouseevent.h"
#include <QStatusBar>
#include <QLabel>
#include<qdebug>
MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("測試滑鼠事件"));

    statusLabel = new QLabel;
    statusLabel->setText(QStringLiteral("指標位置"));
    statusLabel->setFixedWidth(100);

    mousePosLabel = new QLabel;   // ← 改成小寫 m
    mousePosLabel->setText(tr(" "));
    mousePosLabel->setFixedWidth(100);

    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(mousePosLabel);

    setMouseTracking(true);
    resize(400,300);
}

MouseEvent::~MouseEvent() {}

void MouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    mousePosLabel->setText(str);
}


void MouseEvent::mousePressEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";

    if (event->button() == Qt::LeftButton) {
        statusBar()->showMessage(QStringLiteral("左鍵:") + str);
    } else if (event->button() == Qt::RightButton) {
        statusBar()->showMessage(QStringLiteral("右鍵:") + str);
    } else if (event->button() == Qt::MiddleButton) {
        statusBar()->showMessage(QStringLiteral("中鍵:") + str);
    }
    qDebug()<<"按壓";
}


void MouseEvent::mouseReleaseEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + "," +
                  QString::number(event->y()) + ")";
    statusBar()->showMessage(QStringLiteral("釋放:") + str);
    qDebug()<<"釋放";
}






