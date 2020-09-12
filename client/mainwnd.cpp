#include "mainwnd.h"
#include "config.h"

extern staff_t recvmsg;//接收消息结构体

mainwnd::mainwnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwnd)
{
    ui->setupUi(this);
    //设置窗口图标
    setWindowIcon(QPixmap(QString::fromUtf8(":/pic/icon.png")));

    //关联槽函数
}

//初始化函数
void mainwnd::init()
{
    //设置文本输入行 可编辑状态
    ui->lineEdit_17->setDisabled(false);//账号信息
    ui->lineEdit_19->setDisabled(false);//密码信息
    ui->lineEdit_18->setDisabled(false);//姓名
    ui->lineEdit_4->setDisabled(false);//年龄
    ui->lineEdit_5->setDisabled(false);//性别
    ui->lineEdit_7->setDisabled(false);//电话
    ui->lineEdit_8->setDisabled(false);//住址
    ui->lineEdit_6->setDisabled(false);//工资
    //设置按钮操作状态
    ui->pushButton->setDisabled(true);//除能查找信息按钮
    ui->pushButton_3->setDisabled(true);//除能注册新员工按钮
    ui->pushButton_7->setDisabled(true);//除能修改信息按钮
    //设置欢迎信息
    ui->label_name->setText(QString(recvmsg.name).toUtf8());//设置欢迎信息 -名字
    //Root权限设置
    if(recvmsg.permission == ROOT)
    {
        qDebug("ROOT 设置");
        ui->pushButton->setEnabled(true);//使能查找信息按钮
        ui->pushButton_3->setEnabled(true);//使能注册新员工按钮
        ui->pushButton_7->setEnabled(true);//使能修改信息按钮
    }
    //USER权限设置
    if(recvmsg.permission == USER)
    {
        qDebug("USER 设置");
        //设置为文本输入行只能查看（只读）
        ui->lineEdit_17->setDisabled(true);//账号信息
        ui->lineEdit_19->setDisabled(true);//密码信息
        ui->lineEdit_18->setDisabled(true);//姓名
        ui->lineEdit_4->setDisabled(true);//年龄
        ui->lineEdit_5->setDisabled(true);//性别
        ui->lineEdit_7->setDisabled(true);//电话
        ui->lineEdit_8->setDisabled(true);//住址
        ui->lineEdit_6->setDisabled(true);//工资
    }
    ui->stackedWidget->setCurrentIndex(0);//设置stackedWidget界面为显示信息界面

}


//退出
void mainwnd::on_pushButton_5_clicked()
{
    emit mainclose();//发送关闭命令
}

//注销登录
void mainwnd::on_pushButton_8_clicked()
{
    emit mainlogout();//发送注销命令
}

//析构函数
mainwnd::~mainwnd()
{
    delete ui;
}



//查找按钮按下
void mainwnd::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);//设置stackedWidget界面为查找信息界面
}

//员工信息按钮按下
void mainwnd::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//设置stackedWidget界面为员工信息界面
}

//注册新员工按钮按下
void mainwnd::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//设置stackedWidget界面为注册新员工界面
}


