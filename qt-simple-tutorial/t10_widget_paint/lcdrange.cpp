/****************************************************************
**
** Implementation of LCDRange class, Qt tutorial 8
**
****************************************************************/

#include "lcdrange.h"

#include <Qt>
#include <QSlider>
#include <QLCDNumber>

LCDRange::LCDRange( QWidget *parent)
    : QWidget( parent) {
    QLCDNumber *lcd  = new QLCDNumber( 2, this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange( 0, 99 );
    slider->setValue( 0 );
    connect( slider, SIGNAL(valueChanged(int)),
             lcd, SLOT(display(int)) );
    connect( slider, SIGNAL(valueChanged(int)),
             SIGNAL(valueChanged(int)) );

    setFocusProxy( slider );

    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(lcd);
    vbox->addWidget(slider);
    setLayout(vbox);
}

int LCDRange::value() const {
    return slider->value();
}

void LCDRange::setValue( int value ) {
    qDebug("setValue, value: %d", value);
    slider->setValue( value );
}

void LCDRange::setRange( int minVal, int maxVal ) {
    if ( minVal < 0 || maxVal > 99 || minVal > maxVal ) {
        qWarning( "LCDRange::setRange(%d,%d)\n"
                  "\tRange must be 0..99\n"
                  "\tand minVal must not be greater than maxVal",
                  minVal, maxVal );
        return;
    }
    slider->setRange( minVal, maxVal );
}
