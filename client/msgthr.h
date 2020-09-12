#ifndef MSGTHR_H
#define MSGTHR_H
#include <QThread>

class msgThr : public QThread
{
    Q_OBJECT
public:
    explicit msgThr(QObject *p=nullptr);
    ~msgThr();
    void init();
//signals:
//    void sigText(QString);

private:
    void run();
};
#endif // MSGTHR_H
