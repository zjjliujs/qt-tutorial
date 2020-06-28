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

  public slots:
    void setAngle( int degrees );

  signals:
    void angleChanged( int );

  protected:
    void paintEvent( QPaintEvent * );

  private:
    void brushBackground();
    int ang;
};


#endif // CANNON_H
