#include "Juego.h"

Juego::Juego()
{
    this->tiempos = new Tiempos;
}

void Juego::nuevaPartida()
{
    this->partida.nuevoTablero();
}

QString Juego::mostrarAyuda()
{
    QString html;
    html = this->ayuda.getAyudaHtml();

    return html;
}
