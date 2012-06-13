#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"

#define EXITO 0
#define ERROR 1

class Partida
{
    int level;
public:
    Partida();
    Tablero *tablero;
    void nuevoTablero();
    void resolverPartida();
    bool comprobarSolucion();
    void setLevel (int level);
    int getLevel(void);
};

#endif // PARTIDA_H
