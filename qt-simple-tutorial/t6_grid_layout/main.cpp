/****************************************************************
**
** Qt tutorial 6
**
****************************************************************/

#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>
#include <QFont>
#include <QVBoxLayout>
#include <QGridLayout>

class LCDRange : public QWidget {
  public:
    LCDRange( QWidget *parent = 0);
};

LCDRange::LCDRange( QWidget *parent)
    : QWidget( parent) {
    QLCDNumber *lcd  = new QLCDNumber( 2, this);
    QSlider * slider = new QSlider( Qt::Horizontal, this);
    slider->setRange( 0, 99 );
    slider->setValue( 0 );
    connect( slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)) );

    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(lcd);
    vbox->addWidget(slider);
    setLayout(vbox);
}

class MyWidget : public QWidget {
  public:
    MyWidget( QWidget *parent = 0);
};


MyWidget::MyWidget( QWidget *parent)
    : QWidget( parent, Qt::FramelessWindowHint) {
    QPushButton *quit = new QPushButton( "Quit", this);
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );

    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    QGridLayout *grid = new QGridLayout;

    for( int r = 0 ; r < 4 ; r++ )
        for( int c = 0 ; c < 5 ; c++ ) {
            LCDRange * lcd = new LCDRange;
            grid->addWidget(lcd, r, c);
        }

    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(quit);
    vbox->addLayout(grid);
    setLayout(vbox);
}

int main( int argc, char **argv ) {
    QApplication a( argc, argv );

    MyWidget w;
    w.show();
    return a.exec();
}
