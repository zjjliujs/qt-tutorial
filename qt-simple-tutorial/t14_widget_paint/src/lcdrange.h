/****************************************************************
**
** Definition of LCDRange class, Qt tutorial 8
**
****************************************************************/

#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

class LCDRange : public QWidget {
    Q_OBJECT
  public:
    LCDRange( QWidget *parent = 0);
    LCDRange( const char *label, QWidget * parent = 0);

    int value() const;
    const char *labelText() const;

  public slots:
    void setValue( int );
    void setRange( int minVal, int maxVal );
    void setLabelText( const char * );

  signals:
    void valueChanged( int );

  private:
    void init();

    QSlider * slider;
    QLabel * label;
};


#endif // LCDRANGE_H

