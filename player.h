/**
 * @file player.h
 *
 * @brief All player sprites and deplacement in functions of keyevent and environment
 *
 * @date 26 october 2019
 *
 * @author LolyFox
 *
 */

#pragma once

#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <character.h>
#include "Object.h"
#include "room.h"

#define CUR_POS 1024

/*!
 * \struct listKeys
 * \brief The listKeys struct define bool for each key pressed
 */
struct listKeys
{
    // jump = shift
    bool D=false,Q=false, S=false, jump=false,
    right=false,left=false,up=false,down=false;
};

/*!
 * \struct airMov
 * \brief The airMov struct represente state for each available action on the air
 */
struct airMov{
    bool maxJump=false, fall = false, canJump=false;
};

/*!
 * \enum dirOrder
 * \brief The dirOrder enum position for each position in tables canon direction
 */
enum dirOrder
{
    Local_Dir,
    Up_Dir,
    Down_Dir,
    Up,
    Down,
    Other
};

static spriteFrame frame_R[8]=
{
    {250,362,23,40},    // right
    {396,357,32,49},    // right up
    {346,361,31,42},    // right down
    {402,303,20,54},    // up
    {0,0,0,0},          // down
    {249,310,26,43},
    {299,310,26,43},
    {349,310,26,43}
};

static spriteFrame frame_L[8]=
{
    {200,362,23,40},    // left
    {46,358,32,48},     // left up
    {96,361,31,42},     // left down
    {52,303,20,54},      // up
    {0,0,0,0},          // down
    {199,310,26,43},
    {149,310,26,43},
    {99,310,26,43}
};

static spriteFrame frame_D[10]=
{
    {253,1014,18,42},
    {300,1014,23,42},
    {247,1063,29,43},
    {344,1013,35,43},
    {396,1014,32,42},
    {352,1064,19,42},
    {301,1064,22,43},
    {397,1063,29,43},
    {244,1113,35,43},
    {296,1114,32,42}
};

static spriteFrame frame_Q[10]=
{
    {203,1014,18,42},
    {150,1014,23,42},
    {97,1013,29,43},
    {44,1013,35,43},
    {196,1064,32,43},
    {152,1064,19,42},
    {101,1064,22,42},
    {47,1063,29,43},
    {194,1113,35,44},
    {146,1114,32,42}
};

static spriteFrame frame_DR[10]=
{
    {242,1313,39,43},
    {293,1313,37,43},
    {347,1313,30,43},
    {396,1313,32,44},
    {244,1363,36,43},
    {292,1363,39,43},
    {343,1363,38,43},
    {397,1363,29,43},
    {245,1413,33,43},
    {294,1413,36,43}
};

static spriteFrame frame_QL[10]=
{
    {193,1314,38,42},
    {143,1313,37,43},
    {97,1313,30,43},
    {46,1313,32,44},
    {194,1363,36,44},
    {142,1364,39,42},
    {93,1363,38,43},
    {47,1363,29,43},
    {195,1413,33,43},
    {144,1413,36,44}
};

static spriteFrame frame_DU[10]=
{
    {244,1161,35,48},
    {298,1161,28,48},
    {347,1161,30,48},
    {395,1161,34,48},
    {243,1211,37,48},
    {294,1211,36,48},
    {348,1211,27,48},
    {396,1211,31,48},
    {245,1261,34,48},
    {294,1261,37,48}
};

static spriteFrame frame_QU[10]=
{
    {194,1161,36,48},
    {148,1161,28,48},
    {97,1161,30,48},
    {45,1161,34,48},
    {193,1211,37,48},
    {144,1211,36,48},
    {98,1211,27,48},
    {46,1211,31,48},
    {195,1261,34,48},
    {144,1261,35,48}
};

