#include <QApplication>
#include <QWidget>
#include "quitbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QuitButton w;

    w.resize(800, 600);
    w.setWindowTitle("Шифровщик");
    w.show();

    return a.exec();
}
