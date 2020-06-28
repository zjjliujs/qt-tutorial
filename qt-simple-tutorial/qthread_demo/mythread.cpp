#include "mythread.h"

#include <QDebug>
#include <QMutex>

MyThread::MyThread() {
    stopped = false;
    mutex = new QMutex(QMutex::Recursive);
}

MyThread::~MyThread() {
    delete mutex;
}

void MyThread::closeThread() {
    mutex->lock();
    stopped = true;
    qDebug() << tr("CloseThread called, by thread:") << QThread::currentThreadId();
    mutex->unlock();
}

bool MyThread::isStopped() {
    mutex->lock();
    qDebug() << tr("isStopped called, by thread:") << QThread::currentThreadId();
    return stopped;
    mutex->unlock();
}

void MyThread::run() {
    while (1) {
        mutex->lock();
        if(stopped)
            return;
        qDebug() << tr("mythread QThread::currentThreadId()==") << QThread::currentThreadId();
        mutex->unlock();
        sleep(1);
    }
}
