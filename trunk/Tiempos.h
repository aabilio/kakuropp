#ifndef TIEMPOS_H
#define TIEMPOS_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define FILE "tiempos.sav"
#define MODE fstream::in | fstream::out | fstream::app | fstream::ate
#define MAX_TAM 256
#define MAX_NAME 32

typedef struct
{
    char *nombre[MAX_NAME];
    int time;
    int level;
} Registro;

typedef Registro * RegistroRef;

class Tiempos
{
    fstream file;
    char name[25];
    int time;
    int level;

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
    RegistroRef loadScores(void);
};

#endif // TIEMPOS_H
