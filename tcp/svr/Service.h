#ifndef SERVICE_H
#define SERVICE_H
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/epoll.h>
#include<unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include"svr_cfg.h"
#include"../Sock.h"



namespace Service_
{
	using namespace Sock_;
	typedef struct data{
		/*
		 * 数据：
		 * 	数据大小：int size
		 *	数据类型：int flag    0 --> 聊天数据  1 --> 传输文件数据
		 *	数据本身：char * data
		 */
	}Data;

	class Service:public Sock{
		/*
		 *数据： 
		 *	监听数目: const int listenNum
		 *	epoll监听数目：const int epollNum
		 *	端口号：const int port
		 *	套接字描述符  int fd
		 *	ip地址： const char * ip
		 *
		 *	服务端 struct sockaddr_in serviceAddr
		 *
		 *方法：
		 *	构造：Service(const int port_,const int l_len,const int ep_len,const char * ip,const int pro)  数据分配空间 结构体地址分配空间,
		 *	绑定监听端口：bindAndListenPort()
		 *	epoll监听： epollListen()
		 *	获得监听套接字 getSocketFd()
		 *	获得服务器ip：getServiceIP()
		 *	获得服务器端口：getServicePort()
		 */


		public:
			Service(const int port_ , const int l_len,const int ep_len,const char * ip,const int pro);
			~Service();
			int bindAndListenPort();
			int getSocketFd();
			const char * getServiceIp();
			const int getServicePort();
			int epollListen();

		private:
			const int port;
			const int listenNum;
			const int epollNum;
			int fd;
			int exec;
			struct sockaddr_in serviceAddr;
			const char * ip;
			
	};
#if 0
	class listenedObject{
		/*
		 *数据：
		 *	客户端的结构体长度：socklen_t * clientLen
		 *	客户端对应的套接字：int clientFd
		 *	客户端 struct sockadrr_in clientAddr
		 *	数据：Data * data
		 *		
		 */

	}
#endif
}//namespace Service_




#endif
