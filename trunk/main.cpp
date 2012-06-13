#include <QApplication>
#include <QHBoxLayout>


#include "VentanaPrincipal.h"

int main (int argc, char *argv[])
{
    QApplication app(argc,argv);

    app.setStyle("plastique");

    VentanaPrincipal ventana;
    ventana.setGeometry(350,40,0,0);

    ventana.show();

    return app.exec();
}
