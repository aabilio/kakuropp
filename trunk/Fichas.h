#ifndef FICHAS_H
#define FICHAS_H

class Fichas
{
    bool bloqueada;
    int valor;
public:
    Fichas();
    void setBloqueada(bool);
    bool getBloqueada();
    void setValor(int);
    int getValor();
};

#endif // FICHAS_H
