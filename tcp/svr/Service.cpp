#include"Service.h"

using namespace Service_;

Service::Service(const int port_,const int l_len,const int ep_len,const char * ip_,const int pro):
port(port_),
listenNum(l_len),
epollNum(ep_len),
ip(ip_),
Sock(pro){
	fd = 0;
	exec = 0;
}

Service::~Service()
{
}

int Service::bindAndListenPort()
{
	using namespace std;
	exec = 1;
	memset(&serviceAddr,0,sizeof(serviceAddr));
	serviceAddr.sin_family = AF_INET;	
	serviceAddr.sin_port = htons(port);
	if(! inet_aton(ip,&(serviceAddr.sin_addr)))
	{
		cout<<"init ip err"<<endl;
		goto err;
	}
	createSocket();
	fd = getSocket();
	
	if((bind(fd,(struct sockaddr *)&serviceAddr,sizeof(serviceAddr)))==-1)
	{
		perror("bind");
		goto err;
	}	
	
	if(listen(fd,listenNum))
	{
		perror("listen");
		goto err;
	}

	return 0;
err:
	return EOF;

}

int Service::getSocketFd()
{
	using namespace std;
	if(exec == 0)
	{
		cout<<"no have fd,please exec bindAndListenPort\n"<<endl;
	}
	return fd;
}

const char * Service::getServiceIp()
{
	using namespace std;
	if(exec == 0)
	{
		cout<<"no bind,please exec bindAndListenPort\n"<<endl;
	}
	return ip;
}

const int Service::getServicePort()
{
	using namespace std;
	if(exec == 0)
	{
		cout<<"no bind,please exec bindAndListenPort\n"<<endl;
	}
	return port;
}

int Service::epollListen()
{
	using namespace std;
	int epfd = 0;
	int ret = 0;
	int countFds = 0;
	int epollFd = 0;
	int epollReceiveFds;
	struct sockaddr_in clientAddr;
	socklen_t * clientAddrLen;
	struct epoll_event epollEvent[epollNum],epollEven;
	
	
	
	if(exec == 0)
	{
		cout<<"no bind,please exec bindAndListenPort\n"<<endl;
	}
	
	epfd = epoll_create(epollNum);
	if(epfd == EOF )
	{
		perror("epoll_create ");
		goto err;
	}
	
	epollEvent[0].events = EPOLLIN;
	epollEvent[0].data.fd = fd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,epollEvent);
	if(ret == EOF)
	{
		perror("epoll_ctl ");
		goto err;
	}

	//epoll wait
	while(1)
	{
		printf("epoll_wait\n");
		epollReceiveFds = epoll_wait(epfd,epollEvent,epollNum,-1);
		if(epollReceiveFds == EOF)
		{
			perror("epoll_wait");
			goto err;
		}
		for(countFds =0;countFds<epollReceiveFds;countFds++)
		{
			epollFd = epollEvent[countFds].data.fd;
			if(epollFd < 0)
			{
				printf("epollFd err\n");
				goto err;
			}

			if(epollFd == fd)
			{
				ret = accept(fd,(sockaddr *)&clientAddr,clientAddrLen);	
				if(ret == EOF)
				{
					perror("accept");
					goto err;
				}
				epollEven.events = EPOLL_IN;
				epollEven.data.fd = ret;

				ret = epoll_ctl(epfd,EPOLL_CTL_ADD,ret,&epollEven);
				if(ret == EOF)
				{
					perror("epoll_ctl add clientFd");
					goto err;
				}
			}
			else
			{
				//创建监听对象类，接受数据或者发送数据
			}
		}
		
		
	}
	
	return 0;
err:
	return -1;
}


int main()
{
	Service s(PORT,LISTENMAX,EPOLLMAX,IpAddr,TCP);
	s.bindAndListenPort();
	printf("s ip is %s port is %d fd is %d\n",s.getServiceIp(),s.getServicePort(),s.getSocketFd());
	s.epollListen();
}

