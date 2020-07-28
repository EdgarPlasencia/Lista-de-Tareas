#include "principal.h"

#include <QApplication>
#include <QInputDialog>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    QStringList languages;
    languages<<"Spanish"<<"English"<<"French";

    QString lang=QInputDialog::getItem(NULL,"Idioma","Idioma",languages);

    if(lang=="French"){
        t.load("://french.qm");
    }
    else if(lang=="English"){
        t.load("://examen_plasencia_edgar_en_US.qm");
    }
    if(lang!="Spanish"){
        a.installTranslator(&t);
    }

    Principal w;
    w.show();
    return a.exec();
}
