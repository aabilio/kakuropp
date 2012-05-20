#include "fichaventana.h"

FichaVentana::FichaVentana(int _fila,int _col, QWidget *parent) :
    QSpinBox(parent)
{
    //Asignar fila y columna
    fila = _fila;
    columna = _col;
}

//Slot recibe valor
void FichaVentana::recibir_valor(int valor)
{
    //Enviar señal con valor, fila y columna
    emit completar_senal(valor,fila,columna);
}
