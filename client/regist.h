#ifndef REGIST_H
#define REGIST_H

#include <QDebug>
#include <QWidget>

namespace Ui {
class regist;
}

class regist : public QWidget
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();
    void init();
//private:
    Ui::regist *ui;

signals:
    void sigsendmsg();

public slots:
    bool eventFilter(QObject *watched,QEvent *event);    //注意这里
    void on_pushButton_clicked();
};

#endif // REGIST_H
