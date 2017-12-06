#ifndef PINKOD_H
#define PINKOD_H
#include <QMainWindow>
#include "form.h"
#include <QTimer>
#include <QTime>
namespace Ui {
class pinkod;
}
class pinkod : public QMainWindow
{
    Q_OBJECT
public:
    explicit pinkod(QWidget *parent = 0);
    ~pinkod();
signals:
    void PinWindow();
private slots:
    void on_pushButt_clicked();
    void slotTimerAlarm();
    void slotTimerAlarm2();
private:
    Ui::pinkod *ui;
    form* f;
    QTimer *timer;
    QTimer *timer2;
    int time_x;
    int time_x2;
    int a[10000];
    int j;
};
#endif // PINKOD_H
