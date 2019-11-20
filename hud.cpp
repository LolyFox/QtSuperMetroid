#include "hud.h"

QRectF HUD::create_RectF(spriteFrame *p_srites, int p_type)
{
    QRectF name(p_srites[p_type].shift,p_srites[p_type].level,p_srites[p_type].width,p_srites[p_type].height);
    return name;
}

void HUD::Animated(QPainter *p_painter, QPixmap p_pixmap, Player* p_hero)
{
    /* Bar Display */
    p_painter->drawPixmap(t_Bar, p_pixmap, s_BB)  ;
    p_painter->drawPixmap(t_EnB, p_pixmap, s_Enn_Bar)  ;

    /* Left HP Display */
    p_painter->drawPixmap(t_HPL, p_pixmap, v_Blue_HP.at(p_hero->GetHP()/10))  ;
    p_painter->drawPixmap(t_HPR, p_pixmap, v_Blue_HP.at(p_hero->GetHP()%10))  ;

    switch (p_hero->GetHP()) {
        case 0 :
            // TODO: Death Bar + return "game over"
            break;
        default :
            Temp = static_cast<unsigned char>((p_hero->GetHP()*(HUD_POSITIONS[HP_Bar].width))/99);
            p_painter->drawPixmap(HUD_POSITIONS[HP_Bar].shift,HUD_POSITIONS[HP_Bar].level,Temp-1,HUD_POSITIONS[HP_Bar].height,p_pixmap,HUD_ELEMENTS[W_life_pixels].shift,HUD_ELEMENTS[W_life_pixels].level,HUD_ELEMENTS[W_life_pixels].width,HUD_ELEMENTS[W_life_pixels].height); //white
            if(p_hero->GetHP()!=99)
                p_painter->drawPixmap(HUD_POSITIONS[HP_Bar].shift+Temp-1,HUD_POSITIONS[HP_Bar].level,1,HUD_POSITIONS[HP_Bar].height,p_pixmap,HUD_ELEMENTS[Max_life_pixels].shift,HUD_ELEMENTS[Max_life_pixels].level,HUD_ELEMENTS[Max_life_pixels].width,HUD_ELEMENTS[Max_life_pixels].height); //max
            if(p_hero->GetHP()!=98 && p_hero->GetHP()!=99 )
                p_painter->drawPixmap(HUD_POSITIONS[HP_Bar].shift+Temp,HUD_POSITIONS[HP_Bar].level,HUD_POSITIONS[HP_Bar].width-Temp-2,HUD_POSITIONS[HP_Bar].height,p_pixmap,HUD_ELEMENTS[B_life_pixels].shift,HUD_ELEMENTS[B_life_pixels].level,HUD_ELEMENTS[B_life_pixels].width,HUD_ELEMENTS[B_life_pixels].height); //black
            break;
    }

    /* Mun Display */
    p_painter->drawPixmap(t_MunL, p_pixmap, v_Blue_Mun.at(p_hero->GetMun()/10));
    p_painter->drawPixmap(t_MunR, p_pixmap, v_Blue_Mun.at(p_hero->GetMun() % 10));
    p_painter->drawPixmap(t_MunMaxL, p_pixmap, v_Blue_Mun.at(9));
    p_painter->drawPixmap(t_MunMaxR, p_pixmap, v_Blue_Mun.at(9));
}

HUD::HUD()
{
    /* target generations */
    t_Bar = create_RectF(HUD_POSITIONS, Bar_Pos);
    t_HPL = create_RectF(HUD_POSITIONS, HPL);
    t_HPR = create_RectF(HUD_POSITIONS, HPR);
    t_EnB = create_RectF(HUD_POSITIONS, EnB_Pos);
    t_MunL = create_RectF(HUD_POSITIONS, MunL);
    t_MunR = create_RectF(HUD_POSITIONS, MunR);
    t_MunMaxL = create_RectF(HUD_POSITIONS, MunMaxL);
    t_MunMaxR = create_RectF(HUD_POSITIONS, MunMaxR);

    /* source generation */
    s_BB = create_RectF(HUD_ELEMENTS, Blue_Bar);
    s_Enn_Bar = create_RectF(HUD_ELEMENTS, Enn_Bar);

    /* Numbers */
    for (char i=0; i<10; i++)
    {
        v_Blue_HP.push_back(create_RectF(HUD_ELEMENTS, Blue_HP_Base+i));
        v_Blue_Mun.push_back(create_RectF(HUD_ELEMENTS, Blue_Mun_Base+i));
    }
}

HUD::~HUD()
{

}
