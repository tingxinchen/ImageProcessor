#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QColor>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent), gWin(nullptr)
{
    setWindowTitle(QStringLiteral("影像處理"));

    central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    imgWin = new QLabel();
    QPixmap initPixmap(300, 200);
    initPixmap.fill(QColor(255, 255, 255));

    imgWin->setFixedSize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(initPixmap);

    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor()
{
    if (gWin) delete gWin;
}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟檔案(&O)"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    exitAction = new QAction(QStringLiteral("結束(&Q)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, &QAction::triggered, [this]() {
        if (gWin) gWin->close();
        this->close();
    });

    geometryAction = new QAction(QStringLiteral("幾何轉換"), this);
    geometryAction->setShortcut(tr("Ctrl+G"));
    geometryAction->setStatusTip(QStringLiteral("影像幾何轉換"));
    connect(geometryAction, &QAction::triggered, this, &ImageProcessor::showGeometryTransform);
}

void ImageProcessor::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);
    fileMenu->addAction(geometryAction);
    QMenu *toolsMenu = menuBar()->addMenu(QStringLiteral("Tools"));
    toolsMenu->addAction(geometryAction);
}

void ImageProcessor::createToolBars()
{
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(geometryAction);
    fileTool->addAction(geometryAction);
}

void ImageProcessor::loadFile(const QString &filename)
{
    qDebug() << QString("file name: %1").arg(filename);
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showOpenFile()
{
    QString file = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("開啟影像"),
        tr("."),
        "BMP (*.bmp);;PNG (*.png);;JPEG (*.jpg)"
        );

    if (!file.isEmpty())
    {
        filename = file;
        loadFile(filename);
    }
}

void ImageProcessor::showGeometryTransform()
{
    if (!gWin)
        gWin = new GTransFrom(nullptr);

    if (!img.isNull()) {
        gWin->srcImg = img;
        gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImg));
    }

    gWin->resize(500, 400);
    gWin->show();
    gWin->raise();
    gWin->activateWindow();
}
