#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <chartable.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<CharTable> table;

    QList<QString> list({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y" ,"Z"});

    QString word = "DOKUMENTAR";//выбор из файла
    QByteArray ba;
    ba = word.toUtf8();

    for(auto item : ba)
    {
        int currentIndex = list.indexOf(QString(item));
        for(int findIndex = currentIndex - 1; findIndex >= 0; findIndex--)
        {
            if(ba.indexOf(list.at(findIndex)) == -1)
            {
                currentIndex--;
            }
        }
        if(currentIndex == 9)
        {
            table.append(CharTable(QString(item), 0, list.indexOf(QString(ba.at(0))) + 1));
            continue;
        }
        table.append(CharTable(QString(item), currentIndex+1, list.indexOf(QString(ba.at(0))) + 1));
    }

    for(auto item: list)
    {
        auto itObj = std::find_if(table.begin(), table.end(),[item](CharTable o) { return o.chr == item; });
        if (itObj == table.end())
        {

            if(table.length() % 10 == 0)
            {
                table.append(CharTable(QString(item), table[table.length() % 10].pos_up, (list.indexOf(table[(table.length()/10 - 1) * 10].chr) + list.indexOf(item) + 2 >= 10) ? (list.indexOf(table[(table.length()/10 - 1) * 10].chr) + list.indexOf(item) + 2 ) % 10 : (list.indexOf(table[(table.length()/10 - 1) * 10].chr) + list.indexOf(item) + 2 )));
                continue;
            }
            table.append(CharTable(QString(item), table[table.length() % 10].pos_up, (list.indexOf(table[(table.length()/10 - 1) * 10].chr) + list.indexOf(table[table.length()/10 * 10].chr) + 2 >= 10) ? (list.indexOf(table[(table.length()/10 - 1) * 10].chr) + list.indexOf(table[table.length()/10 * 10].chr) + 2) % 10 : (list.indexOf(table[(table.length()/10 - 1) * 10].chr) + list.indexOf(table[table.length()/10 * 10].chr) + 2)));
        }
    }




    //вывод всей таблицы символов с индексами
    for(int i = 0; i < table.count(); i++)
    {
        qDebug() << table[i].chr << " " << table[i].pos_up << table[i].pos_down;

    }


    //индекс по букве
    auto itObj = std::find_if(table.begin(), table.end(),[](CharTable o) { return o.chr == "U"; });
    if (itObj != table.end())
    {
        //qDebug() << itObj->pos_up;
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

