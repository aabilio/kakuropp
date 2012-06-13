#include "VentanaPrincipal.h"
#include <QObject>
#include <QTextStream>
#include <QTextDocument>
#include <QtGui>
#include "Controlador.h"

VentanaPrincipal::VentanaPrincipal()
{
    //Definicion de Qobjetos locales
    QVBoxLayout *botonera;
    //Botones
    QPushButton *nuevo_facil;
    QPushButton *nuevo_medio;
    QPushButton *nuevo_dificil;
    QPushButton *cerrar;

    QString playerName;

    //Instanciar timer:
    lcd = new QLCDNumber;
    lcd->setNumDigits(8);
    this->seconds = 0;
    time = new QTime;
    time->setHMS(0,0,0,0);
    timer = new QTimer(this);

    this->lcdtext = time->toString("hh:mm:ss");
    lcd->display(this->lcdtext);
    lcd->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0, y1:0.431818, x2:1, y2:0.437273, stop:0 rgba(151, 151, 151, 255), stop:1 rgba(124, 124, 124, 255));");
    lcd->setSegmentStyle(QLCDNumber::Outline);
    lcd->setFrameStyle(QFrame::NoFrame);


    //Instanciar controlador
    controlador = new Controlador(this);
    //Instanciacion de objetos
    this->msgInputName = new QLabel(this);
    this->inputName = new QLineEdit(this);
    principal = new QWidget(this);
    qtbrowser = new QTextBrowser(this);
    finalMsg = new QLabel(this);
    msgSaved = new QLabel(this);
    layoutPrincipal = new QHBoxLayout(principal);
    botonera = new QVBoxLayout();
    grid = new QGridLayout();
    espacioVertical = new QSpacerItem(20,100,QSizePolicy::Minimum,QSizePolicy::Expanding);
    espacioHorizontal = new QSpacerItem(0,0/*,QSizePolicy::Expanding,QSizePolicy::Minimum*/);
    Highfacil = new QTableView(this);
    Modelfacil = new QStandardItemModel(20,2);
    Highmedio = new QTableView(this);
    Modelmedio = new QStandardItemModel(20,2);
    Highdificil = new QTableView(this);
    Modeldificil = new QStandardItemModel(20,2);


    Modelfacil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Highfacil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Modelmedio->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Highmedio->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Modeldificil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Highdificil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Modelfacil->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre")));
    Modelfacil->setHorizontalHeaderItem(1, new QStandardItem(QString("Tiempo (fácil)")));
    Highfacil->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Highfacil->setModel(Modelfacil);
    Modelmedio->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre")));
    Modelmedio->setHorizontalHeaderItem(1, new QStandardItem(QString("Tiempo (medio)")));
    Highmedio->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Highmedio->setModel(Modelmedio);
    Modeldificil->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre")));
    Modeldificil->setHorizontalHeaderItem(1, new QStandardItem(QString("Tiempo (difícil)")));
    Highdificil->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Highdificil->setModel(Modeldificil);

    //Botones
    nuevo_facil = new QPushButton(tr("&Fácil"));
    nuevo_facil->setShortcut(tr("f"));
    nuevo_medio = new QPushButton(tr("&Medio"));
    nuevo_medio->setShortcut(tr("m"));
    nuevo_dificil = new QPushButton(tr("&Difícil"));
    nuevo_dificil->setShortcut(tr("d"));
    resolver = new QPushButton(tr("&Solución"));
    resolver->setShortcut(tr("s"));
    terminar = new QPushButton(tr("&Comprobar"));
    terminar->setShortcut(tr("c"));
    cerrar = new QPushButton(tr("Cerrar"));
    cerrar->setShortcut(tr("Esc"));
    comoJugar = new QPushButton(tr("Reglas"));
    comoJugar->setShortcut(tr("?"));
    isayuda = false;
    pause = new QPushButton(tr("&Pausa"));
    pause->setShortcut(tr("p"));
    continuar = new QPushButton(tr("&Continuar"));
    continuar->setShortcut(tr("p"));
    //resto de botones
    this->save = new QPushButton(tr("&Guardar"));
    this->save->setShortcut(tr("g"));
    this->tiempos = new QPushButton(tr("&Tiempos"));
    this->tiempos->setShortcut(tr("t"));
    this->istiempos = false;

    //Tamaño botones
    #ifdef Q_WS_MAC
      nuevo_facil->setMaximumWidth(150);
      nuevo_medio->setMaximumWidth(150);
      nuevo_dificil->setMaximumWidth(150);
      terminar->setMaximumWidth(150);
      cerrar->setMaximumWidth(150);
      comoJugar->setMaximumWidth(150);
      pause->setMaximumWidth(150);
      continuar->setMaximumWidth(150);
      msgInputName->setMaximumSize(150,20);
      inputName->setMaximumSize(150,20);
      lcd->setMaximumWidth(150);
      msgSaved->setMaximumSize(150,20);
    #else
      nuevo_facil->setMaximumWidth(100);
      nuevo_medio->setMaximumWidth(100);
      nuevo_dificil->setMaximumWidth(100);
      terminar->setMaximumWidth(100);
      cerrar->setMaximumWidth(100);
      comoJugar->setMaximumWidth(100);
      pause->setMaximumWidth(100);
      continuar->setMaximumWidth(100);
      msgInputName->setMaximumSize(100,25);
      inputName->setMaximumSize(100,25);
      lcd->setMaximumWidth(100);
      msgSaved->setMaximumSize(100,25);
    #endif

    //Conectar timer:
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

    //Conectar botones
    QObject::connect(cerrar,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(nuevo_facil,SIGNAL(clicked()),this,SLOT(NuevoJuegoFacil()));
    QObject::connect(nuevo_medio,SIGNAL(clicked()),this,SLOT(NuevoJuegoMedio()));
    QObject::connect(nuevo_dificil,SIGNAL(clicked()),this,SLOT(NuevoJuegoDificil()));
    QObject::connect(resolver,SIGNAL(clicked()),this,SLOT(Resolver()));
    //Botones pausa y continuar, terminar y resolver aparecen y desaparecen
    QObject::connect(terminar,SIGNAL(clicked()),this,SLOT(JuegoTerminado()));
        //Para boton facil
    QObject::connect(nuevo_facil,SIGNAL(clicked()),continuar,SLOT(hide()));
    QObject::connect(nuevo_facil,SIGNAL(clicked()),pause,SLOT(show()));
    QObject::connect(nuevo_facil,SIGNAL(clicked()),terminar,SLOT(show()));
    QObject::connect(nuevo_facil,SIGNAL(clicked()),resolver,SLOT(show()));
        //Para boton medio
    QObject::connect(nuevo_medio,SIGNAL(clicked()),continuar,SLOT(hide()));
    QObject::connect(nuevo_medio,SIGNAL(clicked()),pause,SLOT(show()));
    QObject::connect(nuevo_medio,SIGNAL(clicked()),terminar,SLOT(show()));
    QObject::connect(nuevo_medio,SIGNAL(clicked()),resolver,SLOT(show()));
        //para boton dificil
    QObject::connect(nuevo_dificil,SIGNAL(clicked()),continuar,SLOT(hide()));
    QObject::connect(nuevo_dificil,SIGNAL(clicked()),pause,SLOT(show()));
    QObject::connect(nuevo_dificil,SIGNAL(clicked()),terminar,SLOT(show()));
    QObject::connect(nuevo_dificil,SIGNAL(clicked()),resolver,SLOT(show()));

    QObject::connect(comoJugar,SIGNAL(clicked()),this,SLOT(MostrarAyuda()));
    QObject::connect(pause,SIGNAL(clicked()),comoJugar,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),comoJugar,SLOT(show()));

    QObject::connect(tiempos,SIGNAL(clicked()),this,SLOT(MostrarTiempos()));
    QObject::connect(pause,SIGNAL(clicked()),tiempos,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),tiempos,SLOT(show()));

    QObject::connect(pause,SIGNAL(clicked()),continuar,SLOT(show()));
    QObject::connect(pause,SIGNAL(clicked()),pause,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),pause,SLOT(show()));
    QObject::connect(continuar,SIGNAL(clicked()),continuar,SLOT(hide()));
    QObject::connect(continuar,SIGNAL(clicked()),this,SLOT(slotcontinuar()));
    QObject::connect(pause,SIGNAL(clicked()),this,SLOT(slotpause()));
    QObject::connect(comoJugar,SIGNAL(clicked()),this,SLOT(slotpause()));
    QObject::connect(tiempos,SIGNAL(clicked()),this,SLOT(slotpause()));

    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveResults()));


    //Ordenar layout y botones
    //Insertar botones
    botonera->addWidget(nuevo_facil);
    botonera->addWidget(nuevo_medio);
    botonera->addWidget(nuevo_dificil);
    botonera->addSpacing(15);
    botonera->addWidget(resolver);
    botonera->addWidget(terminar);
    botonera->addWidget(cerrar);
    botonera->addWidget(lcd);
    botonera->addSpacing(15);
    botonera->addWidget(this->msgSaved);
    botonera->addWidget(this->msgInputName);
    botonera->addWidget(inputName);
    botonera->addWidget(this->save);
    botonera->addItem(espacioVertical);
    botonera->addWidget(this->tiempos);
    botonera->addWidget(comoJugar);
    botonera->addWidget(pause);
    botonera->addWidget(continuar);
    this->msgSaved->hide();
    terminar->hide();
    continuar->hide();
    resolver->hide();
    lcd->hide();
    inputName->hide();
    this->msgInputName->hide();
    this->save->hide();

    //Insertar botonera
    layoutPrincipal->addLayout(botonera);
    layoutPrincipal->addItem(espacioHorizontal);
    layoutPrincipal->addWidget(qtbrowser);
    layoutPrincipal->addWidget(this->finalMsg);
    layoutPrincipal->addWidget(Highfacil);
    layoutPrincipal->addWidget(Highmedio);
    layoutPrincipal->addWidget(Highdificil);
    Highfacil->hide();
    Highmedio->hide();
    Highdificil->hide();
    qtbrowser->hide();
    this->finalMsg->hide();

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

