#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QSpinBox>
#include <QGridLayout>
#include <QPushButton>

#include "fichaventana.h"


class Controlador;

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
    static const int TAM=9;
    Controlador *controlador;
    //Widget y objetos QT4
    QWidget *principal;
    QHBoxLayout *layoutPrincipal;
    QGridLayout *grid;
    //boton pause
    QPushButton *pause;
    QPushButton *continuar;
    //Tam: tamano del tablero dificil
    FichaVentana *fichas[TAM][TAM];

public:
    explicit VentanaPrincipal();
    void ColocarFichas();
    void BorrarFichas();
    void PintarFichas(int,int);
    
signals:
    
public slots:
    //Slot (Valor, fila, columna)
    void CambiarValor(int,int,int);
    void NuevoJuego();
    //Slot dificulad (por ahora no)
    
};

#endif // VENTANAPRINCIPAL_H
