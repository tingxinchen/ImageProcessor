#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
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

private:
    GTransFrom *gWin;
    QWidget *central;
    QMenu *fileMenu;
    QToolBar *fileTool;

    QImage img;
    QString filename;
    QLabel *imgWin;

    QAction *openFileAction;
    QAction *exitAction;
    QAction *geometryAction;
};

#endif // IMAGEPROCESSOR_H
