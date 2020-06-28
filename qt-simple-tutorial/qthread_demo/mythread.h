#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>

class MyThread : public QThread {
  public:
    MyThread();
    virtual ~MyThread();

  public:
    void closeThread();

  protected:
    virtual void run();
    virtual bool isStopped();

  private:
    QMutex * mutex;
    volatile bool stopped;
    //isStop是易失性变量，需要用volatile进行申明
};

#endif // MYTHREAD_H
