#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <chartable.h>
#include <QTextCodec>
#include <QString>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setlocale(LC_ALL,"Russia");

    QList<QString> listEngl({"A", "a", "B", "b", "C", "c", "D", "d", "E", "e", "F", "f", "G", "g", "H", "h",
                         "I", "i", "J", "j", "K", "k", "L", "l", "M", "m", "N", "n", "O", "o", "P", "p",
                         "Q", "q", "R", "r", "S", "s", "T", "t", "U", "u", "V", "v", "W", "w", "X", "x", "Y", "y","Z", "z"});

    QList<QString> listRus({"А", "а", "Б", "б", "В", "в", "Г", "г", "Д", "д", "Е", "е", "Ё", "ё", "Ж", "ж",
                         "З", "з", "И", "и", "Й", "й", "К", "к", "Л", "л", "М", "м", "Н", "н", "О", "о",
                         "П", "п", "Р", "р", "С", "с", "Т", "т", "У", "у", "Ф", "ф", "Х", "х", "Ц", "ц", "Ч",
                         "ч","Ш", "ш", "Щ", "щ", "ъ", "ы", "ь", "Э", "э", "Ю", "ю", "Я", "я"});

     QList<QString> listSP({"\"", ":", " ", "{", "}", ",", ".", "@"});


    QList<QString> list;
    for(int i = 0; i < listRus.length(); i++)
    {
        if(!(i >= listEngl.length()))
        {
            list.append(listEngl.at(i));
        }

        list.append(listRus.at(i));

        if(!(i >= listSP.length()))
        {
            list.append(listSP.at(i));
        }
    }

    QList<CharTable> table = this->generateAlp(list, "abcеёжghijklmnoprstu");

    QString toCode = "ГитлерSTANdarteвWarшава";//выбор из файла
    QList<int> first = this->firstEncode(toCode, table);

    QString phrase = "DOKUMENTARFILMESINDBELEGTWERDENABERRASCHWIEDERFREI";//выбор из файла
    QList<int> phraseEncoded = this->phraseEncode(table, phrase);

    QList<int> finalEncoded = this->secondEncode(first, phraseEncoded);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//генерация алфавита
QList<CharTable> MainWindow::generateAlp(QList<QString> list, QString key)
{
    QList<CharTable> table;

    QList<QString> l;
    for(int i = 0; i < key.length(); i++)
    {
        l.append(key.mid(i,1));
    }

    //первая строка алфавита
    for(auto item : l)
    {
        int currentIndex = list.indexOf(QString(item));
        for(int findIndex = currentIndex - 1; findIndex >= 0; findIndex--)
        {
            if(l.indexOf(list.at(findIndex)) == -1)
            {
                currentIndex--;
            }
        }
        if(currentIndex == 19)
        {
            table.append(CharTable(QString(item), 0, (list.indexOf(QString(l.at(0))) + 1) >= 10 ? (list.indexOf(QString(l.at(0))) + 1) % 10 : list.indexOf(QString(l.at(0))) + 1));
            continue;
        }
        table.append(CharTable(QString(item), currentIndex+1, (list.indexOf(QString(l.at(0))) + 1) >= 10 ? (list.indexOf(QString(l.at(0))) + 1) % 10 : list.indexOf(QString(l.at(0))) + 1));
    }

    //заполнение всего алфавита
    for(auto item: list)
    {
        auto itObj = std::find_if(table.begin(), table.end(),[item](CharTable o) { return o.chr == item; });
        if (itObj == table.end())
        {


            if(table.length() % 20 == 0)
            {
                int posDown = list.indexOf(table[(table.length()/20 - 1) * 20].chr)/10 + list.indexOf(item)%10 + 2;
                table.append(CharTable(QString(item), table[table.length() % 20].pos_up, posDown));
                continue;
            }

            int posDown = list.indexOf(table[(table.length()/20 - 1) * 20].chr)/10 + list.indexOf(table[table.length()/20 * 20].chr)%10 + 2;
            table.append(CharTable(QString(item), table[table.length() % 20].pos_up, posDown));
        }
    }
    //вывод всей таблицы символов с индексами
    for(int i = 0; i < table.count(); i++)
    {
        qDebug() << table[i].chr << " " << table[i].pos_up << table[i].pos_down;

    }

    return table;
}


//первое наложение
QList<int> MainWindow::firstEncode(QString toCode, QList<CharTable> table)
{
    QList<QString> l;
    for(int i = 0; i < toCode.length(); i++)
    {
        l.append(toCode.mid(i,1));
    }

    QList<int> exitBa;

    for(auto item: l)
    {
        auto itObj = std::find_if(table.begin(), table.end(),[item](CharTable o) { return o.chr == QString(item); });
        if (itObj != table.end())
        {
            if(itObj->pos_up >= 10)
            {
                exitBa.append(itObj->pos_up / 10);
                exitBa.append(itObj->pos_up % 10);
            }
            else
            {
                exitBa.append(0);
                exitBa.append(itObj->pos_up);
            }

            if(itObj->pos_down >= 10)
            {
                exitBa.append(itObj->pos_down / 10);
                exitBa.append(itObj->pos_down % 10);
            }
            else
            {
                exitBa.append(0);
                exitBa.append(itObj->pos_down);
            }
        }

    }
    qDebug() << exitBa << "исходное сообщение";
    return exitBa;
}


//перевод кодовой фразы в цифры
QList<int> MainWindow::phraseEncode(QList<CharTable> table, QString phrase)
{

    QList<QString> phrasedBa;
    for(int i = 0; i < phrase.length(); i++)
    {
        phrasedBa.append(phrase.mid(i,1));
    }

    QList<int> exitPhrase;

    for(auto item: phrasedBa)
    {
        auto itObj = std::find_if(table.begin(), table.end(),[item](CharTable o) { return o.chr == QString(item); });
        if (itObj != table.end())
        {
            if(itObj->pos_up >= 10)
            {
                exitPhrase.append(itObj->pos_up / 10);
                exitPhrase.append(itObj->pos_up % 10);
            }
            else
            {
                exitPhrase.append(0);
                exitPhrase.append(itObj->pos_up);
            }
        }
    }
    qDebug() << exitPhrase << "кодовая фраза";
    return exitPhrase;
}

//второе наложение
QList<int> MainWindow::secondEncode(QList<int> first, QList<int> phraseEncoded)
{
        QList<int> finalCode;
        int count = 0;

        for(auto item: first)
        {
            if(count == phraseEncoded.length())
            {
                count = 0;
            }
            finalCode.append((item + phraseEncoded.at(count)) % 10);
            count++;

        }
        qDebug() << finalCode << "результат шифра";
        return finalCode;
}

