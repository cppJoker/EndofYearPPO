#ifndef IMAGEWINDOW1_H
#define IMAGEWINDOW1_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class ImageWindow1;
}

class ImageWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow1(QString namer = "",QString url = "",QWidget *parent = nullptr);
    void setflName(QString x){
        flName = x;
    }
    bool sett = false;
    ~ImageWindow1();

private:
    QString flName;


    Ui::ImageWindow1 *ui;
};

#endif // IMAGEWINDOW1_H
