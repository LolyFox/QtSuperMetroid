#include "room.h"
#include <iterator>

room::room()
{
    QString Map(":/Map/Dojo1.map");
    QFile file(Map);

    char id = 0;
    int x;

    if(!file.open(QIODevice::ReadOnly)) {
        qCritical("ERROR : error loading map %d", id);
    }

    QTextStream in(&file);
    QString line;
    QStringList fields;

    Map_element temp;
    std::vector<Map_element> Room_Map;


    // try to fill "Room_Map" with the map file
    try {
        while(!in.atEnd()){
            line = in.readLine();
            fields = line.split(" ", QString::SkipEmptyParts);
            temp.tile.clear();
            temp.origin = -1;
            temp.destination = -1;

            if(fields.size() != 0){ // ignore empty line
                // ignore comment : begin by "// "
                if(!fields[0].contains(QRegExp("[//]"))){
                    if(fields[0].contains(QRegExp("[-]")))
                    {
                        // slite in function of '-' and add field[1] content
                        fields = fields[0].split("-") << fields[1];
                        temp.origin = fields[0].toInt();
                        temp.destination = fields[1].toInt();

                        // check if the title is a single type or a pathern
                        if(fields[2].contains(QRegExp("[,]"))){
                            x = fields[2].count(",") +1;
                            fields << fields[2].split(",");
                            for(int i=3;i < 3+x ;i++){
                                temp.tile.push_back(fields[i].toInt());
                            }
                        } else {
                            temp.tile.push_back(fields[2].toInt());
                        }
                    } else {
                        temp.origin = fields[0].toInt();
                        if(fields[1].contains(QRegExp("[,]"))){
                            throw  "Error : Impossible Map config !";
                        } else {
                            temp.tile.push_back(fields[1].toInt());
                        }
                    }
                    Room_Map.push_back(temp);
                }
            }
        }
    } catch (const char * chaine) {
        qCritical(chaine);
        Room_Map.clear();
        Front.clear();
    }

    spriteFrame l_frame;
    unsigned short l_x, l_y;
    tilesObject tile;

    if(Room_Map.size()!=0){
        // try to well fill "Front" vector with "Room_Map" content
        try {
            for(unsigned int i=0;  i < Room_Map.size(); i++){
                if(Room_Map[i].destination == -1){
                    l_frame = loadFrame(Room_Map[i].tile[0]);
                    if(l_frame.level == 0 &&
                            l_frame.shift == 0 &&
                            l_frame.width == 0 &&
                            l_frame.height == 0){
                        throw "Error : wrong on existant type of tile";
                    }
                    l_x=load_x(Room_Map[i].origin);
                    l_y=load_y(Room_Map[i].origin);
                    tile = {l_frame,l_x,l_y};
                    Front.push_back(tile);
                }
                else
                {
                    for(int y=Room_Map[i].origin ;y <Room_Map[i].destination;y++){
                        if(Room_Map[i].tile.size()!=1){
                            // fill l_frame with pathern in order
                            l_frame = loadFrame(Room_Map[i].tile[y % (int)Room_Map[i].tile.size()]);
                        }
                        else{
                            l_frame = loadFrame(Room_Map[i].tile[0]);
                        }

                        if(l_frame.level == 0 &&
                                l_frame.shift == 0 &&
                                l_frame.width == 0 &&
                                l_frame.height == 0){
                            throw "Error : wrong on existant type of tile";
                        }

                        l_x=load_x(y);
                        l_y=load_y(y);
                        tile = {l_frame,l_x,l_y};
                        Front.push_back(tile);
                    }
                }
            }
        } catch (const char * chaine) {
            qCritical(chaine);
            Front.clear();
        }
    }
}

void room::Draw(QPainter *p_painter, QPixmap p_pixmap)
{
    for (unsigned int i = 0; i < Front.size(); i++)
    {
        p_painter->drawPixmap(Front[i].x,Front[i].y,Front[i].frame.width,Front[i].frame.height,p_pixmap,Front[i].frame.shift,Front[i].frame.level,Front[i].frame.width,Front[i].frame.height);
     }
}

spriteFrame room::loadFrame(int p_type)
{
    switch (p_type) {
        case 0:
            return frameGnd[0];
        case 1:
            return frameGnd[1];
        case 2:
            return frameGnd[2];
        case 3:
            return frameGnd[3];
        case 4:
            return frameWall[0];
        case 5:
            return frameWall[1];
        case 6:
            return frameWall[2];
        case 7:
            return frameWall[3];
        case 8:
            return frameWall[4];
        case 9:
            return frameWall[5];
        case 10:
            return frameWall[6];
        default:
            qCritical("Tile type do not exist");
            return {0,0,0,0};
    }
}

unsigned short room::load_x(int p_position)
{
    return (unsigned short) (p_position % 53)*16;
}

unsigned short room::load_y(int p_position)
{
    return (unsigned short) (p_position / 53)*16;
}

std::vector<tilesObject> room::getFront()
{
    return Front;
}

std::vector<tilesObject> room::getBack()
{
    return Back;
}


