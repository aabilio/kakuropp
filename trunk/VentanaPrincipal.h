#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QSpinBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include <QLabel>

#include "fichaventana.h"

#define EXITO 0
#define ERROR 1


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
    //Otros botones
    QPushButton *terminar;
    QPushButton *resolver;
    //boton pause
    QPushButton *pause;
    QPushButton *continuar;
    QPushButton *comoJugar;


    QLabel *msgInputName;
    QLineEdit *inputName;
    QLabel *finalMsg;
    QPushButton *save;
    QLabel *msgSaved;

    QLCDNumber *lcd;
    QString lcdtext;
    QTimer *timer;
    QTime *time;
    int seconds;
    int totalSeconds;

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
    void showTime();
    void saveResults();
    //Slot dificulad (por ahora no)
    
};

#endif // VENTANAPRINCIPAL_H