#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <Game.h>

//#include "sound.h"

class Menu : public QMainWindow
{
    Q_OBJECT
public :
    Menu();
    ~Menu();

protected:
    QPushButton *startButton;
    QPushButton *exitButton;
    QPushButton *soundButton;
    QPushButton *scoreButton;
    QPushButton *creditsButton;

    QLabel *launchLabel;
    QLabel *startLabel;
    QLabel *exitLabel;
    QLabel *soundLabel;
    QLabel *scoreLabel;
    QLabel *creditsLabel;

    //TODO:Sound *gameSound;

private:
    QWidget *gameWidget;
    QWidget *soundWidget;
    QVBoxLayout *layoutMenu;
    QHBoxLayout *layoutSon;

public slots :

private slots:
    void startGame();
    void soundGame();
    void scoreGame();
    void creditsGame();

};

#endif // MENU_H
