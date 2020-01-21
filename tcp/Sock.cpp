#include"Sock.h"

using namespace Sock_;

Sock::Sock(const int pro):
protocol(pro)
{
	fd = nullptr;
}

Sock::~Sock()
{
	if(fd != nullptr)
	{
		delete fd;
	}
}

void Sock::createSocket()
{
	using namespace std;
	if(fd == nullptr)
	{
		fd = new int;
	}	
	else if(*fd <0)
	{
		cout<< "*fd is err"<<endl;
		goto err;
	}
	else
	{
		cout<<"haved a fd, don't need createSocket again"<<endl;
		goto haved;
	}

	if(protocol == 1)
	{
		*fd = socket(AF_INET,SOCK_STREAM,0);
	}
	else if(protocol == 2)
	{
		*fd = socket(AF_INET,SOCK_DGRAM,0);
	}
	else
	{
		cout<<"protocol is "<<protocol<<" err!!"<<endl;
		goto err;
	}
haved:
err:
	return;
}

int Sock::getSocket()
{
	return *fd;
}


//test case
/*
int main()
{
	using namespace std;
	Sock s(TCP);
	s.createSocket();
	cout<<s.getSocket()<<endl;
}
*/
