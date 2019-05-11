#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <ctime>
#include <QVector>
#include <QLineEdit>
#include <algorithm>
#include <random>
#include <QTextEdit>
#include <QTime>
#include <QTabWidget>
#include <QTabBar>
#include <QCoreApplication>
#define BEGINOFEXER ("Commencer la série d'exercises")
#define ENDOFEXER ("Fin de la série")
#define NEXTOFEXER ("Prochaine question")
#define CHECKOFEXER ("Valider")
#define ZEROEXER ("Recommencer")


struct Question{
    QString htmlText;
    QString Answer;
    QString AnswerLabel;
    QString Answer_Explication;
};

class Exercise{

public:

    Exercise(std::vector<Question> qrc2, QLineEdit * Exer_Input, QTextEdit * Exer_RichText,
    QLabel * Exer_QuestionNum, QLabel * Exer_Recherche, QPushButton * Exer_NextBtn, QPushButton * Exer_Reset, QTabWidget * tab){
        std::vector<Question> qrc = qrc2;
        srand((unsigned)time(0));
        int shuffleMax = (rand()%1000)+1;
        auto rng = std::default_random_engine {};
        rng.seed(shuffleMax);
        for (int i = 0; i < shuffleMax; i++) {
            std::shuffle(std::begin(qrc),std::end(qrc),rng);
        }
        _exercice.Score = 0;
        _exercice.questions = qrc;
        _exercice.Length = qrc.size();
        _exercice.Level = 0;
        this->tab = tab;
        this->Exer_Input = Exer_Input;
        this->Exer_RichText = Exer_RichText;
        this->Exer_QuestionNum = Exer_QuestionNum;
        this->Exer_Recherche = Exer_Recherche;
        this->Exer_NextBtn = Exer_NextBtn;
        this->Exer_Reset = Exer_Reset;
    }
    void ChangeInputState(bool state){
        Exer_Input->setEnabled(state);
        Exer_QuestionNum->setEnabled(state);
        Exer_Recherche->setEnabled(state);
        Exer_Reset->setEnabled(state);
    }
    void LoadContent(int flag = NEXT){
        switch (flag) {
        case REFRESH:
            {
            tab->setTabEnabled(0, true);
            tab->setTabEnabled(2, true);
            ChangeInputState(false);
            Exer_NextBtn->setText(BEGINOFEXER);
            }
            break;
        case CORRECT:
            {
                _exercice.Score++;
                ChangeInputState(true);
                Exer_RichText->setText(Exer_RichText->toHtml() + "\nBonne réponse!\n ");
                if(_exercice.Level >= (_exercice.Length-1) ){
                    Exer_NextBtn->setText(ENDOFEXER);
                }else{
                ChangeInputState(false);
                Exer_NextBtn->setText(NEXTOFEXER);
                }
            }
            break;
        case FALSE:
            {
                ChangeInputState(true);
                Exer_RichText->setText(Exer_RichText->toHtml() + "<dl style=\"text-align:center\"><br>Mauvaise réponse!<br> " + _exercice.questions[_exercice.Level].Answer_Explication);
                if(_exercice.Level >= (_exercice.Length-1)){
                    Exer_NextBtn->setText(ENDOFEXER);
                }else{
                ChangeInputState(false);
                Exer_NextBtn->setText(NEXTOFEXER);
                }
            }
            break;
        case NEXT:
            {
            ChangeInputState(true);
            Question newQuestion = _exercice.questions[_exercice.Level];
            Exer_Input->setText("");
            Exer_RichText->setHtml(newQuestion.htmlText);
            Exer_Recherche->setText(newQuestion.AnswerLabel);
            Exer_QuestionNum->setText(_exercice.WhereAt);
            Exer_NextBtn->setText(CHECKOFEXER);
            }
            break;
        case END:
            {
            ChangeInputState(false);
            tab->setTabEnabled(0, true);
            tab->setTabEnabled(2, true);
            Exer_RichText->setHtml("Fin des exercises!");
            Exer_NextBtn->setText(ZEROEXER);
            }
            break;
        }

    }
    void CheckAnswer(){
        QString str = Exer_Input->text();
        for (int i = 0; i < str.length(); i++) {
            QChar c = str[i];
            if(c == ','){
                str[i] = '.';
            }
        }
        if(str != _exercice.questions[_exercice.Level].Answer){
            LoadContent(FALSE);
        }else{
            LoadContent(CORRECT);
        }
    }

    int getState(){
        return _exercice.BtnState;
    }
    void FirstQuestion(){
        LoadContent(REFRESH);
    }
    void NextQuestion(){
        if(Exer_NextBtn->text() == CHECKOFEXER){
            delay2(20);
            CheckAnswer();
            return;
        }
        if(Exer_NextBtn->text() == ZEROEXER){
            delay2(20);
            Reset();
            return;
        }
        if(Exer_NextBtn->text() == ENDOFEXER){
            delay2(20);
            LoadContent(END);
            return;
        }
        if(Exer_NextBtn->text() == NEXTOFEXER){
            delay2(20);
                _exercice.Level = _exercice.Level + 1;
                if(_exercice.Level == _exercice.Length){
                    Exer_NextBtn->setText(ENDOFEXER);
                    return;
                }
                _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
                ChangeInputState(true);
                LoadContent();
            return;
        }
        if(Exer_NextBtn->text() == BEGINOFEXER){
            delay2(20);
            tab->setTabEnabled(0, false);
            tab->setTabEnabled(2, false);
            ChangeInputState(true);
            _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
            LoadContent();
            return;
        }
    }

    void Reset(){
        int shuffleMax = (rand()%1000)+1;
        auto rng = std::default_random_engine {};
        rng.seed(shuffleMax);
        for (int i = 0; i < shuffleMax; i++) {
            std::shuffle(std::begin(_exercice.questions),std::end(_exercice.questions),rng);
        }
        Exer_Input->setText("");
        _exercice.Level = 0;
        _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
        ChangeInputState(false);
        Exercise(_exercice.questions,Exer_Input,Exer_RichText,Exer_QuestionNum,Exer_Recherche, Exer_NextBtn, Exer_Reset, tab);
        LoadContent(REFRESH);
    }

private:
    void delay2( int millisecondsToWait )
    {
        QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
    enum btnState {NEW, CORRECT, FALSE, NEXT,END, REFRESH};
    struct Exer{
        std::vector<Question> questions;
        QString WhereAt;
        int Level;
        int Score;
        int Length;
        btnState BtnState;
    };
    QTabWidget * tab;
    QPushButton * Exer_NextBtn;
    QPushButton * Exer_Reset;
    QLineEdit * Exer_Input;
    QTextEdit * Exer_RichText;
    QLabel * Exer_QuestionNum;
    QLabel * Exer_Recherche;
    Exer _exercice = {};

};
#endif // EXERCISE_H
