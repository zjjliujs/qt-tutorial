/****************************************************************
**
** Implementation of GameBoard class, Qt tutorial 13
**
****************************************************************/

#include "gamebrd.h"

#include <QFont>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QLayout>

#include "lcdrange.h"
#include "cannon.h"

GameBoard::GameBoard( QWidget *parent)
    : QWidget( parent) {
    QPushButton *quit = new QPushButton( "&Quit", this);
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    LCDRange *angle  = new LCDRange( "ANGLE", this );
    angle->setRange( 5, 70 );

    LCDRange *force  = new LCDRange( "FORCE", this);
    force->setRange( 10, 50 );

    cannonField = new CannonField( this);

    connect( angle, SIGNAL(valueChanged(int)),
             cannonField, SLOT(setAngle(int)) );
    connect( cannonField, SIGNAL(angleChanged(int)),
             angle, SLOT(setValue(int)) );

    connect( force, SIGNAL(valueChanged(int)),
             cannonField, SLOT(setForce(int)) );
    connect( cannonField, SIGNAL(forceChanged(int)),
             force, SLOT(setValue(int)) );

    connect( cannonField, SIGNAL(hit()),
             this, SLOT(hit()) );
    connect( cannonField, SIGNAL(missed()),
             this, SLOT(missed()) );

    QPushButton *shoot = new QPushButton( "&Shoot", this);
    shoot->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( shoot, SIGNAL(clicked()), SLOT(fire()) );
    connect( cannonField, SIGNAL(canShoot(bool)),
             shoot, SLOT(setEnabled(bool)) );

    QPushButton *restart
        = new QPushButton( "&New Game", this);
    restart->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( restart, SIGNAL(clicked()), this, SLOT(newGame()) );

    hits = new QLCDNumber( 2, this);
    shotsLeft = new QLCDNumber( 2, this);
    QLabel *hitsL = new QLabel( "HITS", this);
    QLabel *shotsLeftL = new QLabel( "SHOTS LEFT", this);

    QGridLayout *grid = new QGridLayout( this);
    grid->addWidget( quit, 0, 0 );
    grid->addWidget( cannonField, 1, 1 );
    grid->setColumnStretch( 1, 10 );

    QVBoxLayout *leftBox = new QVBoxLayout;
    grid->addLayout( leftBox, 1, 0 );
    leftBox->addWidget( angle );
    leftBox->addWidget( force );

    QHBoxLayout *topBox = new QHBoxLayout;
    grid->addLayout( topBox, 0, 1 );
    topBox->addWidget( shoot );
    topBox->addWidget( hits );
    topBox->addWidget( hitsL );
    topBox->addWidget( shotsLeft );
    topBox->addWidget( shotsLeftL );
    topBox->addStretch( 1 );
    topBox->addWidget( restart );

    angle->setValue( 60 );
    force->setValue( 25 );
    angle->setFocus();

    newGame();
}


void GameBoard::fire() {
    if ( cannonField->gameOver() || cannonField->isShooting() )
        return;
    shotsLeft->display( shotsLeft->intValue() - 1 );
    cannonField->shoot();
}


void GameBoard::hit() {
    hits->display( hits->intValue() + 1 );
    if ( shotsLeft->intValue() == 0 )
        cannonField->setGameOver();
    else
        cannonField->newTarget();
}


void GameBoard::missed() {
    if ( shotsLeft->intValue() == 0 )
        cannonField->setGameOver();
}


void GameBoard::newGame() {
    shotsLeft->display( 15 );
    hits->display( 0 );
    cannonField->restartGame();
    cannonField->newTarget();
}
