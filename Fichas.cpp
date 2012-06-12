#include "Fichas.h"
#include <QtGui>

Fichas::Fichas()
{
    bloqueada = false;
    valor = 0;
    valor_user = 0;
    sumaDer = 0;
    sumaAbajo = 0;
}
void Fichas::setBloqueada(bool _bloq)
{
    bloqueada = _bloq;
}

bool Fichas::getBloqueada()
{
    return bloqueada;
}
void Fichas::setValorUser(int _valor)
{
    valor_user = _valor;
}
int Fichas::getValorUser()
{
    return valor_user;
}

void Fichas::setValor(int _valor)
{
    valor = _valor;
}

int Fichas::getValor()
{
    return valor;
}
void Fichas::setSumaDer(int _suma)
{
    sumaDer = _suma;
}
int Fichas::getSumaDer()
{
    return sumaDer;
}
void Fichas::setSumaAbajo(int _suma)
{
    sumaAbajo = _suma;
}
int Fichas::getSumaAbajo()
{
    return sumaAbajo;
}
