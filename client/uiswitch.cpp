#include <QHostAddress>

#include "uiswitch.h"
#include "config.h"

staff_t sendmsg;//发送消息结构体
staff_t recvmsg;//接收消息结构体

uiswitch::uiswitch()
{
    reg = new regist;
    login = new landWidget;
    mwnd = new mainwnd;
    timer = new QTimer;
    login->ui->pushButton_2->setDisabled(true);//登陆按钮失能
    login->ui->pushButton->setDisabled(true);//注册按钮失能
    login->show();//显示登陆界面

    //mwnd->show();//显示主界面
//    reg->show();//显示注册界面

    //得到流式套接字
    rws = new QTcpSocket(this);
//    if(!rws->isOpen())
//        login->ui->label_tip->setText(QString("isOpen:false"));

    //关联定时器
    connect(timer, &QTimer::timeout, this, &uiswitch::slottimeout);

    //关联登陆界面信号槽
    //注册按钮按下触发函数on_logup_clicked
    connect(login->ui->pushButton,&QPushButton::clicked,
            this,&uiswitch::on_logup_clicked);
    //登陆按钮按下触发函数on_login_clicked
    connect(login->ui->pushButton_2,&QPushButton::clicked,
            this,&uiswitch::on_login_clicked);
    //连接服务器按钮
    connect(login->ui->pushButton_3,&QPushButton::clicked,
            this,&uiswitch::slotconnect);
    //连接服务器信号
    connect(this,&uiswitch::sigconnect,
            this,&uiswitch::slotconnect);

    //关联注册界面按钮
    //注册界面注册按钮按下
    connect(reg, &regist::sigsendmsg,
            this, &uiswitch::slotSendMsg);

    //接收到sendmsg信号时调用发送消息槽函数slotSendMsg
    connect(this,&uiswitch::sigsendmsg,
            this,&uiswitch::slotSendMsg);

    //关联主界面信号槽
    //接收到主界面发送的mainclose消息，界面关闭
    connect(mwnd,&mainwnd::mainclose,
            this,&uiswitch::slotclose);
    connect(mwnd,&mainwnd::mainlogout,
            this,&uiswitch::slotlogout);


    //关联套接字信号槽
    //连接服务器成功触发信号connected
    connect(rws, SIGNAL(connected()),this, SLOT(slotConnected()));
    //流式套接字出错【譬如连接失败】触发信号error(QAbstractSocket::SocketError )
    connect(rws, SIGNAL(error(QAbstractSocket::SocketError )),
            this, SLOT(slotError()));
    //连接断开则触发信号disconnected()
    connect(rws, SIGNAL(disconnected()),
            this, SLOT(slotDisconnected()));
    //套接字接收缓存有数据触发readyRead()
    connect(rws, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));

    emit sigconnect();//发起服务器连接
}

//TCP连接成功
void uiswitch::slotConnected()
{
    login->ui->pushButton_3->setText(QString("服务器连接成功"));//设置连接按钮标签
    login->ui->pushButton_2->setEnabled(true);//登陆按钮使能
    login->ui->pushButton->setEnabled(true);//登陆按钮使能
}

//TCP错误连接
void uiswitch::slotError()
{
    login->ui->pushButton_3->setEnabled(true);//连接按钮使能
    login->ui->pushButton_3->setText(QString("失败-请重试"));
    login->ui->pushButton_2->setDisabled(true);//登陆按钮失能
    login->ui->pushButton->setDisabled(true);//登陆按钮失能

    rws->close();//关闭套接字
}

void uiswitch::slotDisconnected()
{
    //关闭套接字
    rws->close();
}

