#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>
#include <vector>
#include <QPushButton>
#include <QLabel>
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

    Exercise(std::vector<Question> qrc, QLineEdit * Exer_Input, QTextEdit * Exer_RichText,
    QLabel * Exer_QuestionNum, QLabel * Exer_Recherche){
        _exercice.questions = qrc;
        _exercice.Length = qrc.size();
        _exercice.Level = 0;
        _exercice.BtnState = NEW;
        this->Exer_Input = Exer_Input;
        this->Exer_RichText = Exer_RichText;
        this->Exer_QuestionNum = Exer_QuestionNum;
        this->Exer_Recherche = Exer_Recherche;
    }

    int getState(){
        return _exercice.BtnState;
    }

    void NextQuestion(){
        _exercice.Level++;
        _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);

    }

    static void Reset(Exercise* exer){
        delete exer;
    }

private:
    enum btnState {NEW,NEXT,END};
    struct Exer{
        std::vector<Question> questions;
        QString WhereAt;
        int Level;
        int Length;
        btnState BtnState;
    };
    QLineEdit * Exer_Input;
    QTextEdit * Exer_RichText;
    QLabel * Exer_QuestionNum;
    QLabel * Exer_Recherche;
    Exer _exercice = {};

};
#endif // EXERCISE_H
