#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include <list>

#include "Ayuda.h"
#include "Partida.h"
#include "Tablero.h"
#include "Tiempos.h"

using namespace std;

class Juego
{
    Ayuda ayuda;
    Partida partida;
    Tiempos *tiempos;
public:
    Juego();
    void nuevaPartida();
    string mostrarAyuda();

    int getLevel(void);
    void setLevel(int level);
    void setValorUser(int,int,int);
    int getValorUser(int,int);
    void setFichaValor(int, int, int);
    int getFichaValor(int, int);
    bool comprobarSolucion(void);
    bool getFichaBloqueada (int fila, int col);
    int getFichaSumaDerecha (int fila, int col);
    int getFichaSumaAbajo (int fila, int col);
    void setTiempoName (const char *name);
    char * getTiempoName (void);
    void setTiempoLevel(int level);
    int getTiempoLevel(void);
    void setTiempoTime(int seconds);
    int getTiempoTime(void);
    void saveScores(void);
    list<Registro> loadScores(void);



};

#endif // JUEGO_H
