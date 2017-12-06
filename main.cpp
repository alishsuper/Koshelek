#include "mainwindow.h"
#include "pinkod.h"
#include <QApplication>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QDebug>
#include "QSqlError"
#include <stddef.h>
#include "crypter.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    pinkod p;
    QString identificator;
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\koshelek\\Database.db3");
    if (!db.open()) {
        qDebug() << "Could not open the database connection!";
        qDebug() << "Error:" << db.lastError();
    }
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT identificator FROM koshelek");
    //Выводим значения из запроса
    if (query.next()) {
        identificator = query.value(0).toString();
    }
    if (crypter::decryptString(identificator).length()==32) {
        p.show();
    } else {
        w.show();
    }
    return a.exec();
}
