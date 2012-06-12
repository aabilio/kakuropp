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
    //AQUI SE TIENE QUE COMPROBAR LA SOLUCIÓN DADA POR EL USUARIO Y DEVOLVER "EXITO" SI BIEN Y "ERROR" SI MAL!!

    //Comprobar repeticiones en Filas de no bloqueadas:
    /*for (int F=0; F<this->level; F++)
      for (int C=0; C<this->level; C++)
        if (this->tablero->fichas[F][C] )*/


    return EXITO;
}





