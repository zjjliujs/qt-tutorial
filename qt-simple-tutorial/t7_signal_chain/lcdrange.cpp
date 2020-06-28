/****************************************************************
**
** Implementation of LCDRange class, Qt tutorial 7
**
****************************************************************/

#include "lcdrange.h"

#include <Qt>
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>

LCDRange::LCDRange( QWidget *parent)
        : QWidget( parent)
{
    QLCDNumber *lcd  = new QLCDNumber( 2, this);
    slider = new QSlider( Qt::Horizontal, this);
    slider->setRange( 0, 99 );
    slider->setValue( 0 );
    connect( slider, SIGNAL(valueChanged(int)),
             lcd, SLOT(display(int)) );
    connect( slider, SIGNAL(valueChanged(int)),
             SIGNAL(valueChanged(int)) );

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(lcd);
    vbox->addWidget(slider);
    setLayout(vbox);
}

int LCDRange::value() const
{
    return slider->value();
}

void LCDRange::setValue( int value )
{
    slider->setValue( value );
}
