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
#include <QFileInfo>
#define UPDATELINK "https://raw.githubusercontent.com/cppJoker/EndofYearPPO/VisualC/Src/info.json"

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
    setTarget(UPDATELINK);
    download();
}

void ClientUpdate::setTarget(const QString &t) {
    this->target = t;
}
bool fileExists(QString path) {
	QFileInfo check_file(path);
	if (check_file.exists() && check_file.isFile()) {
		return true;
	}
	else {
		return false;
	}
}
void ClientUpdate::downloadFinished(QNetworkReply *data) {
	const QByteArray sdata = data->readAll();
	QString DataAsString(sdata);
	QFile localFile("info.json");
	if (fileExists("info.json") && DataAsString!="") {
		ui->label->setText("Preparation en cours...");
		localFile.remove();
	}
    else {
        ui->label->setText("Preparation en cours...");
	}
    if (!localFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
		ui->label->setText("Une erreur s'est produite [FA::403]");
		QTime dieTime = QTime::currentTime().addMSecs(2000);
		while (QTime::currentTime() < dieTime)
		{
			QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
		}
        QApplication::instance()->quit();
    }
    QTextStream out(&localFile);
    out << DataAsString;
    localFile.close();
    delete data;
    data = 0;
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
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



