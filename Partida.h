#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"
#include "ctime"

class Partida
{
    int level;
public://borrar
    Tablero *tablero;
    int tiempo;
public:
    Partida();
    void nuevoTablero();
    void resolverPartida();
    void setLevel (int level);
    int getLevel(void);
};

#endif // PARTIDA_H
