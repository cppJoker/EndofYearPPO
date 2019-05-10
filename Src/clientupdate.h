#ifndef CLIENTUPDATE_H
#define CLIENTUPDATE_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QCoreApplication>
#include <QUrl>
#include <QFile>

namespace Ui {
class ClientUpdate;
}

class ClientUpdate : public QMainWindow
{
    Q_OBJECT

private:
    QNetworkAccessManager manager;
    QNetworkReply* reply = NULL;
    QString target = "";

signals:
    void done();
public:
    explicit ClientUpdate(QWidget *parent = nullptr);
    ~ClientUpdate();
    Ui::ClientUpdate *ui;
    void setTarget(const QString& t);
public slots:
    void download();
    void downloadFinished(QNetworkReply* data);
    void downloadProgress(qint64 recieved, qint64 total);


};

#endif // CLIENTUPDATE_H
