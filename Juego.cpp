#include "Juego.h"

Juego::Juego()
{

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