static spriteFrame frame_DD[10]=
{
    {245,1463,33,43},
    {294,1463,35,43},
    {345,1463,34,43},
    {398,1463,27,43},
    {247,1513,29,43},
    {295,1513,33,43},
    {344,1513,36,43},
    {394,1513,35,42},
    {249,1563,26,43},
    {297,1563,30,43}
};

static spriteFrame frame_QD[10]=
{
    {195,1463,34,43},
    {148,1463,27,43},
    {97,1463,29,43},
    {45,1463,33,43},
    {194,1513,36,43},
    {149,1513,26,43},
    {97,1513,30,43},
    {45,1513,33,43},
    {194,1563,35,43},
    {145,1563,34,43}
};

// Seat Right directed frames
// 0 to 2 = breath
static spriteFrame frame_S_L[5]=
{
    {201,771,21,32},
    {151,771,21,32},
    {101,771,21,32},
    {50,767,21,43},//up
    {47,817,29,40}//up right
};

// Seat Left directed frames
static spriteFrame frame_S_R[5]=
{
    {251,771,21,32},
    {301,771,21,32},
    {351,771,21,32},
    {403,767,21,43},//up
    {397,817,29,40}//up left
};

// On The air (OTA) action
static spriteFrame frameOTA_L[9]=
{
    {201,819,22,36},    //left
    {148,917,28,39},    //left up
    {149,969,26,36},    //left down
    {101,865,22,44},    //up
    {52,869,21,35},     //down
    {199,914,26,46},    //up left fall
    {200,967,25,40}     //up left fall
};

static spriteFrame frameOTA_R[9]=
{
    {251,819,22,36},    //right
    {298,917,28,39},    //right up
    {298,969,26,36},    //right down
    {351,865,22,44},    //up
    {401,869,21,35},    //down
    {248,914,26,46},    //up right fall
    {249,967,25,40}     //up right fall
};

// Jumping frame
static spriteFrame frame_JR[12]=
{
    {252,154,19,40},
    {303,152,18,43},
    {350,151,23,45},
    {402,155,19,37},
    {253,204,18,40},
    {302,205,19,38},
    {352,206,20,36},
    {401,201,22,45},
    {251,254,21,40},
    {302,251,19,45},
    {352,251,19,46},
    {404,250,15,48}
};

static spriteFrame frame_JL[12]=
{
    {202,154,19,40},
    {153,152,18,43},
    {100,151,23,45},
    {52,155,19,37},
    {203,204,18,40},
    {152,205,19,37},
    {103,204,18,40},
    {51,201,22,45},
    {203,254,18,40},
    {153,251,18,45},
    {103,251,18,45},
    {54,250,16,48}
};

class Player : public Character
{
    Q_OBJECT
public:
    Player(QWidget* p_parent,unsigned char p_HP=55, unsigned short p_X= 420, unsigned short p_Y=400, unsigned char p_Mun = 0)
        :Character(p_parent,p_HP,p_X,p_Y), Mun(p_Mun)
    {
        timerJump = new QTimer(this);
        this->connect(timerJump, SIGNAL(timeout()),this,SLOT(loading_jump()));
    }
    ~Player(){}

    // functions
    unsigned char GetMun();
    void Movement(std::vector<tilesObject> p_room);
    void Animation(QPainter* p_painter,QPixmap p_pixmap);
    void Key_event(QKeyEvent * p_event);
    void Key_release_event(QKeyEvent * p_event);

private:
    QTimer * timerJump;

    // Parameters
    listKeys pressed;
    airMov ota;

    // variables
    bool oldirection = false; // false = right
    unsigned char Mun;
    double AnimationLevel=0;
    double InitPosY=0;
    double TimeJump=0;
    double top_jump = 0; // 10
    // 17^2 = 289 px
    double load_count=0;
    double jump_count=0;
    double speed=4;
    char colision=0;

    // function
    void Print(QPainter * p_painter,QPixmap p_pixmap, spriteFrame* p_Pix_coord,int p_Temp=0);

public slots :
    void loading_jump();
};
