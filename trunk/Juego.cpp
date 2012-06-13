#include "Juego.h"

Juego::Juego()
{
    this->tiempos = new Tiempos;
}

void Juego::nuevaPartida()
{
    this->partida.nuevoTablero();
}

string Juego::mostrarAyuda()
{
    string html;
    html = this->ayuda.getAyudaHtml();

    return html;
}

int Juego::getLevel(void)
{
    return this->partida.getLevel();
}

void Juego::setLevel(int level)
{
    this->partida.setLevel(level);
}
void Juego::setValorUser(int valor, int fila,int columna)
{
    this->partida.tablero->fichas[fila][columna].setValorUser(valor);
}

bool Juego::comprobarSolucion(void)
{
    return this->partida.comprobarSolucion();
}

bool Juego::getFichaBloqueada (int fila, int col)
{
    return this->partida.tablero->fichas[fila][col].getBloqueada();
}

int Juego::getFichaSumaDerecha (int fila, int col)
{
    return this->partida.tablero->fichas[fila][col].getSumaDer();
}

int Juego::getFichaSumaAbajo (int fila, int col)
{
    return this->partida.tablero->fichas[fila][col].getSumaAbajo();
}

int Juego::getValorUser(int fila, int col)
{
    return this->partida.tablero->fichas[fila][col].getValorUser();
}

void Juego::setFichaValor(int valor, int fila, int col)
{
    this->partida.tablero->fichas[fila][col].setValor(valor);
}

int Juego::getFichaValor(int fila, int col)
{
    return this->partida.tablero->fichas[fila][col].getValor();
}

void Juego::setTiempoName (const char *name)
{
    this->tiempos->setName(name);
}

char * Juego::getTiempoName (void)
{
    return this->tiempos->getName();
}

void Juego::setTiempoLevel(int level)
{
    this->tiempos->setLevel(level);
}

int Juego::getTiempoLevel(void)
{
    return this->tiempos->getLevel();
}

void Juego::setTiempoTime(int seconds)
{
    this->tiempos->setTime(seconds);
}

int Juego::getTiempoTime(void)
{
    return this->tiempos->getTime();
}

void Juego::saveScores(void)
{
    this->tiempos->saveScores();
}

list<Registro> Juego::loadScores(void)
{
    return this->tiempos->loadScores();
}
