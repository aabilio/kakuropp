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

int Controlador::getLevel(void)
{
    return this->juego.partida.getLevel();
}

void Controlador::setLevel(int level)
{
    this->juego.partida.setLevel(level);
}
void Controlador::setValorUser(int valor, int fila,int columna)
{
    this->juego.partida.tablero->fichas[fila][columna].setValorUser(valor);
}

bool Controlador::comprobarSolucion(void)
{
    return this->juego.partida.comprobarSolucion();
}
