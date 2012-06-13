#include "Controlador.h"

Controlador::Controlador(VentanaPrincipal *_ventana):
    ventana(_ventana)
{
}

void Controlador::pulsarNuevo(void)
{
    this->juego.nuevaPartida();
}

string Controlador::pulsarAyuda(void)
{
    string html;
    html = juego.mostrarAyuda();
    //Comentario de siempre
    return html;
}
