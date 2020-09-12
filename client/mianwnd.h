#ifndef MIANWND_H
#define MIANWND_H

#include <QWidget>

namespace Ui {
class maimwnd;
}

class maimwnd : public QWidget
{
    Q_OBJECT

public:
    explicit maimwnd(QWidget *parent = nullptr);
    ~maimwnd();

private:
    Ui::maimwnd *ui;
};

#endif // MIANWND_H
