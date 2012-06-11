#ifndef FICHAS_H
#define FICHAS_H

class Fichas
{
    bool bloqueada;
    int valor;
    int valor_user;
    int sumaDer;
    int sumaAbajo;
public:
    Fichas();
    void setBloqueada(bool);
    bool getBloqueada();
    void setValor(int);
    int getValor();
    int getSumaDer();
    void setSumaDer(int);
    int getSumaAbajo();
    void setSumaAbajo(int);
    int getValorUser();
    void setValorUser(int);
};

#endif // FICHAS_H
