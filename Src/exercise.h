#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QLineEdit>
#include <QTextEdit>

class Exercise{

public:
    struct Question{
        QString htmlText;
        QString Answer;
        QString AnswerLabel;
        QString Answer_SbS;
    };

    Exercise(QVector<Question> qrc, QLineEdit * Exer_Input, QTextEdit * Exer_RichText,
    QLabel * Exer_QuestionNum, QLabel * Exer_Recherche, QPushButton * Exer_NextBtn){
        _exercice.questions = qrc;
        _exercice.Length = qrc.size();
        _exercice.Level = 0;
        this->Exer_Input = Exer_Input;
        this->Exer_RichText = Exer_RichText;
        this->Exer_QuestionNum = Exer_QuestionNum;
        this->Exer_Recherche = Exer_Recherche;
        this->Exer_NextBtn = Exer_NextBtn;
    }

    void LoadContent(int flag = NEXT){
        switch (flag) {
        case NEW:
            {

            }
            break;
        case REFRESH:
            {
                Exer_NextBtn->setText("Commencer la série d'exercises!");
            }
            break;
        case CORRECT:
            {

            if(_exercice.Level == _exercice.questions.length()){
                LoadContent(END);
            }else
                Exer_RichText->setText(Exer_RichText->toHtml() + "\nBonne réponse!\n ");
                Exer_NextBtn->setText("Prochaine question");
            }
            break;
        case FALSE:
            {
            if(_exercice.Level == _exercice.questions.length()){
                LoadContent(END);
            }else
                Exer_RichText->setText(Exer_RichText->toHtml() + "\nMauvaise réponse!\n " + _exercice.questions[_exercice.Level].Answer_SbS);
                Exer_NextBtn->setText("Prochaine question");
            }
            break;
        case NEXT:
            {
            Question newQuestion = _exercice.questions[_exercice.Level];
            Exer_RichText->setHtml(newQuestion.htmlText);
            Exer_Recherche->setText(newQuestion.AnswerLabel);
            Exer_QuestionNum->setText(_exercice.WhereAt);
            Exer_NextBtn->setText("Valider");
            }
            break;
        case END:
            {

            }
            break;
        }

    }
    void CheckAnswer(){
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
        if(Exer_NextBtn->text() == "Valider"){
            CheckAnswer();
            return;
        }
        if(_exercice.Level == _exercice.questions.length()){
            LoadContent(END);
            return;
        }
        if(Exer_NextBtn->text() == "Prochaine question"){
            _exercice.Level++;
            _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
            LoadContent();
        }
        if(Exer_NextBtn->text() == "Commencer la série d'exercises!"){
            _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
            LoadContent();
        }
    }

    static void Reset(Exercise* exer){
        delete exer;
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
    QLineEdit * Exer_Input;
    QTextEdit * Exer_RichText;
    QLabel * Exer_QuestionNum;
    QLabel * Exer_Recherche;
    Exer _exercice = {};

};
#endif // EXERCISE_H
