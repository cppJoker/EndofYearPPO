#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculator.h"
#include <QLineEdit>
#include "exercise.h"
#include <QCloseEvent>
#include "imagewindow1.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
    Exercise * exer;
    void InitExercices();
    QMainWindow * window = new QMainWindow();
private slots:
    void closeEvent (QCloseEvent *event);
    void on_pushButton_2_clicked();
    void GenerateChart(std::vector<Coords> coord1, std::vector<Coords> coord2);
    void GenerateRule (QString a, QString b, QLineEdit * lineEdit);
    void on_TrouverB_X_textChanged(const QString &arg1);

    void on_TrouverB_Y_textChanged(const QString &arg1);

    void on_TrouverB_A_textChanged(const QString &arg1);

    void on_TrouverX_Y_textChanged(const QString &arg1);

    void on_TrouverX_A_textChanged(const QString &arg1);

    void on_TrouverX_B_textChanged(const QString &arg1);

    void on_TrouverY_X_textChanged(const QString &arg1);

    void on_TrouverY_A_textChanged(const QString &arg1);

    void on_TrouverY_B_textChanged(const QString &arg1);

    void on_Demarche1_A_textChanged(const QString &arg1);

    void on_Demarche1_B_textChanged(const QString &arg1);

    void on_Demarche2_A_textChanged(const QString &arg1);

    void on_Demarche2_B_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_MainWindow_destroyed();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_Demarche1_Regle_textChanged(const QString &arg1);

    void on_Exer_Reset_clicked();

    void on_Exer_NextBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
