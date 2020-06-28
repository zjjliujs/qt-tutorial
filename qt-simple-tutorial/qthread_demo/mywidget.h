#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMutex>
#include "mythread.h"

class MyWidget : public QWidget {
    Q_OBJECT

  public:
    MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void createView();

  private slots:
    void openThreadBtnSlot();
    void closeThreadBtnSlot();
    void finishedThreadBtnSlot();
    //void testBtnSlot();

  private:
    QVBoxLayout * mainLayout;
    MyThread * thread1;
};

#endif // MYWIDGET_H
