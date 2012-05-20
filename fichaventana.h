#ifndef FICHAVENTANA_H
#define FICHAVENTANA_H

#include <QSpinBox>

class FichaVentana : public QSpinBox
{
    Q_OBJECT

    int fila,columna;
public:
    explicit FichaVentana(int,int, QWidget *parent = 0);

signals:
    //Enviar Valor, fila y columna
    void completar_senal(int,int,int);
public slots:
    //recibe valor
    void recibir_valor(int);
};

#endif // FICHAVENTANA_H
