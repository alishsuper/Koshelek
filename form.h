#ifndef FORM_H
#define FORM_H
#include <QMainWindow>
#include <QTimer>
#include <QTime>
namespace Ui {
class form;
}
class form : public QMainWindow
{
    Q_OBJECT
public:
    explicit form(QWidget *parent = 0);
    int getFlagForm() const {
       return flag;
    }
    void setFlagForm(int val){
       flag=val;
    }
    ~form();
signals:
    void FormWindow();
private slots:
    void on_pushButton_clicked();
    void on_tabWidget_tabBarClicked();
    void on_lineEdit_cursorPositionChanged();
    void on_lineEdit_2_cursorPositionChanged();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::form *ui;
    int flag;
};
#endif // FORM_H
