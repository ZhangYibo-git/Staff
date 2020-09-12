#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>


#define SQL_LEN 256

#define DATABASE "staff.db"


//命令类型
typedef enum
{
	Register = 1, //注册
	Query, 		  //查询
	Land, 		  //登录
	Insert, 	  //插入

	RegisterOk ,  //注册成功
	QueryOk, 	  //查询成功
	LandOk, 	  //登录成功
	InsertOk, 	  //插入成功
	
	RegisterFail,     //注册失败
	QueryFail, 		  //查询失败
	LandFail, 		  //登录失败
	InsertFail, 	  //插入失败

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

}staff;




/*

void do_delete();   //删除用户
void do_update_password(); //修改密码


void creste_database();    //创建数据库


*/


void do_login(staff* msg,int connfd); 	//登录用户

void do_register(staff* msg,int connfd); //注册用户
















#endif
