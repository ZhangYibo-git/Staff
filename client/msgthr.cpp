#include <QSemaphore>

#include "msgthr.h"

/*
起初用于发送接收数据的线程，在本版本无用
*/

//静态对象：本模块可见的一个对象
//定义一个信号量对象，初值为0
static QSemaphore sem(0);

msgThr::msgThr(QObject *p):QThread (p)
{

}

void msgThr::run()
{
//    //P操作：信号量减1【参数是减的值，默认值是1】
//    sem.acquire();

    //V操作：信号量加1【参数是加的值，默认值是1】
    sem.release();
}

msgThr::~msgThr()
{

}

