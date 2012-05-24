#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"
#include "ctime"

class Partida
{public://borrar
    Tablero *tablero;
    int tiempo;
public:
    Partida();
    void nuevoTablero();
    void resolverPartida();
};

#endif // PARTIDA_H
