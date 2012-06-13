#include "Partida.h"

Partida::Partida()
{
    level = 7;
    tablero = new Tablero(this->level);
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

}





