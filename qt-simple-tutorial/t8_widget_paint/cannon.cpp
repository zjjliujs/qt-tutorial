/****************************************************************
**
** Implementation CannonField class, Qt tutorial 8
**
****************************************************************/

#include "cannon.h"
#include <QPainter>


CannonField::CannonField( QWidget *parent)
    : QWidget( parent) {
    ang = 45;
    setPalette( QPalette( QColor( 250, 250, 200) ) );
}

void CannonField::setAngle( int degrees ) {
    if ( degrees < 5 )
        degrees = 5;
    if ( degrees > 70 )
        degrees = 70;
    if ( ang == degrees )
        return;
    ang = degrees;
    repaint();
    emit angleChanged( ang );
}

void CannonField::paintEvent( QPaintEvent * ) {
    QString s = "Angle = " + QString::number( ang );
    brushBackground();
    //int x = (int)(rect().width()/2.f);
    //int y = (int)(rect().height()/2.f);
    //qDebug("paintEvent, x %d, y %d", x, y);
    QPainter p( this );
    p.drawText(rect(), Qt::AlignVCenter | Qt::AlignHCenter, s );
}

void CannonField::brushBackground(void) {
    QPainter p( this );
    p.setBrush(QBrush(QColor(255, 0, 0)));
    p.drawRect(rect());
}