void uiswitch::slotReadyRead()
{
    QByteArray arr = rws->readAll();//从接收缓存把数据全部读出
    memset(&recvmsg, 0, sizeof(staff_t));//清空接收消息结构体
    memcpy(&recvmsg.cmd, arr.data(), sizeof(staff_t));//存到接收消息结构体
    qDebug("接收信息");
    if(!arr.isNull())//接收数据非空
    {
        qDebug() << "接收数据非空 进入switch" << "命令号：" << recvmsg.cmd;

        switch(recvmsg.cmd){

        case RegisterOk:
            //注册成功
            login->ui->label_tip->setText(QString("注册成功 请登录"));
            reg->hide();//隐藏注册界面
            login->show();//显示登陆界面
            break;

        case RegisterFail:
            //注册失败
            login->ui->label_tip->setText(QString("注册失败"));
            reg->hide();//隐藏注册界面
            login->show();//显示登陆界面
            break;

        case LandOk:
            //设置员工信息
            mwnd->ui->lineEdit_17->setText(QString(recvmsg.id).toUtf8());//账号信息
            mwnd->ui->lineEdit_19->setText(QString(recvmsg.passwd).toUtf8());//密码信息
            mwnd->ui->lineEdit_18->setText(QString(recvmsg.name).toUtf8());//姓名
            mwnd->ui->lineEdit_4->setText(QString::number(recvmsg.age));//年龄
            mwnd->ui->lineEdit_5->setText(QString(recvmsg.sex).toUtf8());//性别
            mwnd->ui->lineEdit_7->setText(QString(recvmsg.phone).toUtf8());//电话
            mwnd->ui->lineEdit_8->setText(QString(recvmsg.addr).toUtf8());//住址
            mwnd->ui->lineEdit_6->setText(QString::number(recvmsg.salary));//工资
            //登陆成功
            login->ui->label_tip->setText(QString("登陆成功"));//设置提示信息
            login->ui->pushButton_2->setEnabled(true);//登陆按钮使能
            login->hide();//登陆界面隐藏
            mwnd->init();//主界面初始化
            mwnd->show();//主界面显示

            break;

        case LandFail:
            //登陆失败
            login->ui->label_tip->setText(QString("登陆失败"));
            login->ui->pushButton_2->setEnabled(true);//登陆按键使能
            timer->stop();//关闭定时器
            break;

        case InsertOk:
            break;

        case InsertFail:
            break;

        case QueryOk:
            break;

        case QueryFail:
            break;

        default:
            login->ui->label_tip->setText(QString("命令码错误"));
            break;
        }
    }
    qDebug("接收消息：-----");
    qDebug("账号：%s", recvmsg.id);
    qDebug("姓名：%s", recvmsg.name);
    qDebug("密码：%s", recvmsg.passwd);
    qDebug("性别：%s", recvmsg.sex);
    qDebug("年龄：%d", recvmsg.age);
    qDebug("电话：%s", recvmsg.phone);
    qDebug("地址：%s", recvmsg.addr);

//    //移动文本框的光标文本框尾巴
//    ui->textEdit->moveCursor(QTextCursor::End);
//    ui->textEdit->insertPlainText(text);
}

//发送消息槽函数
void uiswitch::slotSendMsg()
{
    qDebug("发送信息：-----");
    qDebug("账号：%s", sendmsg.id);
    qDebug("姓名：%s", sendmsg.name);
    qDebug("密码：%s", sendmsg.passwd);
    qDebug("性别：%s", sendmsg.sex);
    qDebug("年龄：%d", sendmsg.age);
    qDebug("电话：%s", sendmsg.phone);
    qDebug("地址：%s", sendmsg.addr);

    char * message = (char *)&sendmsg;//获取消息结构体首地址

    if(rws->write(message, sizeof(staff_t)) == -1)//发送消息
    {
        qDebug("write error");
    }
}

//登陆按钮按下槽函数
void uiswitch::on_login_clicked()
{
    //界面切换
    login->show();//显示登录界面
    reg->hide();//隐藏注册界面

    //获取输入信息
    QString account = login->ui->lineEdit->text();//获取账号
    if(account.isEmpty())
    {
        login->ui->label_tip->setText(QString("请输入账号"));
        return;
    }
    QString passwd = login->ui->lineEdit_password->text();//获取密码
    if(passwd.isEmpty())
    {
        login->ui->label_tip->setText(QString("请输入密码"));
        return;
    }

    //登陆按钮状态设置
    login->ui->pushButton_2->setDisabled(true);//登陆按钮失能
    login->ui->label_tip->setText(QString("登陆中"));//设置提示标签

    //填充消息结构体
    sendmsg.cmd = Land;//命令填充
    memcpy(sendmsg.id, account.toUtf8().data(),sizeof(sendmsg.id));//账号id填充
    memcpy(sendmsg.passwd, passwd.toUtf8().data(),sizeof(sendmsg.cmd));//密码填充

    timer->start(TIMEOUT);//开启定时器

    emit sigsendmsg();//触发发送信息信号
}

//连接服务器函数
void uiswitch::slotconnect()
{
    login->ui->pushButton_3->setDisabled(true);//按钮失能
    login->ui->pushButton_3->setText(QString("连接服务器中"));
    rws->connectToHost(QHostAddress(IPADDR), PORT);//连接到主机
}

//注销登录函数
void uiswitch::slotlogout()
{
//    if(rws->isOpen())
//        rws->close();//关闭通信套接字
    mwnd->hide();//隐藏主界面
    login->init();//初始化登陆界面
    login->show();//显示登陆界面
}

//关闭界面函数
void uiswitch::slotclose()
{
    rws->close();//关闭通信套接字
    reg->close();//关闭注册界面
    login->close();//关闭登陆界面
    mwnd->close();//关闭主界面

    close();//关闭窗口
}

//注册按钮按下
void uiswitch::on_logup_clicked()
{
    login->hide();//隐藏登陆界面
    reg->show();//显示注册界面
}
//定时器超时
void uiswitch::slottimeout()
{
    login->ui->label_tip->setText(QString("连接超时 请重试"));
    login->ui->pushButton_2->setEnabled(true);//登陆按键使能
    timer->stop();//关闭定时器
}

//析构函数
uiswitch::~uiswitch()
{
    rws->close();//关闭套接字

    if(rws != NULL)
        delete rws;

    if(mwnd != NULL)
        delete mwnd;

    if(reg != NULL)
        delete reg;

    if(login != NULL)
        delete login;
}
