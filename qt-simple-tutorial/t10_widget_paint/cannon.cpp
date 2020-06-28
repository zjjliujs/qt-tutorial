/****************************************************************
**
** Implementation CannonField class, Qt tutorial 8
**
****************************************************************/

#include "cannon.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

CannonField::CannonField( QWidget *parent)
    : QWidget( parent) {
    ang = 45;
    f = 0;
    setPalette( QPalette( QColor( 250, 250, 250) ) );
}

void CannonField::setAngle( int degrees ) {
    if ( degrees < 5 )
        degrees = 5;
    if ( degrees > 70 )
        degrees = 70;
    if ( ang == degrees )
        return;
    ang = degrees;
    repaint(cannonRect());
    emit angleChanged( ang );
}

void CannonField::setForce( int newton ) {
    if ( newton < 0 )
        newton = 0;
    if ( f == newton )
        return;
    f = newton;
    emit forceChanged( f );
}

void CannonField::paintEvent( QPaintEvent * e ) {
    brushBackground();

    if ( !e->rect().intersects( cannonRect() ) )
        return;

    QRect cr = cannonRect();
    QPixmap pix( cr.size() );
    //pix.fill( this, cr.topLeft() );

    QPainter p( &pix );
    p.setBrush( QColorConstants::Svg::blue );
    p.setPen( Qt::NoPen );
    p.translate( 0, pix.height() - 1 );
    p.drawPie( QRect( -35, -35, 70, 70 ), 0, 90 * 16 );
    p.rotate( -ang );
    p.drawRect( QRect(33, -4, 15, 8) );
    p.end();

    p.begin( this );
    p.drawPixmap( cr.topLeft(), pix );
}

void CannonField::brushBackground() {
    QPainter p( this );
    p.setBrush(QBrush(QColor(255, 0, 0)));
    p.drawRect(rect());
}

QRect CannonField::cannonRect() const {
    QRect r( 0, 0, 50, 50 );
    //r.moveBottomLeft( rect().bottomLeft() );
    //r.moveBottomRight(rect().bottomRight());
    r.moveCenter(rect().center());
    return r;
}
