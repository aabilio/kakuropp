#include "VentanaPrincipal.h"
#include <QObject>
#include <QTextStream>
#include <QTextDocument>
#include "Controlador.h"

VentanaPrincipal::VentanaPrincipal()
{
    //Definicion de Qobjetos locales
    QVBoxLayout *botonera;
    //Botones
    QPushButton *nuevo;
    QPushButton *resolver;
    QPushButton *cerrar;
    //Espacios
    QSpacerItem *espacioVertical;
    QSpacerItem *espacioHorizontal;


    //Instanciar controlador
    controlador = new Controlador(this);
    //Instanciacion de objetos
    principal = new QWidget(this);
    qtbrowser = new QTextBrowser(this);
    layoutPrincipal = new QHBoxLayout(principal);
    botonera = new QVBoxLayout();
    grid = new QGridLayout();
    espacioVertical = new QSpacerItem(20,100,QSizePolicy::Minimum,QSizePolicy::Expanding);
    espacioHorizontal = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    //Botones
    nuevo = new QPushButton(tr("&Nuevo Juego"));
    nuevo->setShortcut(tr("n"));
    resolver = new QPushButton(tr("&Resolver"));
    resolver->setShortcut(tr("r"));
    cerrar = new QPushButton(tr("Cerrar"));
    cerrar->setShortcut(tr("Esc"));
    comoJugar = new QPushButton(tr("Reglas"));
    comoJugar->setShortcut(tr("?"));
    isayuda = false;
    pause = new QPushButton(tr("&Pause"));
    pause->setShortcut(tr("p"));
    continuar = new QPushButton(tr("&Continuar"));
    continuar->setShortcut(tr("p"));
    //resto de botones

    //Tamaño botones
    #ifdef Q_WS_MAC
      nuevo->setMaximumWidth(150);
      cerrar->setMaximumWidth(150);
      comoJugar->setMaximumWidth(150);
      pause->setMaximumWidth(150);
      continuar->setMaximumWidth(150);
    #else
      nuevo->setMaximumWidth(100);
      cerrar->setMaximumWidth(100);
      comoJugar->setMaximumWidth(100);
      pause->setMaximumWidth(100);
      continuar->setMaximumWidth(100);
    #endif

    //Conectar botones
    QObject::connect(cerrar,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(nuevo,SIGNAL(clicked()),this,SLOT(NuevoJuego()));
    QObject::connect(resolver,SIGNAL(clicked()),this,SLOT(Resolver()));
    //Botones pausa y continuar aparecen y desaparecen
    QObject::connect(nuevo,SIGNAL(clicked()),continuar,SLOT(hide()));
    QObject::connect(nuevo,SIGNAL(clicked()),pause,SLOT(show()));

    QObject::connect(comoJugar,SIGNAL(clicked()),this,SLOT(MostrarAyuda()));
    QObject::connect(pause,SIGNAL(clicked()),comoJugar,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),comoJugar,SLOT(show()));

    QObject::connect(pause,SIGNAL(clicked()),continuar,SLOT(show()));
    QObject::connect(pause,SIGNAL(clicked()),pause,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),pause,SLOT(show()));
    QObject::connect(continuar,SIGNAL(clicked()),continuar,SLOT(hide()));

    //Ordenar layout y botones
    //Insertar botones
    botonera->addWidget(nuevo);
    botonera->addWidget(resolver);
    botonera->addWidget(cerrar);
    botonera->addItem(espacioVertical);
    botonera->addWidget(comoJugar);
    botonera->addWidget(pause);
    botonera->addWidget(continuar);
    continuar->hide();


    //Insertar botonera
    layoutPrincipal->addLayout(botonera);
    layoutPrincipal->addItem(espacioHorizontal);
    layoutPrincipal->addWidget(qtbrowser);
    qtbrowser->hide();

    // Para juntarse los spinbox (te gusta?):
    grid->setHorizontalSpacing(0);
    grid->setVerticalSpacing(0);

    //Insertar Grid
    layoutPrincipal->addLayout(grid);

    //Conectar Widget principal
    setCentralWidget(principal);

    //mostrar
    this->show();

    //Iniciar primer tablero
    ColocarFichas();

}

