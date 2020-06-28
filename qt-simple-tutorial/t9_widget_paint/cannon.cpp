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
    QPainter p( this );

    p.setBrush( QColorConstants::Svg::blue );
    p.setPen( Qt::NoPen );

    p.translate( rect().width() / 2., rect().height() / 2. );
    p.drawPie( QRect(-35, -35, 70, 70), 0, 180 * 16 );
    //坐标系顺时针旋转-ang度
    p.rotate( -ang );
    p.drawRect( QRect(33, -4, 15, 8) );
}

QSizePolicy CannonField::sizePolicy() const {
    return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}
