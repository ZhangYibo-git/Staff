#ifndef UISWITCH_H
#define UISWITCH_H

#include <QTcpSocket>
#include <QTimer>

#include "landwidget.h"
#include "regist.h"
#include "mainwnd.h"


class uiswitch : public QWidget
{
    Q_OBJECT


public:
    uiswitch();
    ~uiswitch();

    landWidget *login;//登录界面
    regist *reg;//注册界面
    mainwnd *mwnd;//主界面
    QTimer *timer;//定时器

private:
    QTcpSocket *rws;

signals:
    void sigsendmsg();
    void sigconnect();


private slots:
    void on_logup_clicked();//注册按钮按下
    void on_login_clicked();//登陆按钮按下

    void slotConnected();//已连接处理函数
    void slotError();//链接错误处理函数
    void slotDisconnected();//断开连接
    void slotSendMsg();//发送消息
    void slotclose();//关闭
    void slotlogout();//注销登录
    void slotconnect();//连接客户端函数
    void slotReadyRead();//
    void slottimeout();//定时器超时槽函数

};



#endif // UISWITCH_H
