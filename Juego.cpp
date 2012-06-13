#include "Juego.h"

Juego::Juego()
{
    this->tiempos = new Tiempos;
}

void Juego::nuevaPartida()
{
    this->partida.nuevoTablero();
}

string Juego::mostrarAyuda()
{
    string html;
    html = this->ayuda.getAyudaHtml();

    return html;
}
