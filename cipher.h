#ifndef CIPHER_H
#define CIPHER_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QVector>
#include <QBitArray>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <bitset>
#include <iostream>

const int ROUNDS = 16;
const int QCHAR_BITS = sizeof(QChar) * 8;

class Cipher : public QWidget
{

    Q_OBJECT

public:
    explicit Cipher(QWidget *parent = nullptr);

private slots:
    void ClickOnEncryptBtn();
    void ClickOnDecryptBtn();
    void ClickOnReadBtn();
    void ClickOnWriteBtn();

private:
    QVector<QString>* text_blocks_ = new QVector<QString>;
    QTextEdit* input_field_;
    QTextEdit* output_field_;
    QLabel* key_label_ = new QLabel("Ключ:", this);
    QLineEdit* key_line_;
    uint second_bit_;

    void Encrypt();
    void Decrypt();
    void DivideByBlocks(const QString& text);
    QString UniteFromBlocks();


signals:

};

#endif // CIPHER_H
