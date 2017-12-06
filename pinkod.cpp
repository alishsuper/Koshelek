#include "pinkod.h"
#include "ui_pinkod.h"
#include <QDebug>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include <QDateTime>
pinkod::pinkod(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pinkod)
{
    ui->setupUi(this);
    time_x=61;
    time_x2=0;
    j=0;
    // Инициализируем окно
    f = new form();
    connect(f, &form::FormWindow, this, &pinkod::show);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000); // И запустим таймер

    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(slotTimerAlarm2()));

    qsrand (QDateTime::currentMSecsSinceEpoch());
    for (int i=0; i<10000; i++) {
        a[i] = qrand() % 180;
    }
}
pinkod::~pinkod()
{
    delete ui;
}
void pinkod::on_pushButt_clicked()
{
    timer2->start(1000); // И запустим таймер
    time_x=0;
    QString password;
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::database("QSQLITE");
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT password FROM koshelek");
    if (query.next()){
        password = query.value(0).toString();
    }
    if (ui->lineEdit->text()==password){
        f->show();
        this->close();
        ui->lineEdit->setText("");
    } else {
        ui->label_2->setText("Неверный пароль");
    }
}
void pinkod::slotTimerAlarm()
{
    if (f->getFlagForm()==1){
        time_x=0;
        f->setFlagForm(0);
    }
    if (f->getFlagForm()==2){
        time_x=0;
        f->setFlagForm(0);
    }
    time_x++;
    if (time_x==60){
        this->show();  // Показываем окно
        f->close();    // Закрываем основное окно
    }
}
void pinkod::slotTimerAlarm2()
{
    time_x2++;
    if (time_x2==a[j] && (f->getFlagForm()!=2)){
        QString datetime;
        QDateTime startDate=QDateTime::currentDateTime();
        datetime = startDate.toString("yyyy.MM.dd HH:mm:ss");

        int randInt = qrand() % 10000;
        QString random=QString::number(randInt);
        //Подключаем базу данных
        QSqlDatabase db;
        db = QSqlDatabase::database("QSQLITE");
        QSqlQuery query;
        //Осуществляем запрос
        if (!query.prepare("INSERT INTO indata (indate, inkol) VALUES (?, ?)")){
            qDebug() << "Prepare:" << query.lastError();
        }
        query.addBindValue(datetime);
        query.addBindValue(random);
        query.exec();
        j++;
        if (j==10000){j=0;}
        time_x2=0;
    }
}
