#include "mainwindow.h"
#include "clientupdate.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientUpdate clientw;
    clientw.show();
	int deadline = 0;
    while(clientw.isVisible()){
        QTime dieTime = QTime::currentTime().addMSecs(500);
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
		deadline+=1;
		if (deadline = 20) {
			break;
		}
    }
	clientw.close();
    MainWindow w;
    w.show();

    return a.exec();
}
