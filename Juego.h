#ifndef JUEGO_H
#define JUEGO_H

#include <string>

#include "Ayuda.h"
#include "Partida.h"
#include "Tablero.h"
#include "Tiempos.h"

using namespace std;

class Juego
{
public:
    Juego();
    void nuevaPartida();
    string mostrarAyuda();

    Ayuda ayuda;
    Partida partida;
    Tiempos *tiempos;
};

#endif // JUEGO_H
