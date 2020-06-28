/****************************************************************
 **
 ** Qt tutorial 5
 **
 ****************************************************************/
#include <Qt>
#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>
#include <QFont>

#include <QVBoxLayout>

class MyWidget : public QWidget {
  public:
    MyWidget( QWidget *parent = 0);
};


MyWidget::MyWidget( QWidget *parent)
    : QWidget(parent) {
    QPushButton *quit = new QPushButton( "Quit", this);
    quit->setFont( QFont( "Times", 18, QFont::Bold ) );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    QLCDNumber *lcd  = new QLCDNumber( 2, this);

    QSlider * slider = new QSlider( Qt::Horizontal, this);
    slider->setRange( 0, 99 );
    slider->setValue( 0 );
    connect( slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)) );

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(quit);
    layout->addWidget(lcd);
    layout->addWidget(slider);
    setLayout(layout);
}

int main( int argc, char **argv ) {
    QApplication a( argc, argv );

    MyWidget w;
    w.show();
    return a.exec();
}
