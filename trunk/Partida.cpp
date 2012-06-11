#include "Partida.h"
#include <QtGui>
Partida::Partida()
{
    level = 5;
    tablero = new Tablero(this->level);
    tiempo = 0;
}

void Partida::nuevoTablero()
{
    qDebug () << "ejecuto nuevo tablero";
    while(!tablero->generarTablero(this->level))
    {
        delete tablero;
        tablero = new Tablero(this->level);
    }
}

void Partida::setLevel(int level)
{
    this->level = level;
}

int Partida::getLevel(void)
{
    return this->level;
}
