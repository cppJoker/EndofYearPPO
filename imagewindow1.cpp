#include "imagewindow1.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QThread>
#include "ui_imagewindow1.h"

QString read(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly |
                  QFile::Text))
    {
        return "";
    }

    QTextStream in(&file);
    QString myText = in.readAll();

    // put QString into qDebug stream
    file.close();
    return myText;


}

ImageWindow1::ImageWindow1(QString namer,QString url,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageWindow1)
{
    ui->setupUi(this);
    setWindowTitle(namer);
    ui->centralwidget->setLayout(ui->gridLayout);
    setLayout(ui->gridLayout);
    QPixmap mypix (url);
    ui->label->setPixmap(mypix);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}

ImageWindow1::~ImageWindow1()
{
    delete ui;
}
