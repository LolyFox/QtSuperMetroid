#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>


class Character: public QObject
{
    Q_OBJECT
public:
    QWidget* parent;

    Character(QWidget* p_parent,unsigned char p_HP=99, unsigned short p_X= 420, unsigned short p_Y=320)
        : parent(p_parent), HP(p_HP),X(p_X),Y(p_Y){}
    virtual ~Character(){}

    // functions
    unsigned char GetHP();
    unsigned short GetX();
    unsigned short GetY();
    void SetHP(unsigned char p_HP);
    void SetPos(unsigned short p_X=1024, unsigned short p_Y=1024); // (1024,1024) = default value to keep current coord

private:
    unsigned char HP;
    unsigned short X;
    unsigned short Y;

};

#endif // CHARACTER_H
