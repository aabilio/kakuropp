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
    this->file.open(FILENAME, MODE);
    this->file << this->name << " * " << this->time << " * " << this->level << endl;
    this->file.close();
}

list<Registro> Tiempos::loadScores(void)
{
    list <Registro> L;
    list <Registro>::iterator elemento;
    FILE *file = NULL;
    Registro tmp;

    if ((file = fopen(FILENAME, "r")) == NULL)
    {
        return L;
    }

    while(!feof(file))
    {
        fscanf(file, " %[^*] * %d * %d\n", tmp.nombre, &tmp.time, &tmp.level);
        L.push_front(tmp);
    }
    fclose(file);

    L.sort(this->ComparerTime); //Ordena de mayor a menor tiempo
    L.reverse(); //Le da la vuelta a la lista, de menor a mayor

    return L;
}

int Tiempos::ComparerTime(Registro x, Registro y)
{
    if (x.time > y.time) return 1;
    else if (x.time <= y.time) return 0;

    return -1;
}

list <Registro> Tiempos::sortList(list <Registro> L)
{
    L.sort(this->ComparerTime);
    return L;
}

