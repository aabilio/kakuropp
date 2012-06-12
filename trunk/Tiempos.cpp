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

void Tiempos::loadScores(void)
{
    list <Registro> L;
    list <Registro>::iterator elemento;

    //Para recorrer:
    //for (elemento=L.begin(); elemento != L.end(); ++elemento)
    //  this->file << elemento->time << endl;

    //Para ordenar de mayor a menor:
    //L.sort(this->ComparerTime);

}

int Tiempos::ComparerTime(Registro x, Registro y)
{
    if (x.time > y.time) return 1;
    else if (x.time <= y.time) return 0;
    //else if (x.time < y.time) return -1;
}

list <Registro> Tiempos::sortList(list <Registro> L)
{
    L.sort(this->ComparerTime);
    return L;
}

