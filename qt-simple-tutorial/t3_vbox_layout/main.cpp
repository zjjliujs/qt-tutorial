/****************************************************************
 **
 ** Qt tutorial 3
 **
 ****************************************************************/

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QSizePolicy>

int main( int argc, char **argv ) {
    QApplication a( argc, argv );

    QPushButton * quit = new QPushButton("Quit");
    quit->setFont(QFont( "Times", 18, QFont::Bold ));
    quit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    quit->setMinimumSize(200, 50);

    QWidget *window = new QWidget;

    QVBoxLayout * box = new QVBoxLayout;
    //box->setMargin(100);
    box->addWidget(quit);

    QObject::connect( quit, SIGNAL(clicked()), &a, SLOT(quit()) );

    window->setLayout(box);
    window->show();

    return a.exec();
}
