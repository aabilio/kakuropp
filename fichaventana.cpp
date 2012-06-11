#include "fichaventana.h"

FichaVentana::FichaVentana(QWidget *parent) :
    QSpinBox(parent)
{

}

FichaVentana::FichaVentana(int _fila,int _col, QWidget *parent) :
    QSpinBox(parent)
{
    //Asignar fila y columna
    fila = _fila;
    columna = _col;
}

void FichaVentana::setFilCol(int f, int c)
{
    this->fila = f;
    this->columna = c;
}

//Slot recibe valor
void FichaVentana::recibir_valor(int valor)
{
    //Enviar señal con valor, fila y columna
    emit completar_senal(valor,fila,columna);
}
