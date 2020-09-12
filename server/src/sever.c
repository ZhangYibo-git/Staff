#include "sever.h"	
#include "sqlite3.h"


sqlite3 *db;

int main(int argc, const char *argv[])
{

	staff recvmsg;
	int ret;
	//打开数据库
	if(sqlite3_open(DATABASE, &db) != 0)
	{
		printf("%s\n",sqlite3_errmsg(db));
		return ;
	}

	//创建套接字
	int listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in seraddr,client; 		//定义了两个结构体变量
	seraddr.sin_family = AF_INET; 			//采用的协议族类型
	seraddr.sin_port = htons(6060); 			//端口号
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);  //网络ip地址的设置

	//套接字绑定
	ret = bind(listenfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}

	//允许重复使用端口和地址
	int flag = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR, &flag, sizeof(flag)) == -1)
	{
		perror("setsockopt");
		return -1;
	}

	//监听套接字
	ret = listen(listenfd, 1024);
	if(ret == -1)
	{
		perror("listen");
		return -1;
	}
	printf("listening---\n");
	int connfd;
	int len = sizeof(client);

	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr*)&client, &len);//监听连接---
		if(connfd == -1)
		{
			close(listenfd);
			perror("accept");
			return -1;
		}
		printf("connect sucess---\n");
		while(1)
		{
			memset(&recvmsg, 0, sizeof(staff));//清空接收消息结构体
			ret = recv(connfd, &recvmsg, sizeof(staff), 0);
			if(ret == 0 || ret == -1)
			{
				if(ret == -1){
					//错误连接
					printf("recv error\n");
				}
				else{
					//客户端断开连接
					printf("client quit\n");
				}
				break;
			}	
			printf("----------------------\n");
			printf("账号：%s\n", recvmsg.id);
			printf("姓名：%s\n", recvmsg.name);
			printf("密码：%s\n", recvmsg.passwd);
			printf("性别：%s\n", recvmsg.sex);
			printf("年龄：%d\n", recvmsg.age);
			printf("电话：%s\n", recvmsg.phone);
			printf("地址：%s\n", recvmsg.addr);

			printf("recvmsg.cmd:%d\n", recvmsg.cmd);
			switch(recvmsg.cmd)
			{
			case Register:
				//注册用户
				printf("start register\n");
				do_register(&recvmsg,connfd);
				break;

			case Land:
				//登录用户
				printf("start login\n");
				do_login(&recvmsg,connfd);
				break;

			case Insert:
				//修改密码
				break;

			case Query:
				//删除用户
				break;
			default:
				//退出
				break;
			}
		}
	}

	//关闭套接字
	close(listenfd);
	close(connfd);

	return 0;
}
