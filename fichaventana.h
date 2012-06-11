#ifndef FICHAVENTANA_H
#define FICHAVENTANA_H

#include <QSpinBox>

class FichaVentana : public QSpinBox
{
    Q_OBJECT

    int fila,columna;
public:
    FichaVentana(QWidget *parent = 0);
    explicit FichaVentana(int,int, QWidget *parent = 0);
    void setFilCol(int f, int c);

signals:
    //Enviar Valor, fila y columna
    void completar_senal(int,int,int);
public slots:
    //recibe valor
    void recibir_valor(int);
};

#endif // FICHAVENTANA_H
