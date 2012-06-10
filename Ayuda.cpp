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
                    "<title> Kakuro </title>"
                    "</head>"
                    "<body>"
                    "<h1 style=\"color: Black;\">Juego de Kakuro</h1>"
                    "<h2 style=\"color: Blue;\">Reglas BAsicas</h2>"
                    "<br><br>"
                    "<li style=\"color: black\">Lorem ipsum xD bla bla bla bla</li>"
                    "</body>"
                    "</html>";
}

QString Ayuda::getAyudaHtml()
{
    this->setAyuda("None");
    return this->helpTXT;
}

