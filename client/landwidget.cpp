#include "landwidget.h"
//#include "ui_landwidget.h"

landWidget::landWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::landWidget)
{
    ui->setupUi(this);
    //设置窗口图标
    setWindowIcon(QPixmap(QString::fromUtf8(":/pic/icon.png")));
    //设置固定窗口大小
    setFixedSize(300,400);
    //设置行输入为密码输入模式
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    ui->label_tip->clear();//清除提示信息
}

//初始化函数
void landWidget::init()
{
    ui->label_tip->clear();//清空提示标签
    ui->lineEdit->clear();//清空行编辑器
    ui->lineEdit_password->clear();//清空行编辑器
    ui->pushButton_2->setEnabled(true);//登陆按钮使能
}

landWidget::~landWidget()
{
    delete ui;
}

