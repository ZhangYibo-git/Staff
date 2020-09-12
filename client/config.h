#ifndef CONFIG_H
#define CONFIG_H


//服务器IP
#define IPADDR "192.168.1.222"
//端口号
#define PORT 6060
//超时时间
#define TIMEOUT 3000
//注册标志位
#define ACCOUNT_OK 0x1
#define PASSWORD_OK 0x2
#define PHONE_OK 0x4
#define NAME_OK 0x8
#define FLAG_OK 0xF

//权限
#define USER 0
#define ROOT 1

//命令
typedef enum{
    Register = 1,   //注册 ---1
    Query,          //查询 ---2
    Land,           //登陆 ---3
    Insert,         //插入(修改信息)
    RegisterOk,     //注册成功
    QueryOk,        //查询成功 ---6
    LandOk,         //登陆成功
    InsertOk,       //插入成功
    RegisterFail,     //注册失败
    QueryFail,        //查询失败 ---10
    LandFail,         //登陆失败 ---11
    InsertFail,        //插入失败
}cmd_e;

//消息结构体
typedef struct {
    cmd_e cmd;          //命令类型
    char id[5];         //编号（帐号4位）
    char permission;    //权限
    char name[20];      //名字
    char passwd[20];    //密码
    char sex[5];        //性别
    int age;            //年龄
    char phone[12];     //电话
    char addr[20]; 		//地址
    int salary;         //薪水

}staff_t;

#endif // CONFIG_H
