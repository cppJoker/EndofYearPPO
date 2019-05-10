#include "mainwindow.h"
#include "clientupdate.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientUpdate clientw;
    clientw.show();
    while(clientw.isVisible()){
        QTime dieTime = QTime::currentTime().addMSecs(500);
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
    MainWindow w;
    w.show();

    return a.exec();
}
