#include "Tiempos.h"

Tiempos::Tiempos()
{

}

Tiempos::Tiempos(char *name, int l): level(l)
{
    sprintf(this->name, "%s", name);
}

void Tiempos::setName(const char *name)
{
    strncpy(this->name,name,MAX_NAME);
}

char * Tiempos::getName(void)
{
    return this->name;
}

void Tiempos::setLevel(int level)
{
    this->level = level;
}

int Tiempos::getLevel(void)
{
    return this->level;
}

void Tiempos::setTime(int seconds)
{
    this->time = seconds;
}

int Tiempos::getTime(void)
{
    return this->time;
}

void Tiempos::saveScores(void)
{
    this->file.open(FILE, MODE);
    this->file << this->name << ";" << this->time << ";" << this->level << endl;
    this->file.close();
}

RegistroRef Tiempos::loadScores(void)
{
    char **tmp;
    string line;
    RegistroRef reg;

    tmp = new char * [MAX_TAM];
    for (int i=0; i<MAX_TAM; i++) tmp[i] = new char[MAX_TAM];

    this->file.open(FILE, MODE);

    reg = new Registro;
    for (int i=0; getline(this->file, line); i++)
    {
        //reg->level = line.
    }

}

