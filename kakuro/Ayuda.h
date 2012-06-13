#ifndef AYUDA_H
#define AYUDA_H

#include <string>

using namespace std;

class Ayuda
{
    string helpTXT;
public:
    Ayuda();
    string getAyuda();
    void setAyuda(string text);
    string getAyudaHtml(void);
};

#endif // AYUDA_H
