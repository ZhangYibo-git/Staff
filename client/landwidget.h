#ifndef LANDWIDGET_H
#define LANDWIDGET_H

#include <QWidget>

#include "ui_landwidget.h"


namespace Ui { class landWidget; }


class landWidget : public QWidget
{
    Q_OBJECT

public:
    landWidget(QWidget *parent = nullptr);
    ~landWidget();
    void init();

//private:
    Ui::landWidget *ui;
};
#endif // LANDWIDGET_H
