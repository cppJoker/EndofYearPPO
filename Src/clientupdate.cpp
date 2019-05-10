#include "clientupdate.h"
#include "ui_clientupdate.h"
#include "QLabel"
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QCoreApplication>
#include <QUrl>
#include <QMessageBox>
#include <QTextCodec>
#include <QFile>


ClientUpdate::ClientUpdate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientUpdate)
{
    ui->setupUi(this);
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished(QNetworkReply*)));
    setLayout(ui->gridLayout);
    ui->centralwidget->setLayout(ui->gridLayout);
    QLabel * footer = new QLabel("Mohamed A. Laghrour || Relations et fonctions || PPO");
    footer->setAlignment(Qt::AlignHCenter);
    ui->statusbar->addWidget(footer);
    setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::Window | Qt::FramelessWindowHint);
    QObject::connect(this, SIGNAL(done()), this, SLOT(close()));
    setTarget("https://stackoverflow.com/questions/14131127/qbytearray-to-qstring.html");
    download();
}

void ClientUpdate::setTarget(const QString &t) {
    this->target = t;
}

void ClientUpdate::downloadFinished(QNetworkReply *data) {
    QFile localFile("downloadedfile.html");
    if (!localFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        QApplication::instance()->quit();
    }
    const QByteArray sdata = data->readAll();
    QString DataAsString(sdata);
    QTextStream out(&localFile);
    out << DataAsString;
    localFile.close();
    delete data;
    data = 0;
    emit done();
}

void ClientUpdate::download() {
    QUrl url = QUrl::fromEncoded(this->target.toLocal8Bit());
    QNetworkRequest request(url);
    QObject::connect(manager.get(request), SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
}

void ClientUpdate::downloadProgress(qint64 recieved, qint64 total) {
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(recieved);
}

ClientUpdate::~ClientUpdate()
{
    delete ui;
}



