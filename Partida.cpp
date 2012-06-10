#include "Partida.h"

Partida::Partida()
{
    tablero = new Tablero;
    tiempo = 0;
}

void Partida::nuevoTablero()
{
    while(!tablero->generarTablero())
    {
        delete tablero;
        tablero = new Tablero;
    }
}