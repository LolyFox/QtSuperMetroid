#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include <QFile>
#include <QTextStream>
#include "Object.h"

struct tilesObject
{
    spriteFrame frame;
    unsigned short x, y;
};

struct Map_element
{
    int origin, destination = -1;
    std::vector<int> tile;
};

enum ground
{
    Gnd_L,
    Gnd_R,
    Gnd_M1,
    Gnd_M2
};

static spriteFrame frameGnd[4]={
    {188,763,16,16},    // left max side
    {205,763,16,16},    // right max side
    {171,763,16,16},    // middle 1
    {222,763,16,16}     // middle 2
};

static spriteFrame frameWall[7]={
    {171,797,16,16}, // down tube
    {171,746,16,16}, // up tube
    {188,746,16,16}, // left tube
    {205,746,16,16}, // right tube
    {205,712,16,16}, // connect tube up
    {222,712,16,16}, // border 1
    {171,712,16,16}  // border 2
};

class room: public QObject
{
    Q_OBJECT
public:
    room();
    ~room(){}

    // variable
    QWidget* parent;

    //functions
    void Draw(QPainter * p_painter,QPixmap p_pixmap);
    tilesObject CreateTile(unsigned short p_x,unsigned short p_y, spriteFrame p_frame){
        tilesObject t_tile = {p_frame,p_x,p_y};
        return t_tile;
    }

    std::vector<tilesObject> getFront();
    std::vector<tilesObject> getBack();

private:
    std::vector<tilesObject> Front;
    std::vector<tilesObject> Back;
    spriteFrame loadFrame(int p_type);
    unsigned short load_x(int p_position);
    unsigned short load_y(int p_position);

};

#endif // ROOM_H
