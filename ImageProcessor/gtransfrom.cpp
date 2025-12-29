#include "gtransfrom.h"
#include <QPixmap>
#include <QSizePolicy>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

GTransFrom::GTransFrom(QWidget *parent)
    : QWidget(parent)
{

    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout (this);
    mirrorGroup = new QGroupBox (QStringLiteral("鏡射"),this);
    groupLayout = new QVBoxLayout (mirrorGroup);
    hCheckBox = new QCheckBox (QStringLiteral("水平"),mirrorGroup);
    vCheckBox = new QCheckBox (QStringLiteral("垂直"),mirrorGroup);
    mirrorButton = new QPushButton (QStringLiteral("執行"), mirrorGroup);
    hCheckBox->setGeometry (QRect (13, 28, 87, 19));
    vCheckBox->setGeometry (QRect(13, 54, 87, 19));
    mirrorButton->setGeometry (QRect (13, 80, 93, 28));
    groupLayout->addWidget (hCheckBox);
    groupLayout->addWidget (vCheckBox);
    groupLayout->addWidget (mirrorButton);
    leftLayout->addWidget (mirrorGroup);
    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    vSpacer = new QSpacerItem (20, 58, QSizePolicy:: Minimum,
                              QSizePolicy:: Expanding);
    leftLayout->addWidget (rotateDial);
    leftLayout->addItem(vSpacer);
    mainLayout->addLayout (leftLayout);
    inWin = new QLabel (this);
    inWin->setScaledContents(true);
    QPixmap *initPixmap= new QPixmap (300,200);
    initPixmap->fill(QColor(255,255,255));
    inWin->setPixmap (*initPixmap);
    inWin->setSizePolicy (QSizePolicy:: Expanding, QSizePolicy:: Expanding);
    QPainter *paint = new QPainter (initPixmap);
    paint->setPen (*(new QColor(0,0,0)));
    paint->begin(initPixmap);
    paint->drawRect(15,15,60,40);
    paint->end();
    if (srcImg.isNull())
    {
        srcImg=initPixmap->toImage();
    }


    mainLayout->addWidget(inWin);
    connect (mirrorButton, SIGNAL (clicked()),this, SLOT (mirroredImage()));
    connect (rotateDial, SIGNAL (valueChanged(int)), this, SLOT (rotatedImage()));

    saveButton = new QPushButton(QStringLiteral("存檔"), this);
    leftLayout->addWidget(saveButton);

    connect(saveButton, SIGNAL(clicked()),
            this, SLOT(saveImage()));
}

GTransFrom::~GTransFrom() {}
void GTransFrom::mirroredImage()
{
    bool H,V;
    if (srcImg.isNull())
        return;
    H=hCheckBox->isChecked();
    V=vCheckBox->isChecked();
    dstImg=srcImg.mirrored (H, V);
    inWin->setPixmap (QPixmap:: fromImage (dstImg));
    srcImg=dstImg;
}
void GTransFrom::rotatedImage ()
{
    QTransform tran;
    int angle;
    if (srcImg.isNull())
        return;
    angle=rotateDial->value();
    tran.rotate (angle);
    dstImg = srcImg.transformed (tran);
    inWin->setPixmap (QPixmap:: fromImage (dstImg));
}
void GTransFrom::saveImage()
{
    if (srcImg.isNull())
        return;

    QString fileName = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("儲存"),
        "",
        "PNG (*.png);"
        );

    if (fileName.isEmpty())
        return;

    if (!srcImg.save(fileName)) {
        QMessageBox::warning(this,
                             QStringLiteral("錯誤"),
                             QStringLiteral("存檔失敗"));
    }
}

