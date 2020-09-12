#include "sever.h"
#include "sqlite3.h"
#include "stdlib.h"

extern sqlite3 *db;

//注册用户
void do_register(staff *msg, int connfd)
{
	char sql[SQL_LEN];//定义大数组尽量不要放在函数内

	char *errmsg;
	sprintf(sql,"insert into user_msg values('%s', %d,'%s','%s\','%s\',%d,'%s\','%s\',%d);",\
		msg->id, msg->permission, msg->name, msg->passwd, msg->sex, msg->age, msg->phone,\
		msg->addr, msg->salary);
	printf("注册时发送的命令sql：%s\n", sql);//调试用
	
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("register_sql %s\n",errmsg);
		return;
	}
	
	memset(msg, 0, sizeof(staff));//清空发送消息结构体
	msg->cmd=RegisterOk;//填充命令
	send(connfd,msg,sizeof(staff),0);//发送消息

}


//登录用户
void do_login(staff*msg,int connfd)
{

	char **dbResult;//结果
	int tRow,tColumn;//行列
	char* tzErrmsg;//错误信息
	char sql[SQL_LEN] = {0};

	sprintf(sql,"select * from user_msg where id='%s' and passwd='%s';", msg->id, msg->passwd);
	printf("登陆时发送的命令sql：%s\n", sql);//调试用

	if(sqlite3_get_table(db, sql, &dbResult, &tRow, &tColumn, &tzErrmsg) != SQLITE_OK)
	{
		printf("sqlite3_get_table error:%s\n", tzErrmsg);
		return;
	}
	if(tRow == 0)
	{
		printf("查找不到\n");
		memset(msg, 0, sizeof(staff));
		msg->cmd=LandFail;
		send(connfd, msg, sizeof(staff),0);
	}
	else
	{
		int i,j;
		int index =  tColumn;
		//打印调试用
		// for(i = 0; i < tRow; i++) {
        //     for(j = 0; j < tColumn; j++) {
        //         printf("%d--%s : %s\n", i, dbResult[j], dbResult[index++]);
        //         //  ++index;
        //     }
        //     printf("----------------------------------------------\n");
        // }
		memset(msg, 0, sizeof(staff));
		msg->cmd = LandOk;//填充命令
		strcpy(msg->id, dbResult[index++]);
		msg->permission = atoi(dbResult[index++]);
		strcpy(msg->name, dbResult[index++]);
		strcpy(msg->passwd, dbResult[index++]);
		strcpy(msg->sex, dbResult[index++]);
		msg->age = atoi(dbResult[index++]);
		strcpy(msg->phone, dbResult[index++]);
		strcpy(msg->addr, dbResult[index++]);
		msg->salary = atoi(dbResult[index++]);
		

		send(connfd, msg, sizeof(staff), 0);//发送消息
		//打印调试
		printf("账号：%s\n", msg->id);
		printf("姓名：%s\n", msg->name);
		printf("密码：%s\n", msg->passwd);
		printf("性别：%s\n", msg->sex);
		printf("年龄：%d\n", msg->age);
		printf("电话：%s\n", msg->phone);
		printf("地址：%s\n", msg->addr);
		printf("工资：%d\n", msg->salary);
		printf("命令: %d\n", msg->cmd);
	}

}

/*

do_delete(staff*sta,int connfd)
{

}

do_update_password(staff*sta,int connfd)
{

}

*/











