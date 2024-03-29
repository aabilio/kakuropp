#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <string>

using namespace std;

#include "VentanaPrincipal.h"
#include "kakuro/Juego.h"

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador (VentanaPrincipal *ventana);

    VentanaPrincipal *ventana;
    Juego juego;

    string pulsarAyuda();
    void pulsarNuevo();


signals:
    
public slots:
    
};

#endif // CONTROLADOR_H
