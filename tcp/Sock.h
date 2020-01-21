#ifndef SOCK_H
#define SOCK_H
#include<iostream>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#define TCP 1
#define UDP 2

namespace Sock_{
	class Sock{
		/*数据：
		 * 	套接字 int *fd;
		 * 	协议类型 const int protocol;
		 *
		 * 方法：
		 * 	构造 Sock(const int pro):protocol(pro){}
		 * 	析构 ~Sock(){}
		 * 	创建套接字 createSocket();
		 * 	获得套接字 getSocket();
		 */
		public:
			Sock(const int pro);
			~Sock();
			void createSocket();
			int getSocket();

		private:
			int * fd;
			const int protocol;
	};

}//namespace Sock



#endif
