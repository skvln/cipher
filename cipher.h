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
    QTextEdit* input_field_ = new QTextEdit(this);
    QTextEdit* output_field_ = new QTextEdit(this);
    QLabel* key_label_ = new QLabel("Ключ:", this);
    QLineEdit* key_line_ = new QLineEdit(this);
    uint second_bit_;

    // Методы для обработки текста
    QVector<QString>* DivideByBlocks(const QString& text);
    QString UniteFromBlocks(const QVector<QString>& blocks);

    // Вычисление ключа
    uint CalculateKey();

    // Методы для шифрования/дешифрования
    void Encrypt(QVector<QString>& blocks);
    void Decrypt(QVector<QString>& blocks);


signals:

};

#endif // CIPHER_H
