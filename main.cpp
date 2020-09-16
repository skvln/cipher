#include <QApplication>
#include <QWidget>
#include "quitbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QuitButton window;

    window.resize(800, 600);
    window.setWindowTitle("Шифровщик");
    window.show();

    return a.exec();
}
