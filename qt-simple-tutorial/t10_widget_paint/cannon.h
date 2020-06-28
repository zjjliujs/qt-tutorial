/****************************************************************
**
** Definition of CannonField class, Qt tutorial 8
**
****************************************************************/

#ifndef CANNON_H
#define CANNON_H

#include <QWidget>


class CannonField : public QWidget {
    Q_OBJECT
  public:
    CannonField( QWidget *parent = 0);

    int angle() const {
        return ang;
    }
    int force() const {
        return f;
    }

  public slots:
    void setAngle( int degrees );
    void setForce( int newton);

  signals:
    void angleChanged( int );
    void forceChanged( int );

  protected:
    QRect cannonRect() const;
    void paintEvent( QPaintEvent * );

  private:
    void brushBackground();
    int ang;
    int f;
};


#endif // CANNON_H
