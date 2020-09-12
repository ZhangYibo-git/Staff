#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>

#include "ui_mainwnd.h"

namespace Ui {
class mainwnd;
}


class mainwnd : public QWidget
{
    Q_OBJECT

public:
    explicit mainwnd(QWidget *parent = nullptr);
    ~mainwnd();
    void init();

//private:
    Ui::mainwnd *ui;

signals:
    void mainclose();
    void mainlogout();

private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWND_H
