#include "Fichas.h"

Fichas::Fichas()
{
    bloqueada = false;
    valor = 0;
}
void Fichas::setBloqueada(bool _bloq)
{
    bloqueada = _bloq;
}

bool Fichas::getBloqueada()
{
    return bloqueada;
}

void Fichas::setValor(int _valor)
{
    valor = _valor;
}

int Fichas::getValor()
{
    return valor;
}
