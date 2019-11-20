/**
 * @file Game.h
 *
 * @brief All main functions and element use for the game
 *
 * @date 8 november 2019
 *
 * @author LolyFox
 *
 */

#pragma once

#include <QtGui>
#include <vector>
#include "player.h"
#include "room.h"
#include "hud.h"

/*!
 * \class Game
 * \brief The Game class contain the main elements calls to make the game work
 */
class Game : public QWidget
{
     Q_OBJECT
public:
    Game(QWidget* parent);
    ~Game();

private:
    // variables
    HUD* hud;
    Player* hero;
    room* Dojo;
    QWidget* parent;
    QTimer* timer;
    std::vector<Map_element> Room_Map;

    // functions
    void paintEvent(QPaintEvent *event);
    void ConnectTimer(QTimer* pTimer, const char * p_signal, const QObject * p_receiver,const char * p_method);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void moveable();
};
