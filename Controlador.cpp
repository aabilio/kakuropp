#include <QTextStream>
#include "Controlador.h"

Controlador::Controlador(VentanaPrincipal *_ventana):
    ventana(_ventana)
{

}

void Controlador::pulsarNuevo(void)
{
    this->juego.nuevaPartida();
}

QString Controlador::pulsarAyuda(void)
{
    QString html;
    html = juego.mostrarAyuda();
    //Comentario de siempre
    return html;
}

int Controlador::getLevel(void)
{
    return this->juego.partida.getLevel();
}

void Controlador::setLevel(int level)
{
    this->juego.partida.setLevel(level);
}
void Controlador::setValorUser(int valor, int fila,int columna)
{
    qDebug() << "Fila-Columna:" << fila << "-" << columna << " ";
    this->juego.partida.tablero->fichas[fila][columna].setValorUser(valor);
}
