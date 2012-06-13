#ifndef TIEMPOS_H
#define TIEMPOS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

using namespace std;

#define FILENAME "tiempos.sav"
#define DEBUG "debug.txt"
#define MODE fstream::in | fstream::out | fstream::app | fstream::ate
#define MAX_TAM 256
#define MAX_NAME 32

typedef struct
{
    char nombre[MAX_NAME];
    int time;
    int level;
} Registro;

typedef Registro * RegistroRef;

class Tiempos
{
    fstream file;
    char name[MAX_NAME];
    int time;
    int level;

    static int ComparerTime(Registro x, Registro y);
    list <Registro> sortList(list <Registro> L);

public:
    Tiempos();
    Tiempos(char *name, int level);
    void setName(const char *name);
    char * getName(void);
    void setLevel(int level);
    int getLevel(void);
    void setTime(int seconds);
    int getTime(void);
    void saveScores(void);
    list<Registro> loadScores(void);
};

#endif // TIEMPOS_H
