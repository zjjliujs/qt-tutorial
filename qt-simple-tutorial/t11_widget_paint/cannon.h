/****************************************************************
**
** Definition of CannonField class, Qt tutorial 8
**
****************************************************************/

#ifndef CANNON_H
#define CANNON_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QSizePolicy>
#include <QRect>

class CannonField : public QWidget {
    Q_OBJECT
  public:
    CannonField( QWidget *parent = 0);

  public:
    void setButton (QWidget * button);

    int angle() const {
        return ang;
    }
    int force() const {
        return f;
    }

  public slots:
    void setAngle( int degrees );
    void setForce( int newton);
    void shoot();

  private slots:
    void moveShot();

  signals:
    void angleChanged( int );
    void forceChanged( int );

  protected:
    void paintEvent( QPaintEvent * );
    void enterEvent( QEvent * );

  private:
    void  paintShot( QPainter * );
    void  paintCannon( QPainter * );
    QRect cannonRect() const;
    QRect shotRect() const;

    void brushBackground();
    int ang;
    int f;

    int timerCount;
    QTimer * autoShootTimer;
    float shoot_ang;
    float shoot_f;
    QWidget * button = nullptr;
};


#endif // CANNON_H
