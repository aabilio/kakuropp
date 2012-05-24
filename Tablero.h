#ifndef TABLERO_H
#define TABLERO_H

#include "Fichas.h"
#include <cstdlib>
#include <ctime>
#define MAX 20

class Tablero
{public://borrar
    Fichas fichas[MAX][MAX];
    int dificultad;
public:
    Tablero();
    bool generarTablero();
    bool asignarValor();
    bool colocarBloqueadas();
    bool colocarValor(int,int);
    bool colocarSumas();
    void reiniciarFichas();
    int aleatorio(int a, int b)
    {
        return a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1));
    };

};

#endif // TABLERO_H
