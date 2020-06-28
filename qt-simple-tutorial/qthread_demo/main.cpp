#include <QApplication>
#include "mywidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MyWidget w;
    w.resize(960, 640);
    w.show();
    return a.exec();
}
