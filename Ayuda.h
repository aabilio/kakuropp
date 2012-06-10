#ifndef AYUDA_H
#define AYUDA_H

#include <QTextStream>

class Ayuda
{
    QString helpTXT;
public:
    Ayuda();
    QString getAyuda();
    void setAyuda(QString text);
    QString getAyudaHtml(void);
};

#endif // AYUDA_H
