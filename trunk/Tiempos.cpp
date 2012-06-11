#include "Tiempos.h"

Tiempos::Tiempos()
{
}

Tiempos::Tiempos(char *name, int l): level(l)
{
    sprintf(this->name, "%s", name);
}

void Tiempos::setName(char *name)
{
    sprintf(this->name, "%s", name);
}

char * Tiempos::getName(void)
{
    char *tmp;
    tmp = new char[MAX_NAME];
    sprintf(tmp, "%s", this->name);
    return tmp;
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