//SLOT mostrar ayuda
void VentanaPrincipal::MostrarAyuda()
{
    QLocale spanish(QLocale::Spanish, QLocale::Spain);
    int dificultad = 8, fila, columna;
    static QString html;
    static QTextDocument *doc = new QTextDocument;
    html = this->controlador->pulsarAyuda();
    doc->setHtml(html);
    this->qtbrowser->setDocument(doc);

    //FIXME: mejorar el tamaño. El programa se cierra si dificultad < 8
    //this->qtbrowser->setGeometry(1000, 1000, 400, 400);
    this->qtbrowser->setMinimumSize(this->principal->width()-200,this->principal->height()-100);
    //this->qtbrowser->setMinimumSize(200,200);
    this->qtbrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->qtbrowser->setLocale(spanish);

    //Al pulsar en la ayuda
    if (this->isayuda) //La ayuda ya en pantalla
    {
        //Esconder ayuda:
        this->qtbrowser->hide();
        //Mostrar Fichas
        for(fila=0;fila<dificultad;fila++)
            for(columna=0;columna<dificultad;columna++)
              this->fichas[fila][columna]->show();

        this->isayuda = false;
        pause->show();
    }
    else //No hay ayuda en pantalla
    {
        //Esconder Fichas
        for(fila=0;fila<dificultad;fila++)
            for(columna=0;columna<dificultad;columna++)
              this->fichas[fila][columna]->hide();
        //Mostrar ayuda:
        this->qtbrowser->show();

        this->isayuda = true;
        pause->hide();
    }
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
    //Esto es una prueba
    this->controlador->pulsarNuevo();
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
    int dificultad = 8;
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
            QObject::connect(pause,SIGNAL(clicked()),fichas[fila][columna],SLOT(hide()));
        }
}

void VentanaPrincipal::PintarFichas(int fila,int columna)
{
    //Letra de no bloqueadas y bloqueadas
    #ifdef Q_WS_MAC
      QFont noBloqueadas("Arial",37,QFont::Normal);
      QFont bloqueadas("Arial",19,QFont::Bold);
    #else
      QFont noBloqueadas("Arial",19,QFont::Normal);
      QFont bloqueadas("Arial",19,QFont::Bold);
    #endif


    //Cosas comunes
    fichas[fila][columna]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    fichas[fila][columna]->setAlignment(Qt::AlignCenter);
    fichas[fila][columna]->setButtonSymbols(QSpinBox::NoButtons);
    fichas[fila][columna]->setMinimumSize(80,80);

    //Comprobar el valor en el modelo
    //Esto hay que cambiarlo
    if(!this->controlador->juego.partida.tablero->fichas[fila][columna].getBloqueada())/*Aqui hay que comprobar el valor */
    {
        fichas[fila][columna]->setRange(0,9);
        fichas[fila][columna]->setStyleSheet("background-color: rgb(211, 211, 211);");
        fichas[fila][columna]->setFont(noBloqueadas);
        //fichas[fila][columna]->setValue(this->controlador->juego.partida.tablero.fichas[fila][columna].getValor());
        fichas[fila][columna]->clear();
    }else
    {
        char cadena[8];
        fichas[fila][columna]->setRange(0,50);
        fichas[fila][columna]->setStyleSheet("background-color: qconicalgradient(cx:0.493318, cy:0.676, angle:327.6, stop:0.340909 rgba(192, 192, 192, 255), stop:0.346591 rgba(155, 155, 155, 255));");
        //Esto hay que mejorarlo(con metodos)
        //Estos else if son para dibujar las sumas, hay que mejorarlo
        //falla algo
        if(this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer()!= 0
                && this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer()!= 0)
            #ifdef Q_WS_MAC
              sprintf(cadena, "%d   %d",this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo(),this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer());
            #else // Otros que no mac (windows por ejemplo):
              sprintf(cadena, "%d  %d",this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo(),this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer());
            #endif
        else if(this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer() == 0 &&
                this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo() != 0)
            #ifdef Q_WS_MAC

            sprintf(cadena, "%d     ",this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo());
            #else
              sprintf(cadena, "%d    ",this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo());
            #endif
        else if(this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo() == 0
                && this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer() != 0)
            sprintf(cadena, "    %d",this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo());
        else
        {
            sprintf(cadena,"   ");
            fichas[fila][columna]->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0, y1:0.431818, x2:1, y2:0.437273, stop:0 rgba(151, 151, 151, 255), stop:1 rgba(124, 124, 124, 255));");
        }
        fichas[fila][columna]->setSpecialValueText(cadena);
       // fichas[fila][columna]->setValue(this->controlador->juego.partida.tablero.fichas[fila][columna].getSumaDer());//Comprobar en el modelo
        fichas[fila][columna]->setDisabled(TRUE);

        fichas[fila][columna]->setFont(bloqueadas);
    }
}

void VentanaPrincipal::Resolver()
{
    int dificultad = 8;
    for(int fila=0;fila<dificultad;fila++)
        for(int columna=0;columna<dificultad;columna++)
        {
            if(!this->controlador->juego.partida.tablero->fichas[fila][columna].getBloqueada())/*Aqui hay que comprobar el valor */
            {
                fichas[fila][columna]->setValue(this->controlador->juego.partida.tablero->fichas[fila][columna].getValor());

            }
        }

}
