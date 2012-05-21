#include "VentanaPrincipal.h"
#include <QObject>
#include "Controlador.h"

VentanaPrincipal::VentanaPrincipal()
{
    //Definicion de Qobjetos locales
    QVBoxLayout *botonera;
    QPushButton *nuevo;
    //Otros botones
    QPushButton *cerrar;
    QSpacerItem *espacioVertical;
    QSpacerItem *espacioHorizontal;


    //Instanciacion de objetos
    principal = new QWidget(this);
    layoutPrincipal = new QHBoxLayout(principal);
    botonera =new QVBoxLayout();
    grid = new QGridLayout();
    espacioVertical = new QSpacerItem(20,100,QSizePolicy::Minimum,QSizePolicy::Expanding);
    espacioHorizontal = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    //Botones
    nuevo = new QPushButton("Nuevo Juego");
    cerrar = new QPushButton("Cerrar");
    pause = new QPushButton("Pause");
    continuar = new QPushButton("Continuar");
    //resto de botones

    //Tamaño botones
    nuevo->setMaximumWidth(100);
    cerrar->setMaximumWidth(100);
    pause->setMaximumWidth(100);
    continuar->setMaximumWidth(100);

    //Conectar botones
    QObject::connect(cerrar,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(nuevo,SIGNAL(clicked()),this,SLOT(NuevoJuego()));
    //Botones pausa y continuar aparecen y desaparecen
    QObject::connect(pause,SIGNAL(clicked()),continuar,SLOT(show()));
    QObject::connect(pause,SIGNAL(clicked()),pause,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),pause,SLOT(show()));
    QObject::connect(continuar,SIGNAL(clicked()),continuar,SLOT(hide()));
    //Ordenar layout y botones
    //Insertar botones
    botonera->addWidget(nuevo);
    botonera->addWidget(cerrar);
    botonera->addItem(espacioVertical);
    botonera->addWidget(pause);
    botonera->addWidget(continuar);
    continuar->hide();


    //Insertar botonera
    layoutPrincipal->addLayout(botonera);
    layoutPrincipal->addItem(espacioHorizontal);

    //Insertar Grid
    layoutPrincipal->addLayout(grid);

    //Conectar Widget principal
    setCentralWidget(principal);

    //mostrar
    this->show();

    //Iniciar primer tablero
    ColocarFichas();

}

//SLOT cambiar valor
void VentanaPrincipal::CambiarValor(int valor,int fila,int columna)
{
    //Se necesita funciones de controlador para conectar
    //con la logica del programa
}

//SLOT Nuevo Juego
void VentanaPrincipal::NuevoJuego()
{
    //Se borra tablero
    BorrarFichas();
    //se inicia tablero
    ColocarFichas();
}

//metodo borrar fichas
void VentanaPrincipal::BorrarFichas()
{
    int tam = grid->columnCount(); //Cuento las columnas, col == filas

    for(int fila=0;fila<tam;fila++)
        for(int columna=0;columna<tam;columna++)
        {
            grid->removeWidget(fichas[fila][columna]);
            delete fichas[fila][columna];
        }
    grid->update();
}
//Metodo colocar fichas
void VentanaPrincipal::ColocarFichas()
{
    int fila,columna;
    //Comproba dificultad en el modelo para
    //definir tamaño del tablero
    int dificultad = 6;
    for(fila=0;fila<dificultad;fila++)
        for(columna=0;columna<dificultad;columna++)
        {
            //Instanciar y pintar dependiendo del valor
            fichas[fila][columna] = new FichaVentana(fila,columna);
            PintarFichas(fila,columna);
            //añadir yconectar fichas
            grid->addWidget(fichas[fila][columna],fila,columna);
            QObject::connect(fichas[fila][columna],SIGNAL(valueChanged(int)),fichas[fila][columna],SLOT(recibir_valor(int)));
            QObject::connect(fichas[fila][columna],SIGNAL(completar_senal(int,int,int)),this,SLOT(CambiarValor(int,int,int)));
            //Conexiones para pausar y continuar
            QObject::connect(pause,SIGNAL(clicked()),fichas[fila][columna],SLOT(hide()));
            QObject::connect(continuar,SIGNAL(clicked()),fichas[fila][columna],SLOT(show()));
        }
}

void VentanaPrincipal::PintarFichas(int fila,int columna)
{
    //Letra de no bloqueadas y bloqueadas
    QFont noBloqueadas("Arial",24,QFont::Normal);
    QFont bloqueadas("Arial",24,QFont::Bold);

    //Cosas comunes
    fichas[fila][columna]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    fichas[fila][columna]->setAlignment(Qt::AlignCenter);
    fichas[fila][columna]->setButtonSymbols(QSpinBox::NoButtons);
    fichas[fila][columna]->setMinimumSize(60,60);

    //Comprobar el valor en el modelo
    if(1)/*Aqui hay que comprobar el valor */
    {
        fichas[fila][columna]->setRange(0,9);
        fichas[fila][columna]->setStyleSheet("background-color: rgb(211, 211, 211);");
        fichas[fila][columna]->setFont(noBloqueadas);
        fichas[fila][columna]->clear();
    }else
    {
        fichas[fila][columna]->setRange(0,50);
        fichas[fila][columna]->setValue(8);//Comprobar en el modelo
        fichas[fila][columna]->setDisabled(TRUE);
        fichas[fila][columna]->setStyleSheet("background-color: rgb(203, 158, 159);color: rgb(0, 0, 0);");
        fichas[fila][columna]->setFont(bloqueadas);
    }
}
