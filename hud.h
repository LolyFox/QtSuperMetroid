#ifndef HUD_H
#define HUD_H

#include <QRectF>
#include <vector>
#include <QPainter>
#include "Object.h"
#include "player.h"

enum HUD_SRC
{
    Blue_Bar,
    Red_Bar,
    Enn_Bar,
    Max_life_pixels,
    W_life_pixels,
    B_life_pixels,
    Blue_HP_Base,
    Blue_Mun_Base=16,
    Red_HP_Base=26,
    Red_Mun_Base=36
};

enum HUD_POSITION
{
    Bar_Pos,
    EnB_Pos,
    HPL,
    HPR,
    HP_Bar,
    MunL,
    MunR,
    MunMaxL,
    MunMaxR
};

static spriteFrame HUD_ELEMENTS[]=
{
    {25, 20, 193, 34}, // Blue Bar
    {25, 63, 193, 34}, // RED Bar
    {252, 24, 137, 34}, // ENNNEMIE Bar
    {62, 33, 1, 2}, // max
    {63, 33, 1, 2}, // w
    {114, 33, 1, 2}, // b
    /* Blue HP numbers */
    {253, 101, 10, 9}, {267, 101, 10, 9}, {281, 101, 10, 9}, {295, 101, 10, 9}, {309, 101, 10, 9},
    {253,114, 10, 9}, {267,114, 10, 9}, {281,114, 10, 9}, {295,114, 10, 9}, {309,114, 10, 9},
    /* Blue Mun numbers */
    {253, 129, 8, 7}, {266,129, 8, 7}, {279,129, 8, 7}, {292,129, 8, 7}, {305,129, 8, 7},
    {253, 140, 8, 7}, {266,140, 8, 7}, {279,140, 8, 7}, {292,140, 8, 7}, {305,140, 8, 7},
    /* Red HP numbers */
    {325, 101, 10, 9}, {339, 101, 10, 9}, {353, 101, 10, 9}, {367, 101, 10, 9}, {381, 101, 10, 9},
    {325,114, 10, 9}, {339,114, 10, 9}, {353,114, 10, 9}, {367,114, 10, 9}, {381,114, 10, 9},
    /* Red Mun numbers */
    {325, 129, 8, 7}, {338,129, 8, 7}, {351,129, 8, 7}, {364,129, 8, 7}, {377,129, 8, 7},
    {325, 140, 8, 7}, {338,140, 8, 7}, {351,140, 8, 7}, {364,140, 8, 7}, {377,140, 8, 7}
};

static spriteFrame HUD_POSITIONS[]=
{
    {0, 0, 193, 34},
    {704, 0, 137, 34},
    {11, 12, 10, 9},
    {21, 12, 10, 9},
    {38,13,80,2},
    {144, 11, 8, 7},
    {152, 11, 8, 7},
    {163, 11, 8, 7},
    {171, 11, 8, 7}
};


class HUD
{

public:
    QRectF t_Bar,t_HPL,t_HPR,t_EnB,t_MunL,t_MunR,t_MunMaxL,
    t_MunMaxR,s_BB,s_RB,s_Enn_Bar,s_Max_life_pixels,
    s_W_life_pixels, s_B_life_pixels,t_Player;
    std::vector<QRectF> v_Blue_HP;
    std::vector<QRectF> v_Blue_Mun;
    unsigned char Temp=0;
    void Animated(QPainter* p_painter, QPixmap p_pixmap, Player* p_hero);
    HUD();
    ~HUD();
};

#endif // HUD_H
