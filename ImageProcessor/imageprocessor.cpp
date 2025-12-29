#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QStatusBar>

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

    imgWin->setMouseTracking(true);
    central->setMouseTracking(true);
    setMouseTracking(true);

    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    statusLabel = new QLabel("狀態: 就緒", this);
    mousePosLabel = new QLabel("(0,0) Gray: -", this);
    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(mousePosLabel);

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

void ImageProcessor::mouseMoveEvent(QMouseEvent *event)
{
    if (!img.isNull())
    {
        QPoint pos = imgWin->mapFromParent(event->pos());
        if (pos.x() >= 0 && pos.x() < img.width() &&
            pos.y() >= 0 && pos.y() < img.height())
        {
            int gray = qGray(img.pixel(pos.x(), pos.y()));
            mousePosLabel->setText(QString("(%1,%2) Gray: %3")
                                       .arg(pos.x()).arg(pos.y()).arg(gray));
        }
        else
        {
            mousePosLabel->setText("(-,-) Gray: -");
        }
    }
}

void ImageProcessor::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = imgWin->mapFromParent(event->pos());
    QString str = QString("(%1,%2)").arg(pos.x()).arg(pos.y());

    if (event->button() == Qt::LeftButton)
        statusLabel->setText(QStringLiteral("左鍵按下: ") + str);
    else if (event->button() == Qt::RightButton)
        statusLabel->setText(QStringLiteral("右鍵按下: ") + str);
    else if (event->button() == Qt::MiddleButton)
        statusLabel->setText(QStringLiteral("中鍵按下: ") + str);
}

void ImageProcessor::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = imgWin->mapFromParent(event->pos());
    QString str = QString("(%1,%2)").arg(pos.x()).arg(pos.y());
    statusLabel->setText(QStringLiteral("釋放: ") + str);
}
