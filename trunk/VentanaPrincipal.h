#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QSpinBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>

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
    QTextBrowser *qtbrowser;
    //boton pause
    QPushButton *pause;
    QPushButton *continuar;
    QPushButton *comoJugar;
    bool isayuda;
    //Tam: tamano del tablero dificil
    FichaVentana *fichas[TAM][TAM];

public:
    explicit VentanaPrincipal();
    void ColocarFichas();
    void BorrarFichas(int);
    void PintarFichas(int,int);
    void NuevoJuego(int);
signals:
    
public slots:
    //Slot (Valor, fila, columna)
    void CambiarValor(int,int,int);
    void Resolver();
    void MostrarAyuda();
    void NuevoJuegoFacil();
    void NuevoJuegoMedio();
    void NuevoJuegoDificil();
    void JuegoTerminado();
    void slotcontinuar();
    void slotpause();
    //Slot dificulad (por ahora no)
    
};

#endif // VENTANAPRINCIPAL_H
