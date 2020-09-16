#include "quitbutton.h"
#include <QPushButton>
#include <QApplication>

QuitButton::QuitButton(QWidget* parent)
    : QWidget(parent)
{
    QPushButton* quitBtn = new QPushButton("Quit", this);
    quitBtn->setGeometry(700, 550, 75, 25);

    connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
}
