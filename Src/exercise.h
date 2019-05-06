#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QLineEdit>
#include <QTextEdit>
#include <QTime>
#include <QCoreApplication>
#define BEGINOFEXER ("Commencer la série d'exercises!")
#define ENDOFEXER ("Fin de la série")
#define NEXTOFEXER ("Prochaine question")
#define CHECKOFEXER ("Valider")
#define ZEROEXER ("Recommencer")

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

struct Question{
    QString htmlText;
    QString Answer;
    QString AnswerLabel;
    QString Answer_SbS;
};
class Exercise{

public:


    Exercise(QVector<Question> qrc2, QLineEdit * Exer_Input, QTextEdit * Exer_RichText,
    QLabel * Exer_QuestionNum, QLabel * Exer_Recherche, QPushButton * Exer_NextBtn, QPushButton * Exer_Reset){
        QVector<Question> qrc = qrc2;
        _exercice.questions = qrc;
        _exercice.Length = qrc.length();
        _exercice.Level = 0;
        this->Exer_Input = Exer_Input;
        this->Exer_RichText = Exer_RichText;
        this->Exer_QuestionNum = Exer_QuestionNum;
        this->Exer_Recherche = Exer_Recherche;
        this->Exer_NextBtn = Exer_NextBtn;
        this->Exer_Reset = Exer_Reset;
    }

    void LoadContent(int flag = NEXT){
        switch (flag) {
        case REFRESH:
            {
            Exer_Input->setEnabled(true);
            Exer_QuestionNum->setEnabled(true);
            Exer_Recherche->setEnabled(true);
            Exer_Reset->setEnabled(true);
                Exer_NextBtn->setText(BEGINOFEXER);
            }
            break;
        case CORRECT:
            {
                Exer_RichText->setText(Exer_RichText->toHtml() + "\nBonne réponse!\n ");
                if(_exercice.Level >= (_exercice.Length-1) ){
                    Exer_NextBtn->setText(ENDOFEXER);
                }else
                Exer_NextBtn->setText(NEXTOFEXER);
            }
            break;
        case FALSE:
            {

                Exer_RichText->setText(Exer_RichText->toHtml() + "\nMauvaise réponse!\n " + _exercice.questions[_exercice.Level].Answer_SbS);
                if(_exercice.Level >= (_exercice.Length-1)){
                    Exer_NextBtn->setText(ENDOFEXER);
                }else
                Exer_NextBtn->setText(NEXTOFEXER);
            }
            break;
        case NEXT:
            {
            Exer_Input->setEnabled(true);
            Exer_QuestionNum->setEnabled(true);
            Exer_Recherche->setEnabled(true);
            Exer_Reset->setEnabled(true);

            Question newQuestion = _exercice.questions[_exercice.Level];
            Exer_RichText->setHtml(newQuestion.htmlText);
            Exer_Recherche->setText(newQuestion.AnswerLabel);
            Exer_QuestionNum->setText(_exercice.WhereAt);
            Exer_NextBtn->setText(CHECKOFEXER);
            }
            break;
        case END:
            {
            Exer_Input->setVisible(false);
            Exer_QuestionNum->setVisible(false);
            Exer_Recherche->setVisible(false);
            Exer_Reset->setVisible(false);
            Exer_RichText->setHtml("newQuestion.htmlText""");
            Exer_NextBtn->setText(ZEROEXER);
            }
            break;
        }

    }
    void CheckAnswer(){
        Exer_Input->setEnabled(false);
        Exer_QuestionNum->setEnabled(false);
        Exer_Recherche->setEnabled(false);
        Exer_Reset->setEnabled(false);
        if(Exer_Input->text() != _exercice.questions[_exercice.Level].Answer){
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
            delay(1);
            CheckAnswer();
            return;
        }
        if(Exer_NextBtn->text() == ZEROEXER){
            delay(1);
            Reset();
            return;
        }
        if(Exer_NextBtn->text() == ENDOFEXER){
            delay(1);
            LoadContent(END);
            return;
        }
        if(Exer_NextBtn->text() == NEXTOFEXER){
            delay(1);
                _exercice.Level = _exercice.Level + 1;
                if(_exercice.Level == _exercice.Length){
                    Exer_NextBtn->setText(ENDOFEXER);
                    return;
                }
                _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
                LoadContent();
            return;
        }
        if(Exer_NextBtn->text() == BEGINOFEXER){
            delay(1);
            Exer_Input->setEnabled(true);
            Exer_QuestionNum->setEnabled(true);
            Exer_Recherche->setEnabled(true);
            Exer_Reset->setEnabled(true);
            _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
            LoadContent();
            return;
        }
    }

    void Reset(){
        _exercice.Level = 0;
        _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
        Exer_Input->setVisible(false);
        Exer_QuestionNum->setVisible(false);
        Exer_Recherche->setVisible(false);
        Exer_Reset->setVisible(false);
        Exercise(_exercice.questions,Exer_Input,Exer_RichText,Exer_QuestionNum,Exer_Recherche, Exer_NextBtn, Exer_Reset);
        LoadContent(REFRESH);
    }

private:
    enum btnState {NEW, CORRECT, FALSE, NEXT,END, REFRESH};
    struct Exer{
        QVector<Question> questions;
        QString WhereAt;
        int Level;
        int Length;
        btnState BtnState;
    };
    QPushButton * Exer_NextBtn;
    QPushButton * Exer_Reset;
    QLineEdit * Exer_Input;
    QTextEdit * Exer_RichText;
    QLabel * Exer_QuestionNum;
    QLabel * Exer_Recherche;
    Exer _exercice = {};

};
#endif // EXERCISE_H
