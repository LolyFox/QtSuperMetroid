#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtGui>
#include <vector>
#include "hud.h"
#include "room.h"
#include "player.h"

class Game : public QWidget
{
     Q_OBJECT
public:
    Game(QWidget* parent);
    ~Game();
    HUD* hud;
    Player* hero;
    room* Dojo;
    QWidget* parent;
    QTimer* timer;
    std::vector<Map_element> Room_Map;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void ConnectTimer(QTimer* pTimer, const char * p_signal, const QObject * p_receiver,const char * p_method);

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void moveable();
};

#endif // MYWIDGET_H
