/****************************************************************
**
** Qt tutorial 2
**
****************************************************************/

#include <QApplication>
#include <QPushButton>
#include <QFont>


int main( int argc, char **argv ) {
    QApplication app( argc, argv );

    QPushButton quit_button( "Quit", 0 );
    //quit_button.resize( 75, 30 );
    quit_button.setFont( QFont( "Times", 18, QFont::Bold ) );

    QObject::connect( &quit_button, SIGNAL(clicked()), &app, SLOT(quit()) );

    quit_button.show();
    return app.exec();
}
