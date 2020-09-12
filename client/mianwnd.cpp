#include "mianwnd.h"
#include "ui_mianwnd.h"

mianwnd::mianwnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mianwnd)
{
    ui->setupUi(this);
}

mianwnd::~mianwnd()
{
    delete ui;
}
