//#include <QApplication>
//#include "Scene_Display.h"

//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);

//    Scene_Display display;
//    display.setWindowTitle("metroid test");
//    display.setBaseSize(840,640);
//    display.show();

//    return app.exec();
//}


/*------------------------------------------ */

#include <QApplication>
#include "menu.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Menu menu;
    menu.show();

    return app.exec();
}
