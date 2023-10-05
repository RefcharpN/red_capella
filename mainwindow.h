#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chartable.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<CharTable> generateAlp(QList<QString> list, QString key);
    QList<int> firstEncode(QString toCode, QList<CharTable> table);
    QList<int> phraseEncode(QList<CharTable> table, QString phrase);
    QList<int> secondEncode(QList<int> first, QList<int> phraseEncoded);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
