#include "tienda.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     QLocale location;
     QString text = location.languageToString(location.language());
     /*QTranslator traduccion;
     if (QLocale::system().language() == QLocale::English){
         traduccion.load(":/tienda_japones.qm");
         traduccion.load(":/tienda_portuges.qm");
         a.installTranslator(&traduccion);
     }*/

    // Objeto para manejar las traducciones
        QTranslator traducion;

        // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
        if (text == "Japones"){
            traducion.load(":/tienda_japones.qm");
        }else if (text == "Portuges"){
            traducion.load(":/tienda_portuges.qm");
        }
        // Si es diferente de español, se instala la traducción en TODA la aplicación
        if (text != "Español"){
            a.installTranslator(&traducion);
        }
    Tienda w;
    w.show();
    return a.exec();
}
