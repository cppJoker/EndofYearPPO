#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include <QLabel>
#include "calculator.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <thread>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QCategoryAxis>
#include <QTextStream>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <vector>
#include "imagewindow1.h"
#include <QCloseEvent>

using namespace QtCharts;

bool doesHaveChar(QString & str){
    for (int i = 0; i < str.length(); i++) {
        QChar c = str[i];
        if(c == ','){
            str[i] = '.';
        }
    }
    for (int i = 0; i < str.length(); i++) {
       QChar c = str[i];
       if(c.isLetter()){
            return true;
       }

    }
    return false;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(window->isVisible())
    window->close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

void MainWindow::Init(){
    ui->checkBox->setChecked(false);
    setWindowTitle("Secondaire 3: Relations et fonctions");
    ui->centralWidget->setLayout(ui->gridLayout);
    ui->tab->setLayout(ui->gridLayout_2);
    ui->tab_4->setLayout(ui->gridLayout_5);
    ui->tab_2->setLayout(ui->gridLayout_3);
    ui->tab_3->setLayout(ui->gridLayout_4);
    ui->tab_6->setLayout(ui->gridLayout_6);
    //ui->tab_7->setLayout(ui->gridLayout_9);
    ui->tab_10->setLayout(ui->gridLayout_7);
    ui->tab_11->setLayout(ui->gridLayout_8);
    //ui->tab_12->setLayout(ui->gridLayout_10);
    QLabel *author = new QLabel();
    author->setText("Auteur: Mohamed A. Laghrour || <b>Utilisation personelle</b>");
    statusBar()->addWidget(author);
    setFixedSize(size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    std::vector<Coords> cord1;
    std::vector<Coords> cord2;
    QString SRegle1_A = ui->Demarche1_A->text();
    QString SRegle1_B = ui->Demarche1_B->text();
    QString SRegle2_A = ui->Demarche2_A->text();
    QString SRegle2_B = ui->Demarche2_B->text();

    if(doesHaveChar(SRegle1_A) || doesHaveChar(SRegle1_B) || doesHaveChar(SRegle2_A) || doesHaveChar(SRegle2_B)){
        return;
    }
    double Regle1_A = SRegle1_A.toDouble();
    double Regle1_B = SRegle1_B.toDouble();
    double Regle2_A = SRegle2_A.toDouble();
    double Regle2_B = SRegle2_B.toDouble();
    if(Regle1_A == Regle2_A){
        ui->Demarche_Edit->setHtml("<dl style=\"text-align:center\"> Calcul impossible: <b>A1 = A2</b> </dl>");
        return;
    }

    double R1 = Regle2_A - Regle1_A;
    double R2 = R1 - Regle2_B;
    double R = Regle1_B - Regle2_B;
    double R3 = R/R1;

    double res1 = 0;
    {
    double x = R3;
    double a = Regle1_A;
    double b = Regle1_B;
    res1 =(a*x) + b;
    }
    ui->Demarche_Edit->setHtml(
                "<dl style=\"text-align:center\"><b>Demarche:</b>"
                "<br>""<br>"
                "Etape 1: <b>Substitution</b>"
                "<br>"
                + ui->Demarche1_A->text() + "x + " + ui->Demarche1_B->text() + " = " + ui->Demarche2_A->text() + "x + " + ui->Demarche2_B->text() +
                "<br>""<br>"
                "Etape 2: <b>Isoler b et x</b> <br>"
                + ui->Demarche1_A->text() + "x <b style=\"color: red\">(-"+ ui->Demarche1_A->text() +")</b> + " + ui->Demarche1_B->text() + " = " + ui->Demarche2_A->text() + "x <b style=\"color: red\">(-"+ ui->Demarche1_A->text() +")</b> + " + ui->Demarche2_B->text()+
                "<br>"
                + ui->Demarche1_B->text() + " = " + QString::number(R1) + "x + " + ui->Demarche2_B->text() + ""
                "<br>""<br>"
                "Etape 3: <b>Isoler x</b><br>"+
                ui->Demarche1_B->text() + " <b style=\"color: red\">(-"+ui->Demarche2_B->text()+")</b> = " + QString::number(R1) + "x + " + ui->Demarche2_B->text() +" <b style=\"color: red\">(-"+ui->Demarche2_B->text()+")</b>" +
                "<br>"+
                QString::number(R) + " = " + QString::number(R1) + "x"
                "<br>""<br>"
                "Etape 4: <b>Trouver x</b><br>"+
                QString::number(R)+ " <b style=\"color: red\">(÷"+QString::number(R1)+"x)</b>" + " = " + QString::number(R1) + "x <b style=\"color: red\">(÷"+QString::number(R1)+"x)</b>" +
                "<br>"+
                QString::number(R3)+ " = x || "+ QString::number(res1)+" = y"
                "</dl>");
    //Graphique
    if(ui->checkBox->isChecked()){
        double lookedx = R3 - ui->lineEdit->text().toInt();
        double Forwardx = R3 + ui->lineEdit->text().toInt();
        if(Regle1_A == 0 || Regle2_A == 0){
            return;
        }
        double YL1; double YF1; double YL2; double YF2;
        {double x = lookedx; double a = Regle1_A; double b = Regle1_B; YL1 =(a*x) + b;}
        {double x = Forwardx; double a = Regle1_A; double b = Regle1_B; YF1 =(a*x) + b;}
        {double x = lookedx; double a = Regle2_A; double b = Regle2_B; YL2 =(a*x) + b;}
        {double x = Forwardx; double a = Regle2_A; double b = Regle2_B; YF2 =(a*x) + b;}

        Coords Regle1C{
            lookedx,YL1
        };
        Coords Regle2C{
             lookedx, YL2
        };
        Coords Regle1C2{
             Forwardx, YF1
        };
        Coords Regle2C2{
             Forwardx, YF2
        };

        cord1.push_back(Regle1C);
        cord1.push_back(Regle1C2);
        cord2.push_back(Regle2C);
        cord2.push_back(Regle2C2);

        std::reverse(cord1.begin(), cord1.end());
        std::reverse(cord2.begin(), cord2.end());
        GenerateChart(cord1,cord2, R3);
    }
}

void MainWindow::GenerateChart(std::vector<Coords> coord1, std::vector<Coords> coord2, double x_x){
    QChart *chart = new QChart();
       QValueAxis *axisX = new QValueAxis;
       axisX->setTickCount(ui->lineEdit->text().toInt());
       chart->addAxis(axisX, Qt::AlignBottom);
       QSplineSeries *series = new QSplineSeries;
       for(auto i: coord1)
            series->append(i.x,i.y);

       series->setColor(Qt::blue);
       series->setName(ui->Demarche1_Regle->text().mid(7));
       chart->addSeries(series);

       QValueAxis *axisY = new QValueAxis;
       axisY->setTickCount(ui->lineEdit_2->text().toInt());
       chart->addAxis(axisY, Qt::AlignLeft);
       series->attachAxis(axisX);
       series->attachAxis(axisY);

       QSplineSeries *series2 = new QSplineSeries;
       for(auto i: coord2)
            series2->append(i.x,i.y);

       series2->setName(ui->Demarche2_Regle->text().mid(7));
       series2->setColor(Qt::red);
       chart->addSeries(series2);
       axisX->setTitleText("Axe des X");
       axisY->setTitleText("Axe des Y");
       series2->attachAxis(axisY);
       series2->attachAxis(axisX);

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       //ui->gridChart->addWidget(chartView);
       window->setCentralWidget(chartView);
       window->setStyleSheet("background-color: transparent");
       window->resize(800,600);
       window->setWindowTitle("Graphique d'intersection // Precision X: " + ui->lineEdit->text() + " Precision Y: " + ui->lineEdit_2->text());
       window->show();
}

void MainWindow::GenerateRule (QString a, QString b, QLineEdit * lineEdit){

    if(doesHaveChar(a) || doesHaveChar(b)){
        lineEdit->setText("Calcul impossible");
        return;
        }
    if(a.toDouble() == 0.00000000000){
        lineEdit->setText("Calcul impossbile: a = 0 (x * 0 = 0)");
        return;
    }
    double _a = a.toDouble();
    double _b = b.toDouble();
    QString rule = "Regle: y = " + QString::number(_a) + "x + " + QString::number(_b);
    lineEdit->setText(rule);
}

enum Fonction {TROUVERX, TROUVERB, TROUVERY};
void Calcul(Fonction f, QString arg1, QString arg2, QString arg3, QLineEdit * lineEdit){
    if(doesHaveChar(arg1) || doesHaveChar(arg2) || doesHaveChar(arg3)){
        lineEdit->setText("Calcul impossible");
        return;
    }

    QString result;
    switch (f) {
    case TROUVERX:
    {
        double b = arg3.toDouble();
        double a = arg2.toDouble();
        if(a == 0.00000000000){
            lineEdit->setText("Calcul impossbile: a = 0 (x * 0 = 0)");
            return;
        }
        double y = arg1.toDouble();
        double res = 0;
        /*
         * 15 = 2*x + b
         * 15/2 - b = x
        */
        y /= a;
        y -= b;
        res = y;
        result = QString::number(res);
    }
        break;
    case TROUVERB:
    {
        double x = arg1.toDouble();
        double y = arg2.toDouble();
        double a = arg3.toDouble();
        if(a == 0.00000000000){
            lineEdit->setText("Calcul impossbile: a = 0 (x * 0 = 0)");
            return;
        }
        double res = 0;
        /*
         *15 = 2*5 + b
         *15 - (2*5) = b
         */
        y -= (x*a);
        res = y;
        result = QString::number(res);
    }
        break;
    case TROUVERY:
    {
        double x = arg1.toDouble();
        double a = arg2.toDouble();
        if(a == 0.00000000000){
            lineEdit->setText("Calcul impossbile: a = 0 (x * 0 = 0)");
            return;
        }
        double b = arg3.toDouble();
        double res = 0;
        /*
         *y = a*x + b
         */
        res =(a*x) + b;
        result = QString::number(res);
    }
        break;
    }
    lineEdit->setText(result);
    return;
}

void MainWindow::on_TrouverB_X_textChanged(const QString &arg1)
{
    Calcul(TROUVERB, ui->TrouverB_X->text(), ui->TrouverB_Y->text(), ui->TrouverB_A->text(), ui->TrouverB_Reponse);
}
void MainWindow::on_TrouverB_Y_textChanged(const QString &arg1)
{
    Calcul(TROUVERB, ui->TrouverB_X->text(), ui->TrouverB_Y->text(), ui->TrouverB_A->text(), ui->TrouverB_Reponse);
}
void MainWindow::on_TrouverB_A_textChanged(const QString &arg1)
{
    Calcul(TROUVERB, ui->TrouverB_X->text(), ui->TrouverB_Y->text(), ui->TrouverB_A->text(), ui->TrouverB_Reponse);
}
void MainWindow::on_TrouverX_Y_textChanged(const QString &arg1)
{
    Calcul(TROUVERX, ui->TrouverX_Y->text(), ui->TrouverX_A->text(), ui->TrouverX_B->text(), ui->TrouverX_Reponse);
}
void MainWindow::on_TrouverX_A_textChanged(const QString &arg1)
{
    Calcul(TROUVERX, ui->TrouverX_Y->text(), ui->TrouverX_A->text(), ui->TrouverX_B->text(), ui->TrouverX_Reponse);
}
void MainWindow::on_TrouverX_B_textChanged(const QString &arg1)
{
    Calcul(TROUVERX, ui->TrouverX_Y->text(), ui->TrouverX_A->text(), ui->TrouverX_B->text(), ui->TrouverX_Reponse);
}
void MainWindow::on_TrouverY_X_textChanged(const QString &arg1)
{
    Calcul(TROUVERY, ui->TrouverY_X->text(), ui->TrouverY_A->text(), ui->TrouverX_B->text(), ui->TrouverY_Reponse);
}
void MainWindow::on_TrouverY_A_textChanged(const QString &arg1)
{
    Calcul(TROUVERY, ui->TrouverY_X->text(), ui->TrouverY_A->text(), ui->TrouverX_B->text(), ui->TrouverY_Reponse);
}
void MainWindow::on_TrouverY_B_textChanged(const QString &arg1)
{
    Calcul(TROUVERY, ui->TrouverY_X->text(), ui->TrouverY_A->text(), ui->TrouverY_B->text(), ui->TrouverY_Reponse);
}


void MainWindow::on_Demarche1_A_textChanged(const QString &arg1)
{

    GenerateRule(ui->Demarche1_A->text(), ui->Demarche1_B->text(), ui->Demarche1_Regle);
}

void MainWindow::on_Demarche1_B_textChanged(const QString &arg1)
{
    GenerateRule(ui->Demarche1_A->text(), ui->Demarche1_B->text(), ui->Demarche1_Regle);
}

void MainWindow::on_Demarche2_A_textChanged(const QString &arg1)
{
    GenerateRule(ui->Demarche2_A->text(), ui->Demarche2_B->text(), ui->Demarche2_Regle);
}

void MainWindow::on_Demarche2_B_textChanged(const QString &arg1)
{
    GenerateRule(ui->Demarche2_A->text(), ui->Demarche2_B->text(), ui->Demarche2_Regle);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()){
        ui->label_20->setEnabled(true);
        ui->label_21->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit->setEnabled(true);
    }else{
        ui->label_20->setEnabled(false);
        ui->label_21->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit->setEnabled(false);
    }
}

void MainWindow::on_MainWindow_destroyed()
{
    window->close();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString nw = arg1;
    if((arg1.toInt() <= 1) || doesHaveChar(nw)){
        ui->lineEdit->setText("2");
    }
}


void MainWindow::on_pushButton_clicked()
{   
    ImageWindow1 * image = new ImageWindow1("Relations et fonctions/explication",":/new/prefix1/_pdp_sq_.jpg");
    image->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ImageWindow1 * image = new ImageWindow1("Relations et fonctions/mode de representation",":/new/prefix1/_pdp_sq_.jpg");
    image->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    ImageWindow1 * image = new ImageWindow1("Algebre/Inequation",":/new/prefix1/inequation.jpg");
    image->show();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString nw = arg1;
    if((arg1.toInt() <= 1) || doesHaveChar(nw)){
        ui->lineEdit_2->setText("2");
    }
}

void MainWindow::on_Demarche1_Regle_textChanged(const QString &arg1)
{

}