//SLOT terminado
void VentanaPrincipal::JuegoTerminado()
{
    int dificultad = this->controlador->getLevel();

    this->pause->hide();
    this->continuar->hide();
    this->comoJugar->hide();
    this->terminar->hide();
    this->tiempos->hide();
    //this->resolver->hide();

    this->timer->stop();
    this->totalSeconds = this->seconds;

    this->finalMsg->setMinimumSize(this->principal->width()-200,this->principal->height()-100);
    this->finalMsg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //this->finalMsg->setTextFormat();

    //Comprobar Resultado:
    switch (this->controlador->comprobarSolucion())
    {
        case EXITO: //La solución proporcionada es buena
          qDebug() << "Toma ya! he ganado! en " << this->totalSeconds << "segundos";
          this->resolver->hide(); //No nos interesa resolver si hemos ganado
          //Ocultar fichas:
          for(int fila=0;fila<dificultad;fila++)
              for(int columna=0;columna<dificultad;columna++)
                this->fichas[fila][columna]->hide();
          //Mostar Mensaje final:
          this->finalMsg->setText("<h1><font color='Blue'>ENHORABUENA!<br>HAS GANADO!</color></h1>");
          this->finalMsg->show();

          this->msgInputName->setText("Introduce tu nombre");
          this->msgInputName->show();
          this->inputName->show();
          this->save->show();
        break;
        case ERROR: //La solución proporcionada es mala
          qDebug() << "Mierda! he perdido! en " << this->totalSeconds << "segundos";
          //Ocultar fichas:
          for(int fila=0;fila<dificultad;fila++)
              for(int columna=0;columna<dificultad;columna++)
                this->fichas[fila][columna]->hide();
          //Mostar Mensaje final:
          this->finalMsg->setText("<h1><font color='Red'>LO SIENTO!<br>HAS PERDIDO!</color></h1>");
          this->finalMsg->show();
        break;
    }

}

