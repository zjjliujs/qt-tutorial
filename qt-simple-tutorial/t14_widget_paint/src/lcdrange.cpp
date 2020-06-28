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

    init();
}

LCDRange::LCDRange(const char *label, QWidget * parent)
    : QWidget(parent) {

    init();
    setLabelText(label);
}

void LCDRange::init() {
    QLCDNumber *lcd  = new QLCDNumber( 2, this);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange( 0, 99 );
    slider->setValue( 0 );

    label = new QLabel( " ", this );
    label->setAlignment( Qt::AlignCenter );

    connect( slider, SIGNAL(valueChanged(int)),
             lcd, SLOT(display(int)) );
    connect( slider, SIGNAL(valueChanged(int)),
             SIGNAL(valueChanged(int)) );

    setFocusProxy( slider );

    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(lcd);
    vbox->addWidget(slider);
    vbox->addWidget(label);
    setLayout(vbox);
}

int LCDRange::value() const {
    return slider->value();
}

void LCDRange::setValue( int value ) {
    qDebug("setValue, value: %d", value);
    slider->setValue( value );
}

const char *LCDRange::labelText() const {
    std::string str = label->text().toStdString();
    const char* ch = str.c_str();
    return ch;
}

void LCDRange::setLabelText(const char * text) {
    label->setText(text);
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
