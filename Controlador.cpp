#include <QTextStream>
#include "Controlador.h"

Controlador::Controlador(VentanaPrincipal *_ventana):
    ventana(_ventana)
{

}

void Controlador::pulsarNuevo(void)
{
    this->juego.nuevaPartida();
}

QString Controlador::pulsarAyuda(void)
{
    QString html;
    html = juego.mostrarAyuda();

    return html;
}
