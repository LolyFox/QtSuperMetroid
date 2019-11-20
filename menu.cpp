#include "menu.h"

Menu::Menu()
{
    setWindowTitle("Jeu Metrold - AFO TLA AIO");

    gameWidget = new QWidget;
    soundWidget = new QWidget;
    layoutMenu = new QVBoxLayout;
    layoutSon = new QHBoxLayout;

    startButton = new QPushButton("Jouer");
    exitButton = new QPushButton("Quitter");
    soundButton = new QPushButton("Son");
    scoreButton = new QPushButton("Score");
    creditsButton = new QPushButton("Crédits");

    launchLabel = new QLabel("Bienvenue sur le jeu 'Metrold' !");
    startLabel =  new QLabel;
    exitLabel = new QLabel;
    soundLabel = new QLabel("Test son");
    scoreLabel = new QLabel;
    creditsLabel = new QLabel;

    layoutMenu->addWidget(launchLabel);
    layoutMenu->addWidget(startButton);
    layoutMenu->addWidget(soundButton);
    layoutMenu->addWidget(creditsButton);
    layoutMenu->addWidget(exitButton);
     //layoutMenu->addWidget(
    layoutSon->addWidget(soundLabel);

    connect(startButton, &QPushButton::clicked, this, &Menu::startGame);
    connect(exitButton, &QPushButton::clicked, this, &Menu::close);
    connect(soundButton, &QPushButton::clicked, this, &Menu::soundGame);
    connect(scoreButton, &QPushButton::clicked, this, &Menu::scoreGame);
    connect(creditsButton, &QPushButton::clicked, this, &Menu::creditsGame);

    gameWidget->setLayout(layoutMenu);
    //soundWidget->setLayout(layoutSon);

    gameWidget->show();

    setCentralWidget(gameWidget);
}

Menu::~Menu(){}

void Menu::startGame()
{
    Game* partie = new Game(this);
    partie->setWindowTitle("let's play -- yahaha");
    partie->setFixedSize(848,640);
    partie->show();

    gameWidget->close();
}

void Menu::soundGame()
{

}

void Menu::scoreGame()
{

}

void Menu::creditsGame()
{

}
