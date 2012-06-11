#include <QtGui>
#include <QTextStream>
#include "Ayuda.h"

Ayuda::Ayuda()
{

}

QString Ayuda::getAyuda()
{
  return this->helpTXT;
}

void Ayuda::setAyuda(QString text)
{
    this->helpTXT = "<html>"
                    "<head>"
                    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />"
                    "<title> Kakuro </title>"
                    "</head>"
                    "<body>"
                    "<br><br>"
                    "<h1 align=center style=\"color: Black;\">Juego de Kakuro</h1>"
                    "<h2 align=center style=\"color: Blue;\">Reglas B&aacute;sicas</h2>"
                    "<br><br>"
                    "<p align=justify>Las reglas para resolver un Kakuro son muy sencillas, se trata de rellenar las casillas con n&uacute;meros del <span style=\"color: Red;\">1 al 9</span> , teniendo en cuenta que:</p>"
                    "<ul>"
                    "<li style=\"color: Blue;\">Cada fila o columna debe sumar lo indicado a la izquierda o arriba (respectivamente) de la misma</li>"
                    "<li style=\"color: Blue;\">No se puede repetir un mismo n&uacute;mero en una suma (fila o columna)</li>"
                    "</ul>"
                    "<p>La clave est&aacute; en encontrar aquellos casos en que s&oacute;lo hay una combinaci&oacute;n de n&uacute;meros posibles que encaje. Por ejemplo: dos casillas que sumen 17 han de ser necesariamente un 8 y un 9, tres casillas que sumen 23, han de ser 6, 8 y 9 (en cualquier orden), etc&#8230;</p>"
                    "</body>"
                    "</html>";
}

QString Ayuda::getAyudaHtml()
{
    this->setAyuda("None");
    return this->helpTXT;
}

