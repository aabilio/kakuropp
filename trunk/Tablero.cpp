#include "Tablero.h"

Tablero::Tablero(int level)
{
    dificultad = level;
    srand(time(NULL));
}

bool Tablero::generarTablero(int level)
{
    this->dificultad = level;
    //Poner todas las fichas a 0;
    reiniciarFichas();
    //Bloquear fila=0 y columna =0
    for(int fila=0; fila<dificultad;fila++)
        fichas[fila][0].setBloqueada(true);
    for(int col=0; col <dificultad; col++)
        fichas[0][col].setBloqueada(true);
    //Bloquear otros elementos
    colocarBloqueadas();
    //Rellenar con tablero
    for(int i=1;i<dificultad;i++)
    {
        for(int j=1;j<dificultad;j++)
        {
            fichas[i][j].setValorUser(0);
            if(!fichas[i][j].getBloqueada())
            {
                if(!colocarValor(i,j))
                {
                    return false;
                }
                //si falla generar nuevo tablero;
            }

        }
    }
    colocarSumas();
    return true;
}
bool Tablero::colocarBloqueadas()
{
    //Generar numero de bloqueadas nuevas
    int numbloqueadas = aleatorio(dificultad,dificultad+dificultad);
    for(int i = numbloqueadas; i>0; i--)
    {
        //Elegir lado y elemento
        int lado,elemento;
        lado = aleatorio(0,3);
        elemento = aleatorio(1,dificultad-1);
        //lado == 0 es la fila=1
        if(lado == 0)
        {
           lado =1;
           while(fichas[lado][elemento].getBloqueada())
                lado++;

           fichas[lado][elemento].setBloqueada(true);
        }
        //lado == 0 es la columana 1
        else if(lado == 1)
        {
            while(fichas[elemento][lado].getBloqueada())
                lado++;

            fichas[elemento][lado].setBloqueada(true);

        }
        //lado ==2 es la ultima fila
        else if(lado == 2)
        {
            lado = dificultad-1;
            while(fichas[lado][elemento].getBloqueada())
                lado--;
            fichas[lado][elemento].setBloqueada(true);
        }
        //Ultima columna
        else
        {
           lado = dificultad-1;
           while(fichas[elemento][lado].getBloqueada())
               lado--;
           fichas[elemento][lado].setBloqueada(true);
        }

    }
    return true;
}

bool Tablero::colocarValor(int filaTope,int colTope)
{
    bool fallo = true;
    int dato;
    //contador de intentos
    int cont = 0;
    //Comentar funcion
    while(fallo)
    {
        if(cont==100)
            return false;

        fallo = false;
        dato = aleatorio(1,9);
        for(int i=colTope-1; fichas[filaTope][i].getBloqueada() == false && fallo == false ; i--)
        {
            if(fichas[filaTope][i].getValor() == dato)
            {
                fallo = true;
            }
        }
        for(int i=filaTope-1; fichas[i][colTope].getBloqueada() == false && fallo == false ; i--)
        {
            if(fichas[i][colTope].getValor() == dato)
            {
                fallo = true;
            }
        }

        cont++;

    }
    fichas[filaTope][colTope].setValor(dato);
    return true;

}
bool Tablero::colocarSumas()
{
    int suma =0;
    for(int i=0; i<dificultad;i++)
        for(int j=dificultad-1;j>=0;j--)
        {
            suma = suma+fichas[i][j].getValor();
            if(fichas[i][j].getBloqueada())
            {
                fichas[i][j].setSumaDer(suma);
                suma=0;
            }

        }
    for(int i=0; i<dificultad;i++)
        for(int j=dificultad-1;j>=0;j--)
        {
            suma = suma+fichas[j][i].getValor();
            if(fichas[j][i].getBloqueada())
            {
                fichas[j][i].setSumaAbajo(suma);
                suma=0;
            }

        }
    return true;

}
void Tablero::reiniciarFichas()
{
    for(int fila=0;fila < this->dificultad; fila++)
        for(int col =0;col< this->dificultad;col++)
        {
            fichas[fila][col].setBloqueada(false);
            fichas[fila][col].setValor(0);
            fichas[fila][col].setSumaDer(0);
            fichas[fila][col].setSumaAbajo(0);
        }
}

bool Tablero::resolverTablero()
{

    int suma = 0;
    int valor;
    for(int i=0; i<dificultad;i++)
    {
        suma=0;
        for(int j=dificultad-1;j>=0;j--)
        {
            suma = suma+fichas[i][j].getValorUser();
            if(fichas[i][j].getBloqueada())
            {
                if(fichas[i][j].getSumaDer() !=suma && fichas[i][j].getSumaDer()!= 0)
                    return false;
                suma=0;
            }

        }
    }
    for(int i=0; i<dificultad;i++)
    {
        suma = 0;
        for(int j=dificultad-1;j>=0;j--)
        {
            suma = suma+fichas[j][i].getValorUser();
            if(fichas[j][i].getBloqueada())
            {
                if(fichas[j][i].getSumaAbajo()!= suma && fichas[i][j].getSumaAbajo()!=0)
                    return false;
                suma=0;
            }

        }
    }
    for(int i=0;i<dificultad;i++)
    {
        for(int j=dificultad-1;j>=0;j--)
        {
            valor = fichas[i][j].getValorUser();
            if(!fichas[i][j].getBloqueada())
            {
                for(int k=j-1;k>=0 && !fichas[i][k].getBloqueada();k--)
                {
                    if(valor == fichas[i][k].getValorUser())
                     return false;

                }
            }
        }
    }

    return true;
}
