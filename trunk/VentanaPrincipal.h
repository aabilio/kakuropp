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
#include <list>
#include <QTableView>
#include <QStandardItemModel>

#include "fichaventana.h"

#define EXITO 0
#define ERROR 1

#define MAX_NAME 32


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

    QTableView *Highfacil;
    QStandardItemModel *Modelfacil;
    QStandardItemModel *Modelmedio;
    QStandardItemModel *Modeldificil;
    QTableView *Highmedio;
    QTableView *Highdificil;

    QLabel *msgInputName;
    QLineEdit *inputName;
    QLabel *finalMsg;
    QPushButton *save;
    QPushButton *tiempos;
    QLabel *msgSaved;

    QLCDNumber *lcd;
    QString lcdtext;
    QTimer *timer;
    QTime *time;
    int seconds;
    int totalSeconds;

    bool isayuda;
    bool istiempos;
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
    void MostrarTiempos();
    //Slot dificulad (por ahora no)
    
};

//typedef struct
//{
//    char nombre[MAX_NAME];
//    int time;
//    int level;
//} Registro;

#endif // VENTANAPRINCIPAL_H