//SLOT mostrar ayuda
void VentanaPrincipal::MostrarAyuda()
{
    QLocale spanish(QLocale::Spanish, QLocale::Spain);
    int dificultad = controlador->getLevel();
    int fila, columna;
    static QString html;
    static QTextDocument *doc = new QTextDocument;
    html = QString::fromUtf8(this->controlador->pulsarAyuda().c_str());
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
        comoJugar->show();
        continuar->hide();
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
        comoJugar->hide();
        this->tiempos->hide();
        continuar->show();
    }
}

//SLOT cambiar valor
void VentanaPrincipal::CambiarValor(int valor,int fila,int columna)
{
    controlador->setValorUser(valor,fila,columna);
}

//Funcion Nuevo Juego 1(facil) 2(medio) 3(dificil)
void VentanaPrincipal::NuevoJuego(int level)
{
    this->showNormal();
    this->espacioHorizontal->changeSize(0,0);
    this->finalMsg->hide();
    this->qtbrowser->hide();
    this->Highfacil->hide();
    this->Highmedio->hide();
    this->Highdificil->hide();
    this->comoJugar->show();
    this->tiempos->show();
    this->msgInputName->hide();
    this->inputName->hide();
    this->msgSaved->hide();
    this->save->hide();

    this->isayuda = false;
    this->istiempos = false;

    int tam_anterior = controlador->getLevel();

    switch(level)
    {
        case 1:
            controlador->setLevel(5);
            break;
        case 2:
            controlador->setLevel(6);
            break;
        case 3:
            controlador->setLevel(7);
            break;
    }

    this->controlador->pulsarNuevo();
    this->seconds = 0;
    this->lcd->show();
    this->timer->start(1000);
    //Se borra tablero
    BorrarFichas(tam_anterior);
    //se inicia tablero
    ColocarFichas();
}

