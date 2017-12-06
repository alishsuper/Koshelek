#include "form.h"
#include "ui_form.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
form::form(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::form)
{
    ui->setupUi(this);
    flag = 0;
}
form::~form()
{
    delete ui;
}
//send
void form::on_pushButton_clicked()
{
    QString datetime;
    QDateTime startDate=QDateTime::currentDateTime();
    datetime = startDate.toString("yyyy.MM.dd HH:mm:ss");
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");
    QSqlQuery query;
    //Осуществляем запрос
    if (!query.prepare("INSERT INTO out (outdate, outkol) VALUES (?, ?)")){
        qDebug() << "Prepare:" << query.lastError();
    }
    query.addBindValue(datetime);
    query.addBindValue(ui->lineEdit_2->text());
    query.exec();
    flag=2;
}
void form::on_tabWidget_tabBarClicked()
{
    flag=1;
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    ui->textEdit->insertPlainText("Дата                           Сумма\n");
    ui->textEdit_2->insertPlainText("Дата                           Сумма\n");

    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT indate, inkol FROM indata");
    //Выводим значения из запроса
    while (query.next()) {
        QString indate = query.value(0).toString();
        QString inkol = query.value(1).toString();
        ui->textEdit->insertPlainText(indate+" "+inkol+"\n");
    }
    query.exec("SELECT outdate, outkol FROM out");
    //Выводим значения из запроса
    while (query.next()) {
        QString outdate = query.value(0).toString();
        QString outkol = query.value(1).toString();
        ui->textEdit_2->insertPlainText(outdate+" "+outkol+"\n");
    }
}
void form::on_lineEdit_cursorPositionChanged()
{
    flag=1;
}
void form::on_lineEdit_2_cursorPositionChanged()
{
    flag=1;
}
//update
void form::on_pushButton_2_clicked()
{
    flag=1;
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    ui->textEdit->insertPlainText("Дата                           Сумма\n");
    ui->textEdit_2->insertPlainText("Дата                           Сумма\n");

    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT indate, inkol FROM indata");
    //Выводим значения из запроса
    while (query.next()) {
        QString indate = query.value(0).toString();
        QString inkol = query.value(1).toString();
        ui->textEdit->insertPlainText(indate+" "+inkol+"\n");
    }
    query.exec("SELECT outdate, outkol FROM out");
    //Выводим значения из запроса
    while (query.next()) {
        QString outdate = query.value(0).toString();
        QString outkol = query.value(1).toString();
        ui->textEdit_2->insertPlainText(outdate+" "+outkol+"\n");
    }
}
//export
void form::on_pushButton_3_clicked()
{
    flag=1;
    QString identificator;
    QString password;
    QString indate;
    QString inkol;
    QString outdate;
    QString outkol;
    QFile filekal;
    QTextStream stream(&filekal); // Создаем объект класса QTextStream
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");
    QString dirname = QFileDialog::getExistingDirectory(this, tr("Select a Directory"), QDir::currentPath());
    if( !dirname.isNull()) {
        filekal.setFileName(dirname+"/koshelek.txt");
        if(!filekal.open(QIODevice::Append | QIODevice::Truncate)) {
          qDebug() << "File don't open!";
        }
    }
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT identificator, password FROM koshelek");
    //Выводим значения из запроса
    while (query.next()) {
        identificator = query.value(0).toString();
        password = query.value(1).toString();
    }
    stream <<identificator << endl;
    stream <<password << endl;
    //Осуществляем запрос
    query.exec("SELECT indate, inkol FROM indata");
    //Выводим значения из запроса
    while (query.next()) {
        indate = query.value(0).toString();
        inkol = query.value(1).toString();
        stream <<indate << endl;
        stream <<inkol << endl;
    }
    stream <<"------" << endl;
    //Осуществляем запрос
    query.exec("SELECT outdate, outkol FROM out");
    //Выводим значения из запроса
    while (query.next()) {
        outdate = query.value(0).toString();
        outkol = query.value(1).toString();
        stream <<outdate << endl;
        stream <<outkol << endl;
    }
    stream <<"------" << endl;
}
