#include <QObject>
#include <QTextStream>
#include <QTextDocument>
#include <QtGui>

#include "VentanaPrincipal.h"
#include "Controlador.h"

VentanaPrincipal::VentanaPrincipal()
{
    //Temporizadores:
    lcd = new QLCDNumber;
    lcd->setNumDigits(8);
    this->seconds = 0;
    time = new QTime;
    time->setHMS(0,0,0,0);
    timer = new QTimer(this);
    //LCD de tiempo:
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

    //Opciones de tablas de Tiempos:
    Modelfacil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Highfacil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Modelmedio->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Highmedio->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Modeldificil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Highdificil->setProperty("editTriggers",QAbstractItemView::NoEditTriggers);
    Modelfacil->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre")));
    Modelfacil->setHorizontalHeaderItem(1, new QStandardItem(QString("Tiempo (f�cil)")));
    Highfacil->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Highfacil->setModel(Modelfacil);
    Modelmedio->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre")));
    Modelmedio->setHorizontalHeaderItem(1, new QStandardItem(QString("Tiempo (medio)")));
    Highmedio->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Highmedio->setModel(Modelmedio);
    Modeldificil->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre")));
    Modeldificil->setHorizontalHeaderItem(1, new QStandardItem(QString("Tiempo (dif�cil)")));
    Highdificil->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Highdificil->setModel(Modeldificil);

    //Botones
    nuevo_facil = new QPushButton(tr("&F�cil"));
    nuevo_facil->setShortcut(tr("f"));
    nuevo_medio = new QPushButton(tr("&Medio"));
    nuevo_medio->setShortcut(tr("m"));
    nuevo_dificil = new QPushButton(tr("&Dif�cil"));
    nuevo_dificil->setShortcut(tr("d"));
    resolver = new QPushButton(tr("&Soluci�n"));
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
    this->isIniciado = false;

    //Tama�o botones
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

    //Conexiones entre botones:
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    QObject::connect(cerrar,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(nuevo_facil,SIGNAL(clicked()),this,SLOT(NuevoJuegoFacil()));
    QObject::connect(nuevo_medio,SIGNAL(clicked()),this,SLOT(NuevoJuegoMedio()));
    QObject::connect(nuevo_dificil,SIGNAL(clicked()),this,SLOT(NuevoJuegoDificil()));
    QObject::connect(resolver,SIGNAL(clicked()),this,SLOT(Resolver()));
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


    //Colocar los botones:
    botonera->addWidget(nuevo_facil);
    botonera->addWidget(nuevo_medio);
    botonera->addWidget(nuevo_dificil);
    botonera->addSpacing(15);
    botonera->addWidget(resolver);
    botonera->addWidget(terminar);
    botonera->addWidget(cerrar);
    botonera->addSpacing(15);
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

    //Cargar el Layout Principal con los Widgets
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

    //Juntado SpinBoxes
    grid->setHorizontalSpacing(0);
    grid->setVerticalSpacing(0);

    //Insertar Grid
    layoutPrincipal->addLayout(grid);

    //Conectar Widget principal
    setCentralWidget(principal);

    this->show();

    //Iniciar primer tablero
    ColocarFichas();
}

//SLOT terminado
void VentanaPrincipal::JuegoTerminado()
{
    int dificultad = this->controlador->juego.getLevel();

    this->isIniciado = false;
    this->pause->hide();
    this->continuar->hide();
    this->comoJugar->hide();
    this->terminar->hide();
    this->tiempos->hide();

    this->timer->stop();
    this->totalSeconds = this->seconds;

    this->finalMsg->setMinimumSize(this->principal->width()-200,this->principal->height()-100);
    this->finalMsg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Comprobar Resultado:
    switch (this->controlador->juego.comprobarSolucion())
    {
        case EXITO: //La soluci�n proporcionada es buena
          this->resolver->hide(); //No nos interesa resolver si hemos ganado
          //Ocultar fichas:
          for(int fila=0;fila<dificultad;fila++)
              for(int columna=0;columna<dificultad;columna++)
                this->fichas[fila][columna]->hide();
          //Mostar Mensaje final:
          this->finalMsg->setText("<center><h1><font color='Green'>ENHORABUENA!<br>HAS GANADO!</color></h1></center>");
          this->finalMsg->show();

          this->msgInputName->setText("Introduce tu nombre");
          this->msgInputName->show();
          this->inputName->show();
          this->save->show();
        break;
        case ERROR: //La soluci�n proporcionada es mala
          //Ocultar fichas:
          for(int fila=0;fila<dificultad;fila++)
              for(int columna=0;columna<dificultad;columna++)
                this->fichas[fila][columna]->hide();
          //Mostar Mensaje final:
          this->finalMsg->setText("<center><h1><font color='Red'>FAIL!<br>HAS PERDIDO!</color></h1></center>");
          this->finalMsg->show();
        break;
    }

}

//SLOT mostrar ayuda
void VentanaPrincipal::MostrarAyuda()
{
    int dificultad = this->controlador->juego.getLevel();
    int fila, columna;
    QLocale spanish(QLocale::Spanish, QLocale::Spain);
    static QString html;
    static QTextDocument *doc = new QTextDocument;
    html = QString::fromUtf8(this->controlador->pulsarAyuda().c_str());
    doc->setHtml(html);
    this->qtbrowser->setDocument(doc);

    //Opciones del contenedor de la ayuda
    this->qtbrowser->setMinimumSize(this->principal->width()-200,this->principal->height()-100);
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
        this->terminar->show();
        this->resolver->show();
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
        this->terminar->hide();
        this->resolver->hide();
        comoJugar->hide();
        this->tiempos->hide();
        continuar->show();
    }
}