//metodo borrar fichas
void VentanaPrincipal::BorrarFichas(int tam)
{
    //int tam = grid->columnCount(); //Cuento las columnas, col == filas
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
    int dificultad = controlador->getLevel();
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
                && this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaAbajo()!= 0)
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
            sprintf(cadena, "    %d",this->controlador->juego.partida.tablero->fichas[fila][columna].getSumaDer());
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
    int dificultad = controlador->getLevel();

    this->finalMsg->hide(); //Ocultar mensaje final si es el caso de ver solución después de fallar
    this->resolver->hide(); //No se puede volver a resolver (solo volver a jugar nueva partida)
    this->lcd->hide(); //Tampoco interesa mostrar ya el timepo
    this->terminar->hide();  //Ya no nos interesa terminar, por que hemos visto el resultado
    this->comoJugar->hide(); //Ni ver las reglas
    this->pause->hide(); //Ni pausar el juego
    this->tiempos->hide(); //Ni los tiempos

    for(int fila=0;fila<dificultad;fila++)
        for(int columna=0;columna<dificultad;columna++)
        {
            this->fichas[fila][columna]->show(); //Volver a mostrar por si se ejecutó después de mostrar mensaje final
            if(!this->controlador->juego.partida.tablero->fichas[fila][columna].getBloqueada())/*Aqui hay que comprobar el valor */
            {
                fichas[fila][columna]->setValue(this->controlador->juego.partida.tablero->fichas[fila][columna].getValor());

            }
        }

}
//SLOt pausa y continuar
void VentanaPrincipal::slotpause()
{
    //Parar temporizador
    this->timer->stop();
    this->espacioHorizontal->changeSize(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
}
void VentanaPrincipal::slotcontinuar()
{
    //continuar temporizador
    this->qtbrowser->hide();
    this->Highfacil->hide();
    this->Highmedio->hide();
    this->Highdificil->hide();
    this->showNormal();
    this->espacioHorizontal->changeSize(0,0);
    // !!!!!!!!! AQUÍ EL HIDE DEL NUEVO WIDGET DE TIEMPOS !!!!!!!!!
    this->isayuda = false;
    this->istiempos = false;
    this->timer->start(1000);
}

//SLot nuevo juegos facil,medio,dificil
void VentanaPrincipal::NuevoJuegoFacil()
{
    NuevoJuego(1);
}
void VentanaPrincipal::NuevoJuegoMedio()
{
    NuevoJuego(2);
}
void VentanaPrincipal::NuevoJuegoDificil()
{
    NuevoJuego(3);
}

void VentanaPrincipal::showTime(void)
{
    QTime newTime;
    seconds++;
    newTime = time->addSecs(this->seconds);

    QString text = newTime.toString("hh:mm:ss");
    lcd->display(text);
}

void VentanaPrincipal::saveResults(void)
{
    qDebug() << "Voy a guardar --> Nombre: " << this->inputName->text() << " Nivel: " << this->controlador->juego.partida.getLevel() << " en  " << this->seconds << " segundos." << endl;

    //QString qsname =this->inputName->text();

    this->controlador->juego.tiempos->setName(this->inputName->text().toLatin1().constData());
    this->controlador->juego.tiempos->setLevel(this->controlador->juego.partida.getLevel());
    this->controlador->juego.tiempos->setTime(this->seconds);
    qDebug() << "Nombre: " << this->controlador->juego.tiempos->getName();
    this->controlador->juego.tiempos->saveScores();
    this->msgInputName->hide();
    this->inputName->hide();
    this->save->hide();
    this->msgSaved->setText("<font color='green'>Guardado</font>");
    this->msgSaved->show();

    //this->tiempos->show(); <-- Sería bonito, pero da problemas dificiles de resolver en corto plazo (sin rediseñar)
}

void VentanaPrincipal::MostrarTiempos(void)
{
    int dificultad = controlador->getLevel();
    int fila, columna;

    QTime tiempo;

    //reg_tiempos es la lista con los tiempos ordenados por segundos de juego
    //ATENCIÓN funciona bien! Solo que cambié el formato de archivo (por lo que no te funcionará con un archivo anterior)
    list<Registro> reg_tiempos = this->controlador->juego.tiempos->loadScores();
    list<Registro>::iterator elemento;
    qDebug() << "devueltos numero de elemenos: " << reg_tiempos.size();
    /*
     REGISTRO:
        typedef struct
        {
            char nombre[MAX_NAME];
            int time;
            int level;
        } Registro;

      PARA RECORRER reg_tiempos:
          for (elemento=reg_tiempos.begin(); elemento != reg_tiempos.end(); ++elemento)
            qDebug() << elemento->nombre; // Por ejemplo
    */
    int contfacil = 0;
    int contmedio = 0;
    int contdificil = 0;
    for (elemento=reg_tiempos.begin(); elemento != reg_tiempos.end(); ++elemento)
     {
        tiempo.setHMS(0,0,0,0);
        tiempo = tiempo.addSecs(elemento->time);
        qDebug() << "segundos --> " << elemento->time << " || en horas --> " << tiempo.toString("hh:mm:ss");
        switch(elemento->level)
         {
                case 5:
                    Modelfacil->setItem(contfacil, 0, new QStandardItem(QString::fromUtf8(elemento->nombre)));
                    Modelfacil->setItem(contfacil, 1, new QStandardItem(tiempo.toString("hh:mm:ss")));
                    contfacil++;
                    break;
                case 6:
                    Modelmedio->setItem(contmedio, 0, new QStandardItem(QString::fromUtf8(elemento->nombre)));
                    Modelmedio->setItem(contmedio, 1, new QStandardItem(tiempo.toString("hh:mm:ss")));
                    contmedio++;
                    break;
                case 7:
                    Modeldificil->setItem(contdificil, 0, new QStandardItem(QString::fromUtf8(elemento->nombre)));
                    Modeldificil->setItem(contdificil, 1, new QStandardItem(tiempo.toString("hh:mm:ss")));
                    contdificil++;
                    break;
        }
    }

    // !!!!!!!!!AQUÍ habra que formar el nuevo widget que contenga los datos de ref_tiempos!!!!!!!!

    //Al pulsar en tiempos
    if (this->istiempos) //Los tiempos ya en pantalla
    {
        //Esconder tiempos:
        Highfacil->hide();
        Highmedio->hide();
        Highdificil->hide();
        //!!!!!!!!!!!!!!AQUÍ IRA EL HIDE DEL NUEVO WIDGET!!!!!!!!!!
        //Mostrar Fichas
        for(fila=0;fila<dificultad;fila++)
            for(columna=0;columna<dificultad;columna++)
              this->fichas[fila][columna]->show();

        this->istiempos = false;
        pause->show();
        this->tiempos->show();
        continuar->hide();
    }
    else //No están los tiempos en pantalla
    {
        this->hide();
        //Esconder Fichas
        for(fila=0;fila<dificultad;fila++)
            for(columna=0;columna<dificultad;columna++)
              this->fichas[fila][columna]->hide();
        this->showMaximized();
        //Mostrar ayuda:
        Highfacil->show();
        Highmedio->show();
        Highdificil->show();
        //!!!!!!!!!!!!!AQUÍ IRÁ EL SHOW DEL NUEVO WIDGET!!!!!!!!!!!!!!!!

        this->istiempos = true;
        this->comoJugar->hide();
        pause->hide();
        tiempos->hide();
        continuar->show();
    }
}
