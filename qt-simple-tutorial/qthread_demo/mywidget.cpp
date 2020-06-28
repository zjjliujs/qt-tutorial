#include "mywidget.h"
#include <QDebug>
#include <windows.h>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent) {
    createView();
}

MyWidget::~MyWidget() {
}


void MyWidget::createView() {
    /*添加界面*/
    QPushButton *openThreadBtn = new QPushButton(tr("打开线程"));
    QPushButton *closeThreadBtn = new QPushButton(tr("关闭线程"));
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(openThreadBtn);
    mainLayout->addWidget(closeThreadBtn);
    mainLayout->addStretch();
    connect(openThreadBtn, SIGNAL(clicked(bool)), this, SLOT(openThreadBtnSlot()));
    connect(closeThreadBtn, SIGNAL(clicked(bool)), this, SLOT(closeThreadBtnSlot()));

    /*线程初始化*/
    thread1 = new MyThread;
    connect(thread1, SIGNAL(finished()), this, SLOT(finishedThreadBtnSlot()));
}

void MyWidget::openThreadBtnSlot() {
    /*开启一个线程*/
    thread1->start();
    qDebug() << "主线程id：" << QThread::currentThreadId();
}

void MyWidget::closeThreadBtnSlot() {
    /*关闭多线程*/
    thread1->closeThread();
    thread1->wait();
}

void MyWidget::finishedThreadBtnSlot() {
    qDebug() << tr("完成信号finished触发") << QThread::currentThreadId();
}
