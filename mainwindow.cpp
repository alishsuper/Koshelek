#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include <QDebug>
#include <string.h>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "crypter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag=0;
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    p = new pinkod();
    connect(p, &pinkod::PinWindow, this, &MainWindow::show);

    QString random="";
    QString identificator="";
    int randInt=0;
    qsrand (QDateTime::currentMSecsSinceEpoch());
    for (int i=0; i<32; i++) {
        randInt = qrand() % 10;
        random=QString::number(randInt);
        identificator=identificator+random;
    }
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");
    QSqlQuery query;
    bool ok;
    ui->lineEdit->text().toInt(&ok);
    if (ui->lineEdit->text()==ui->lineEdit_2->text() && ok) {
        if (!query.prepare("INSERT INTO koshelek (identificator, password) VALUES (?, ?)")){
            qDebug() << "Prepare:" << query.lastError();
        }
        query.addBindValue(crypter::cryptString(identificator));
        query.addBindValue(ui->lineEdit->text());
        query.exec();
        p->show();  // Показываем окно
        this->close();    // Закрываем основное окно
    } else {
        ui->label_3->setText("Несовпадение паролей либо введена буква");
    }
}
//import
void MainWindow::on_pushButton_2_clicked()
{
    p = new pinkod();
    connect(p, &pinkod::PinWindow, this, &MainWindow::show);

    QString identificator;
    QString password;
    QString indate;
    QString inkol;
    QString outdate;
    QString outkol;
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");

    QFile file;
    QString fileName=QFileDialog::getOpenFileName(this,tr("OpenFile"),"",tr("Text Files (*.txt)"));
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly)){
       qDebug() << "File don't open!";
    }
    identificator = file.readLine();
    identificator.remove("\n");
    password = file.readLine();
    password.remove("\n");
    QSqlQuery query;
    if (!query.prepare("INSERT INTO koshelek (identificator, password) VALUES (?, ?)")){
        qDebug() << "Prepare:" << query.lastError();
    }
    query.addBindValue(identificator);
    query.addBindValue(password);
    query.exec();

    indate = file.readLine();
    indate.remove("\n");
    while (indate!="------"){
        inkol = file.readLine();
        inkol.remove("\n");
        if (!query.prepare("INSERT INTO indata (indate, inkol) VALUES (?, ?)")){
            qDebug() << "Prepare:" << query.lastError();
        }
        query.addBindValue(indate);
        query.addBindValue(inkol);
        query.exec();

        indate = file.readLine();
        indate.remove("\n");
    }

    outdate = file.readLine();
    outdate.remove("\n");
    while (outdate!="------"){
        outkol = file.readLine();
        outkol.remove("\n");
        if (!query.prepare("INSERT INTO out (outdate, outkol) VALUES (?, ?)")){
            qDebug() << "Prepare:" << query.lastError();
        }
        query.addBindValue(outdate);
        query.addBindValue(outkol);
        query.exec();

        outdate = file.readLine();
        outdate.remove("\n");
    }
    identificator = "";
    QSqlQuery query2;
    query2.exec("SELECT identificator FROM koshelek");
    //Выводим значения из запроса
    if (query2.next()){
        identificator = query2.value(0).toString();
    }
    if (crypter::decryptString(identificator).length()==32) {
        p->show();  // Показываем окно
        this->close();    // Закрываем основное окно
    }
}
