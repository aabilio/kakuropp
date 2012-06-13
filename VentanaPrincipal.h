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

    bool isayuda;
    bool istiempos;
    bool isIniciado;

    int seconds;
    int totalSeconds;
    static const int TAM=9;

    QString playerName;
    QString lcdtext;

    Controlador *controlador;
    FichaVentana *fichas[TAM][TAM];

    //Widget y objetos QT4
    QWidget *principal;

    QHBoxLayout *layoutPrincipal;
    QVBoxLayout *botonera;
    QGridLayout *grid;

    QSpacerItem *espacioVertical;
    QSpacerItem *espacioHorizontal;

    QPushButton *nuevo_facil;
    QPushButton *nuevo_medio;
    QPushButton *nuevo_dificil;
    QPushButton *pause;
    QPushButton *continuar;
    QPushButton *comoJugar;
    QPushButton *cerrar;
    QPushButton *terminar;
    QPushButton *resolver;
    QPushButton *save;
    QPushButton *tiempos;

    QStandardItemModel *Modelfacil;
    QStandardItemModel *Modelmedio;
    QStandardItemModel *Modeldificil;

    QTableView *Highfacil;
    QTableView *Highmedio;
    QTableView *Highdificil;

    QLabel *msgInputName;
    QLabel *finalMsg;
    QLabel *msgSaved;

    QLineEdit *inputName;

    QTextBrowser *qtbrowser;

    QLCDNumber *lcd;

    QTimer *timer;
    QTime *time;

public:
    explicit VentanaPrincipal();
    void ColocarFichas();
    void BorrarFichas(int);
    void PintarFichas(int,int);
    void NuevoJuego(int);
signals:
    
public slots:
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
};

#endif // VENTANAPRINCIPAL_H
