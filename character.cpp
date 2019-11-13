#include "character.h"

void Character::SetHP(unsigned char p_HP){X=p_HP;}

void Character::SetPos(unsigned short p_X, unsigned short p_Y)
{
    if(p_X!=1024)
        X=p_X;
    if(p_Y!=1024)
        Y=p_Y;
}

unsigned char Character::GetHP(){return HP;}

unsigned short Character::GetX(){return X;}

unsigned short Character::GetY(){return Y;}
