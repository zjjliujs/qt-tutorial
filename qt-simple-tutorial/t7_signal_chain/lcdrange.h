/****************************************************************
**
** Definition of LCDRange class, Qt tutorial 7
**
****************************************************************/

#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>
#include <QVBoxLayout>

class QSlider;


class LCDRange : public QWidget
{
    Q_OBJECT
public:
    LCDRange( QWidget *parent=0);

    int value() const;

public slots:
    void setValue( int );

signals:
    void valueChanged( int );

private:
    QSlider *slider;
};


#endif // LCDRANGE_H
