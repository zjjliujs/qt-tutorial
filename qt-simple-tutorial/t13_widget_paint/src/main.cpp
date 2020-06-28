/****************************************************************
**
** Qt tutorial 8
**
****************************************************************/

#include <Qt>
#include <QApplication>
#include <QPushButton>
#include <QLCDNumber>
#include <QFont>
#include <QLayout>

#include "lcdrange.h"
#include "cannon.h"
#include "gamebrd.h"


int main( int argc, char **argv ) {
    QApplication a( argc, argv );
    GameBoard w;
    w.setGeometry( 0, 0, 500, 355);
    w.show();
    return a.exec();
}
