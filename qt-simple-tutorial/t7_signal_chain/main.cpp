/****************************************************************
**
** Qt tutorial 7
**
****************************************************************/

#include <QApplication>
#include <QPushButton>
#include <QLCDNumber>
#include <QFont>
#include <QVBoxLayout>
#include <QGridLayout>

#include "lcdrange.h"


class MyWidget : public QWidget
{
public:
    MyWidget( QWidget *parent=0);
};


MyWidget::MyWidget( QWidget *parent)
        : QWidget( parent)
{
    QPushButton *quit = new QPushButton( "Quit", this);
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    QGridLayout *grid = new QGridLayout;

    LCDRange *previous = 0;
    for( int r = 0 ; r < 4 ; r++ ) {
        for( int c = 0 ; c < 4 ; c++ ) {
            LCDRange* lr = new LCDRange;
            if ( previous ){
                connect( lr, SIGNAL(valueChanged(int)),
                         previous, SLOT(setValue(int)) );
            }
            previous = lr;
            grid->addWidget(lr, r, c);
        }
    }

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(quit);
    vbox->addLayout(grid);

    setLayout(vbox);
}


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MyWidget w;
    w.show();
    return a.exec();
}