//SLOT cambiar valor
void VentanaPrincipal::CambiarValor(int valor,int fila,int columna)
{
    this->controlador->juego.setValorUser(valor, fila, columna);
}

//Funcion Nuevo Juego 1(facil) 2(medio) 3(dificil)
void VentanaPrincipal::NuevoJuego(int level)
{
    this->isIniciado = true;
    this->showNormal();
    this->espacioHorizontal->changeSize(0,0);
    this->finalMsg->hide();
    this->qtbrowser->hide();
    this->Highfacil->hide();
    this->Highmedio->hide();
    this->Highdificil->hide();
    this->comoJugar->show();
    this->terminar->show();
    this->resolver->show();
    this->tiempos->show();
    this->msgInputName->hide();
    this->inputName->hide();
    this->msgSaved->hide();
    this->save->hide();

    this->isayuda = false;
    this->istiempos = false;

    int tam_anterior = this->controlador->juego.getLevel();

    switch(level)
    {
        case 1:
            this->controlador->juego.setLevel(5);
            break;
        case 2:
            this->controlador->juego.setLevel(6);
            break;
        case 3:
            this->controlador->juego.setLevel(7);
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

    int dificultad = this->controlador->juego.getLevel();
    for(fila=0;fila<dificultad;fila++)
        for(columna=0;columna<dificultad;columna++)
        {
            //Instanciar y pintar dependiendo del valor
            fichas[fila][columna] = new FichaVentana(fila,columna);
            PintarFichas(fila,columna);
            //a�adir y conectar fichas
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
    if(!this->controlador->juego.getFichaBloqueada(fila, columna))
    {
        fichas[fila][columna]->setRange(0,9);
        fichas[fila][columna]->setStyleSheet("background-color: rgb(211, 211, 211);");
        fichas[fila][columna]->setFont(noBloqueadas);
        fichas[fila][columna]->clear();
    }else
    {
        char cadena[8];
        fichas[fila][columna]->setRange(0,50);
        fichas[fila][columna]->setStyleSheet("background-color: qconicalgradient(cx:0.493318, cy:0.676, angle:327.6, stop:0.340909 rgba(192, 192, 192, 255), stop:0.346591 rgba(155, 155, 155, 255));");

        if(this->controlador->juego.getFichaSumaDerecha(fila,columna) != 0
                && this->controlador->juego.getFichaSumaAbajo(fila, columna) != 0 )
            #ifdef Q_WS_MAC
              sprintf(cadena, "%d   %d",this->controlador->juego.getFichaSumaAbajo(fila, columna),this->controlador->juego.getFichaSumaDerecha(fila,columna));
            #else // Otros que no mac (windows por ejemplo):
              sprintf(cadena, "%d  %d",this->controlador->juego.getFichaSumaAbajo(fila, columna),this->controlador->juego.getFichaSumaDerecha(fila,columna));
            #endif
        else if(this->controlador->juego.getFichaSumaDerecha(fila,columna) == 0 &&
                this->controlador->juego.getFichaSumaAbajo(fila, columna) != 0)
            #ifdef Q_WS_MAC
              sprintf(cadena, "%d     ",this->controlador->juego.getFichaSumaAbajo(fila, columna));
            #else
              sprintf(cadena, "%d    ",this->controlador->juego.getFichaSumaAbajo(fila, columna));
            #endif
        else if(this->controlador->juego.getFichaSumaAbajo(fila, columna) == 0
                && this->controlador->juego.getFichaSumaDerecha(fila,columna) != 0)
            sprintf(cadena, "    %d",this->controlador->juego.getFichaSumaDerecha(fila,columna));
        else
        {
            sprintf(cadena,"   ");
            fichas[fila][columna]->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0, y1:0.431818, x2:1, y2:0.437273, stop:0 rgba(151, 151, 151, 255), stop:1 rgba(124, 124, 124, 255));");
        }
        fichas[fila][columna]->setSpecialValueText(cadena);
        fichas[fila][columna]->setDisabled(TRUE);
        fichas[fila][columna]->setFont(bloqueadas);
    }
}

void VentanaPrincipal::Resolver()
{
    int dificultad = this->controlador->juego.getLevel();

    this->finalMsg->hide(); //Ocultar mensaje final si es el caso de ver soluci�n despu�s de fallar
    this->resolver->hide(); //No se puede volver a resolver (solo volver a jugar nueva partida)
    this->lcd->hide(); //Tampoco interesa mostrar ya el timepo
    this->terminar->hide();  //Ya no nos interesa terminar, por que hemos visto el resultado
    this->comoJugar->hide(); //Ni ver las reglas
    this->pause->hide(); //Ni pausar el juego
    this->tiempos->hide(); //Ni los tiempos

    for(int fila=0;fila<dificultad;fila++)
        for(int columna=0;columna<dificultad;columna++)
        {
            this->fichas[fila][columna]->show(); //Volver a mostrar por si se ejecut� despu�s de mostrar mensaje final
            if(!this->controlador->juego.getFichaBloqueada(fila,columna))
            {
                fichas[fila][columna]->setValue(this->controlador->juego.getFichaValor(fila, columna));

            }
        }

}

//SLOT pausa y continuar
void VentanaPrincipal::slotpause()
{
    this->terminar->hide();
    this->resolver->hide();
    this->timer->stop();
    this->espacioHorizontal->changeSize(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
}
void VentanaPrincipal::slotcontinuar()
{
    this->qtbrowser->hide();
    this->Highfacil->hide();
    this->Highmedio->hide();
    this->Highdificil->hide();
    this->showNormal();
    this->espacioHorizontal->changeSize(0,0);

    if(isIniciado)
    {
        this->terminar->show();
        this->resolver->show();
    }

    this->isayuda = false;
    this->istiempos = false;
    this->timer->start(1000);
}

//SLOT's nuevo juegos facil,medio,dificil
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
    this->controlador->juego.setTiempoName(this->inputName->text().toLatin1().constData());
    this->controlador->juego.setTiempoLevel(this->controlador->juego.getLevel());
    this->controlador->juego.setTiempoTime(this->seconds);

    this->controlador->juego.saveScores();

    this->msgInputName->hide();
    this->inputName->hide();
    this->save->hide();
    this->msgSaved->setText("<center><font color='green'>Guardado</font></center>");
    this->msgSaved->show();

    this->finalMsg->hide();
    this->MostrarTiempos();
    this->continuar->hide();
}

void VentanaPrincipal::MostrarTiempos(void)
{
    int dificultad = this->controlador->juego.getLevel();
    int fila, columna;

    QTime tiempo;

    list<Registro> reg_tiempos = this->controlador->juego.loadScores();
    list<Registro>::iterator elemento;

    int contfacil = 0;
    int contmedio = 0;
    int contdificil = 0;
    for (elemento=reg_tiempos.begin(); elemento != reg_tiempos.end(); ++elemento)
     {
        tiempo.setHMS(0,0,0,0);
        tiempo = tiempo.addSecs(elemento->time);
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

    //Al pulsar en tiempos
    if (this->istiempos) //Los tiempos ya en pantalla
    {
        //Esconder tiempos:
        Highfacil->hide();
        Highmedio->hide();
        Highdificil->hide();
        //Mostrar Fichas
        for(fila=0;fila<dificultad;fila++)
            for(columna=0;columna<dificultad;columna++)
              this->fichas[fila][columna]->show();

        this->istiempos = false;
        pause->show();
        this->tiempos->show();
        continuar->hide();
    }
    else //No est�n los tiempos en pantalla
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

        this->istiempos = true;
        this->comoJugar->hide();
        pause->hide();
        terminar->hide();
        resolver->hide();
        tiempos->hide();
        continuar->show();
    }
}
