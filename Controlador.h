#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QtCore>
#include <QtGui>


#include "VentanaPrincipal.h"
#include "Juego.h"

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(VentanaPrincipal *ventana);

    VentanaPrincipal *ventana;
    Juego juego;

    void pulsarNuevo();
    QString pulsarAyuda();

signals:
    
public slots:
    
};

#endif // CONTROLADOR_H
