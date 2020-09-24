#include "cipher.h"

Cipher::Cipher(QWidget *parent) : QWidget(parent)
{
    // Создание объекта сетки для разметки
    QGridLayout* grid = new QGridLayout(this);

    // Создание объекта для вертикального размещения нескольких виджетов
    QVBoxLayout* action_btns = new QVBoxLayout(this);

    // Сохранение указателя на поле в атрибут класса
    input_field_ = new QTextEdit(this);
    output_field_ = new QTextEdit(this);

    // Запрет на редактирование поля вывода
    output_field_->setReadOnly(true);

    // Создание кнопок интерфейса
    QPushButton* quit_btn = new QPushButton("Quit", this);
    QPushButton* encrypt_btn = new QPushButton("Encrypt", this);
    QPushButton* decrypt_btn = new QPushButton("Decrypt", this);
    QPushButton* read_from_file_btn = new QPushButton("Read from file", this);
    QPushButton* write_to_file_btn = new QPushButton("Write to file", this);

    // Привязка сценариев (слотов) к событиям на кнопках
    connect(quit_btn, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(encrypt_btn, &QPushButton::clicked, this, &Cipher::ClickOnEncryptBtn);
    connect(decrypt_btn, &QPushButton::clicked, this, &Cipher::ClickOnDecryptBtn);
    connect(read_from_file_btn, &QPushButton::clicked, this, &Cipher::ClickOnReadBtn);
    connect(write_to_file_btn, &QPushButton::clicked, this, &Cipher::ClickOnWriteBtn);

    // Разметка вертикального блока с кнопками
    action_btns->addSpacing(1);
    action_btns->addStretch(1);
    action_btns->addWidget(encrypt_btn);
    action_btns->addWidget(decrypt_btn);
    action_btns->addWidget(read_from_file_btn);
    action_btns->addWidget(write_to_file_btn);
    action_btns->addStretch(1);

    // Выравнивание текстового блока и кнопок в вертикальном блоке
    input_field_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    action_btns->setAlignment(Qt::AlignRight);

    // Размещение объектов на сетке
    grid->addWidget(input_field_, 0, 0);
    grid->addWidget(output_field_, 0, 1);
    grid->addLayout(action_btns, 0, 2);
    grid->addWidget(key_label_, 1, 0);
    // grid->addWidget(key_line_, 2, 0);
    grid->addWidget(quit_btn, 2, 2, Qt::AlignRight);
}

// Обработка нажатия на кнопку "Encrypt"
void Cipher::ClickOnEncryptBtn()
{
    QString text = input_field_->toPlainText();

    if (text.size() % 2 == 1)
    {
        text.append(" ");
    }

    DivideByBlocks(text);
    Encrypt();

    output_field_->setText(UniteFromBlocks());
}

// Обработка нажатия на кнопку "Decrypt"
void Cipher::ClickOnDecryptBtn()
{
    QString text = input_field_->toPlainText();

    DivideByBlocks(text);
    Decrypt();

    output_field_->setText(UniteFromBlocks());
}

// Обработка нажатия на кнопку "Read from file"
void Cipher::ClickOnReadBtn()
{
    QString file_path = QFileDialog::getOpenFileName(nullptr, "Choose file", "", "*.txt");
    QFile file(file_path);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox* msg_box = new QMessageBox;
        msg_box->setText("Wrong format of document or it cannot be opened");
        msg_box->exec();
        return;
    }

    QTextStream in(&file);
    in.setCodec("Windows-1251");
    QString* file_text = new QString;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        *file_text += line + '\n';
    }

    input_field_->setText(*file_text);

    file.close();
}

// Обработка нажатия на кнопку "Write to file"
void Cipher::ClickOnWriteBtn()
{
    QString* text = new QString;
    *text = output_field_->toPlainText();

    QString file_path = QFileDialog::getSaveFileName(nullptr, "Choose file", "", "*.txt");
    QFile file(file_path);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox* msg_box = new QMessageBox;
        msg_box->setText("Smth went wrong...");
        msg_box->exec();
        return;
    }

    QTextStream out(&file);
    out.setCodec("Windows-1251");

    out << *text << Qt::endl;

    file.close();
}

// Разделение сообщения на блоки для шифрования
void Cipher::DivideByBlocks(const QString& text)
{
    text_blocks_->clear();
    for (int i = 1; i < text.size(); i += 2)
    {
        QString block = "";
        block.append(text[i - 1]);
        block.append(text[i]);
        text_blocks_->append(block);
    }
}

// Объединение блоков в единый текст
QString Cipher::UniteFromBlocks()
{
    QString text = "";
    for (const QString& block : *text_blocks_)
    {
        text += block;
    }

    return text;
}

// Шифрование сообщения
void Cipher::Encrypt()
{
    uint first_bit = 0;
    uint second_bit = 3;
    for (uint round = 0; round < ROUNDS; ++round)
    {
        for (QString& block : *text_blocks_)
        {
            std::bitset<QCHAR_BITS> left, right;
            left = block[0].unicode();
            right = block[1].unicode();
            if (right.test(first_bit) != right.test(second_bit))
            {
                right.flip(first_bit);
                right.flip(second_bit);
            }
            block[0] = block[1];
            block[1] = (int)(left ^ right).to_ulong();
        }
        if (round < ROUNDS - 1)
        {
            first_bit = second_bit;
            second_bit = (second_bit + 3) % QCHAR_BITS;
        }
    }
    // --- Написать функцию вычисления бита по ключу ---
    second_bit_ = second_bit;
}

// Дешифрование сообщения
void Cipher::Decrypt()
{
    uint first_bit = (second_bit_ + QCHAR_BITS - 3) % QCHAR_BITS;
    uint second_bit = second_bit_;
    for (uint round = 0; round < ROUNDS; ++round)
    {
        for (QString& block : *text_blocks_)
        {
            std::bitset<QCHAR_BITS> left, right;
            left = block[0].unicode();
            right = block[1].unicode();
            if (left.test(first_bit) != left.test(second_bit))
            {
                left.flip(first_bit);
                left.flip(second_bit);
            }
            block[1] = block[0];
            block[0] = (int)(left ^ right).to_ulong();
        }
        second_bit = first_bit;
        first_bit = (first_bit + QCHAR_BITS - 3) % QCHAR_BITS;
    }
}
