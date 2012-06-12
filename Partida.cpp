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

bool Partida::comprobarSolucion(void)
{
    if(this->tablero->resolverTablero())
        return EXITO;
    else
        return ERROR;


   // return EXITO;
}





