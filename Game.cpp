#include <Game.h>

Game::Game(QWidget* p_parent)
{
    parent=p_parent;
    timer = new QTimer(this);
    this->connect(timer, SIGNAL(timeout()),this,SLOT(moveable()));
    timer->start(16); // 16.7 = 60Hz
    hud = new HUD();
    hero = new Player(this);
    Dojo = new room();
//    Room_Map = CreateRoom(":/Map/Dojo1.map");
}

Game::~Game()
{
    delete hud;
    delete hero;
    delete Dojo;
}

void Game::paintEvent(QPaintEvent *)
{
    QPixmap pixmap_HUD(":/img/HUD2.png");
    QPixmap pixmap_Player(":/img/MetroidPlayer.png");
    QPixmap pixmap_Tiles(":/img/BackgroundTiles.png");

    QPainter painter(this);

    painter.drawPixmap(0, 0, QPixmap(":/img/BG/Crateria/OldTourain.bmp").scaled(size()));

    Dojo->Draw(&painter,pixmap_Tiles);

    hud->Animated(&painter,pixmap_HUD,hero);

    hero->Animation(&painter,pixmap_Player);



    // bullet[]


    // ennemies[]
    // items_animated[]


    painter.end();
}

void Game::keyPressEvent(QKeyEvent * event)
{
    hero->Key_event(event);
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D && !event->isAutoRepeat())
    {
        hero->pressed.D=false;
        if (!hero->ota.canJump && !hero->ota.fall)
            hero->AnimationLevel=0;
    }
    else if(event->key() == Qt::Key_Q && !event->isAutoRepeat())
    {
        hero->pressed.Q =false;
        if (!hero->ota.canJump && !hero->ota.fall)
            hero->AnimationLevel=0;
    }
    else if(event->key() == Qt::Key_Z  && !event->isAutoRepeat())
    {
        hero->pressed.up =false;
        if (!hero->ota.canJump && !hero->ota.fall)
            hero->AnimationLevel=0;
    }
    else if(event->key() == Qt::Key_S && !event->isAutoRepeat())
    {
        hero->pressed.S =false;
        if (!hero->ota.canJump && !hero->ota.fall)
            hero->AnimationLevel=0;

    }
    else if(event->key() == Qt::Key_Down && !event->isAutoRepeat())
    {
        hero->pressed.down =false;
        if (!hero->ota.canJump && !hero->ota.fall)
            hero->AnimationLevel=0;

    }
    else if(event->key() == Qt::Key_Up && !event->isAutoRepeat())
    {
        hero->pressed.up =false;
    }
    else if(event->key() == Qt::Key_Left && !event->isAutoRepeat())
    {
        hero->pressed.left =false;
    }
    else if(event->key() == Qt::Key_Right && !event->isAutoRepeat())
    {
        hero->pressed.right =false;
    }
    else if(event->key() == Qt::Key_Shift && !event->isAutoRepeat() )
    {
        hero->pressed.jump =false;
    }
}

void Game::moveable()
{
    hero->Movement(Dojo->getFront());
    update();
}

void Game::ConnectTimer(QTimer* pTimer, const char * p_signal, const QObject * p_receiver,const char * p_method )
{
    this->connect(pTimer,p_signal,p_receiver,p_method);
}

//std::vector<Map_element> Game::CreateRoom(QString p_path)
//{
//
//}

/* -------------------------------------- */
//    /* P2 */
//    QRectF target(0.0, 0.0, 118.0, 18.0); // incrustation
//    QRectF source(25.0, 155.0, 118.0, 18.0); // extration rectangle

//    /* P2 */
//    QRectF target(0.0, 0.0, 118.0, 18.0); // incrustation
//    QRectF source(25.0, 135.0, 118.0, 18.0); // extration rectangle


//    /* P1 */
//    QRectF target(0.0, 0.0, 118.0, 18.0); // incrustation
//    QRectF source(25.0, 115.0, 118.0, 18.0); // extration rectangle


    /* P0 */
//    QRectF target(0.0, 0.0, 118.0, 18.0); // incrustation
//    QRectF source(25.0, 100.0, 118.0, 18.0); // extration rectangle
