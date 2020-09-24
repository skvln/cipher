#include <QApplication>
#include <QWidget>
#include "cipher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Cipher window;

    window.setWindowTitle("Cipher");
    window.show();

    return a.exec();
}
