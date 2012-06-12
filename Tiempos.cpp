#include "Tiempos.h"

Tiempos::Tiempos()
{
    //this->name = new char [MAX_NAME];
}

Tiempos::Tiempos(char *name, int l): level(l)
{
    sprintf(this->name, "%s", name);
}

void Tiempos::setName(const char *name)
{
  //qDebug() << "Nombre recibido: " << name;
    strncpy(this->name,name,24);
    //sprintf(this->name, "%s", name);
   // qDebug << "hola";
}

char * Tiempos::getName(void)
{
    //char *tmp;
    //tmp = new char[MAX_NAME];
    //sprintf(tmp, "%s", this->name);
    return this->name; //tmp;
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

