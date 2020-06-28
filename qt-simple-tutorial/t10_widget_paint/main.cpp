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


class MyWidget: public QWidget {
  public:
    MyWidget( QWidget *parent = 0);
};


MyWidget::MyWidget( QWidget *parent)
    : QWidget( parent) {
    QPushButton *quit = new QPushButton( "&Quit", this );
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    LCDRange *angle = new LCDRange( this );
    angle->setRange( 5, 70 );

    LCDRange *force  = new LCDRange( this );
    force->setRange( 10, 50 );

    CannonField *cannonField = new CannonField( this);

    connect( angle, SIGNAL(valueChanged(int)),
             cannonField, SLOT(setAngle(int)) );
    connect( cannonField, SIGNAL(angleChanged(int)),
             angle, SLOT(setValue(int)) );

    connect( force, SIGNAL(valueChanged(int)),
             cannonField, SLOT(setForce(int)) );
    connect( cannonField, SIGNAL(forceChanged(int)),
             force, SLOT(setValue(int)) );

    QGridLayout *grid = new QGridLayout( this);
    grid->addWidget( quit, 0, 0 );
    QVBoxLayout *leftBox = new QVBoxLayout;
    //grid->addLayout( leftBox, 1, 0 );
    leftBox->addWidget( angle );
    leftBox->addWidget( force );
    grid->addLayout(leftBox, 1, 0, Qt::AlignBottom );

    grid->addWidget( cannonField, 0, 1, 2, 2);
    grid->setColumnStretch(1, 10 );

    angle->setValue( 60 );
    force->setValue( 25 );
    angle->setFocus();
}


int main( int argc, char **argv ) {
    QApplication a( argc, argv );
    MyWidget w;
    w.setGeometry( 0, 0, 500, 355);
    w.show();
    return a.exec();
}
