#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QStatusBar>
#include <QLabel>

class MouseEvent : public QMainWindow
{
    Q_OBJECT

public:
    // 建構與解構
    MouseEvent(QWidget *parent = nullptr);
    ~MouseEvent();

protected:
    // 滑鼠事件函數
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel *statusLabel;    // 狀態列文字
    QLabel *mousePosLabel;  // 滑鼠座標顯示
};

#endif // MOUSEEVENT_H
