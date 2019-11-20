#include <Game.h>

Game::Game(QWidget* p_parent)
{
    parent=p_parent;

    timer = new QTimer(this);
    this->connect(timer, SIGNAL(timeout()),this,SLOT(moveable()));
    // 60 Hz = 16.666666666667 ms
    timer->start(16);

    hud = new HUD();
    hero = new Player(this);
    Dojo = new room();

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

    // TODO :
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
    hero->Key_release_event(event);
}

/*!
 * \fn Game::moveable
 * \brief Game::moveable is space for update information for display
 */
void Game::moveable()
{
    hero->Movement(Dojo->getFront());
    update();
}

void Game::ConnectTimer(QTimer* pTimer, const char * p_signal, const QObject * p_receiver,const char * p_method )
{
    this->connect(pTimer,p_signal,p_receiver,p_method);
}
