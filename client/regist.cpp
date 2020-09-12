#include "regist.h"
#include "ui_regist.h"
#include "config.h"

unsigned int megflags = 0;//信息填充标志位
extern staff_t sendmsg;//发送消息结构体

regist::regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);

    //设置窗口图标
    setWindowIcon(QPixmap(QString::fromUtf8(":/pic/icon.png")));
    //设置固定窗口大小
    setFixedSize(300,400);
    //清空标签信息
    ui->label_password->clear();//密码提示
    ui->label_apassword->clear();//再次输入密码提示
    ui->label_account->clear();//账号提示
    //安装事件过滤器
    ui->lineEdit_password->installEventFilter(this);
    ui->lineEdit_apassword->installEventFilter(this);
    ui->lineEdit_account->installEventFilter(this);
    //设置密码行输入为密码输入模式
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_apassword->setEchoMode(QLineEdit::Password);
}

bool regist::eventFilter(QObject *watched, QEvent *event)
{
    static int passwd_ok = 0;
    if (watched==ui->lineEdit_account)      //首先判断控件(这里指 lineEdit_account)
    {
        if(event->type()==QEvent::FocusOut)    // 这里指 lineEdit_account 控件的失去焦点事件
        {
            if(ui->lineEdit_account->isModified() && !ui->lineEdit_account->text().isEmpty())
            {
                if(ui->lineEdit_account->text().length() == 4)
                {
                    ui->label_account->setText(QString("√"));
                    megflags |= ACCOUNT_OK;//账号填充完成 --标志位置起
                }
                else
                    ui->label_account->setText(QString("请输入四位数的账号"));
            }
            else
                ui->label_account->setText(QString("请输入账号"));
        }
    }
    if (watched==ui->lineEdit_password)           //这里来处理 lineEdit_password , lineEdit_account 是一样的
    {
        if (event->type()==QEvent::FocusOut)
        {
            if(ui->lineEdit_password->isModified() && !ui->lineEdit_password->text().isEmpty())
            {
                passwd_ok = 1;//密码填充完成标志为
                ui->label_password->setText(QString("√"));

            }
            else
            {
                ui->label_password->setText(QString("请输入密码"));
                passwd_ok = 0;//密码填充未完成标志为
            }
        }
    }
    if (watched==ui->lineEdit_apassword)           //与上面同理
    {
        if (event->type()==QEvent::FocusOut)
        {
            if(ui->lineEdit_apassword->isModified() && passwd_ok)
            {
                if(ui->lineEdit_password->text() == ui->lineEdit_apassword->text())
                {
                    ui->label_apassword->setText(QString("√"));
                    megflags |= PASSWORD_OK;//账号填充完成 --标志位置起
                }
                else
                    ui->label_apassword->setText(QString("两次输入密码不同"));
            }
            else
                ui->label_apassword->setText(QString("请确认密码"));
        }
    }
    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}

//注册界面按钮按下
void regist::on_pushButton_clicked()
{
    if(ui->lineEdit_8->isModified() && !ui->lineEdit_8->text().isEmpty())//行编辑器内容改变且非空
        megflags |= PHONE_OK;//电话填充完成 --标志位置起
    else
        megflags &= ~PHONE_OK;

    if(ui->lineEdit_4->isModified() && !ui->lineEdit_4->text().isEmpty())//行编辑器内容改变且非空
        megflags |= NAME_OK;//姓名填充完成 --标志位置起
    else
        megflags &= ~NAME_OK;

    if(megflags == FLAG_OK) //注册必要信息填充完毕
    {
        //重置提示信息
        ui->label_tip1->setText(QString("*为必填项"));

        //填充结构体
        memset(&sendmsg, 0, sizeof(staff_t));//清空发送消息结构体
        sendmsg.cmd = Register;//填充命令
        memcpy(sendmsg.id, ui->lineEdit_account->text().toUtf8().data(), sizeof(sendmsg.id));//获取账号
        memcpy(sendmsg.name, ui->lineEdit_4->text().toUtf8().data(), sizeof(sendmsg.name));//获取姓名
        memcpy(sendmsg.passwd, ui->lineEdit_password->text().toUtf8().data(), sizeof(sendmsg.passwd));//获取密码
        memcpy(sendmsg.sex, ui->lineEdit_7->text().toUtf8().data(), sizeof(sendmsg.sex));//获取性别
        sendmsg.age = ui->lineEdit_5->text().toInt();//获取年龄
        memcpy(sendmsg.phone, ui->lineEdit_8->text().toUtf8().data(), sizeof(sendmsg.phone));//获取性别
        memcpy(sendmsg.addr, ui->lineEdit_6->text().toUtf8().data(), sizeof(sendmsg.addr));//获取地址
        emit sigsendmsg();//发送 发送信息 信号
    }
    else
        ui->label_tip1->setText(QString("*为必填项 请填充必填项"));
}

//初始化函数
void regist::init()
{

}

//析构函数
regist::~regist()
{
    delete ui;
}


