#include <QApplication>
#include <QHBoxLayout>

#include "VentanaPrincipal.h"

int main (int argc, char *argv[])
{
    QApplication app(argc,argv);

    VentanaPrincipal ventana;

    //Mostrar ventena:
    ventana.show();

    return app.exec();
}
