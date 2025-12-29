#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include "GTransFrom.h"

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();

    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(const QString &filename);

private slots:
    void showOpenFile();
    void showGeometryTransform();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    GTransFrom *gWin;
    QWidget *central;
    QMenu *fileMenu;
    QToolBar *fileTool;

    QImage img;
    QString filename;
    QLabel *imgWin;

    QLabel *statusLabel;
    QLabel *mousePosLabel;

    QAction *openFileAction;
    QAction *exitAction;
    QAction *geometryAction;
};

#endif // IMAGEPROCESSOR_H
