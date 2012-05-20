#ifndef JUEGO_H
#define JUEGO_H

#include "Ayuda.h"
#include "Partida.h"
#include "Tablero.h"
#include "Tiempos.h"

class Juego
{
public:
    Juego();

    Ayuda ayuda;
    Partida partida;
    Tiempos *tiempos;
};

#endif // JUEGO_H
