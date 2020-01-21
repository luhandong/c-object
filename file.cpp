#include"file.h"

using namespace file_;

file::file(const char *  name):
	f_name(name){
		f_str = nullptr;
		fd = 0;
		str_num = 0;
		f_readPath = nullptr;
		f_writePath = nullptr;
	}

file::~file(){
	if(f_str != nullptr)
	{
		delete f_str;
	}
	if(f_readPath != nullptr)
	{
		delete f_readPath;
	}
	if(f_writePath != nullptr)
	{
		delete f_writePath;
	}
}

int file::setReadPath(const char * readPath)
{
	using namespace std;
	if(f_readPath == nullptr)
	{
		f_readPath = new char[20];
	}
	strcpy(f_readPath,readPath);
	return 0;
}

int file::setWritePath(const char * writePath)
{
	using namespace std;
	if(f_writePath == nullptr)
	{
		f_writePath = new char[20];
	}
	strcpy(f_writePath,writePath);
	return 0;
}

int file::getFileCharaterNumber()
{
	using namespace std;
	int count_f = 0;
	FILE * fp;
	char temp_c;
	int temp_count;
	if(f_readPath == nullptr && f_writePath == nullptr)
	{
		cout<<"file is not exist"<<endl;
		goto err;
	}
	else
	{
		if(f_readPath != nullptr && f_writePath == nullptr)
		{
			fp = fopen(f_readPath,"r+");
			if(fp == nullptr)
			{
				cerr<<"fopen f_readPath err"<<endl;
				cout<< f_readPath<<endl;
				goto err;
			}

			while((temp_count = fread(&temp_c,1,1,fp)) == 1)
			{
				count_f ++;
			}
			if(temp_count != 0)
			{
				fclose(fp);
				goto err;
			}

		}
		else if(f_readPath ==nullptr && f_writePath != nullptr)
		{
			fp = fopen(f_writePath,"r+");
			if(fp == nullptr)
			{
				cerr<<"fopen f_writePath err"<<endl;
				goto err;
			}

			while((temp_count = fread(&temp_c,1,1,fp)) == 1)
			{
				count_f ++;
			}
			if(temp_count != 0)
			{
				fclose(fp);
				goto err;
			}

		}
		else
		{
			cout<<"filePath is err"<<"readPath is "<< f_readPath<< "writePath is "<< f_writePath<<endl;
			goto err;
		}
	}

	str_num = count_f;
	return str_num;

err:
	return -1;
}

char * file::readFile(int * data_len){
	using namespace std;
	if(f_readPath != nullptr && f_writePath == nullptr)
	{
		int fd=0;
		int count=0;
		fd = open(f_readPath,O_RDONLY);
		if(fd < 0)
		{
			cerr<<"open f_readPath "<<endl;
			goto err;
		}

		getFileCharaterNumber();

		f_str = new char[str_num];

		for(count = 0; count<str_num;count++)
		{
			if(read(fd,&(f_str[count]),1)!=1)
			{
			//	count<<"read  error"<<endl;
				close(fd);
				goto err;
			}
		}
	}
	else
	{
		cout<<"filePath is err,"<<endl;
		goto err;
	}
	*data_len = str_num;
	return f_str;
err:
	return nullptr;

}

int file::writeFile(char *  data,int data_len_)
{
	using namespace std;
	if(f_writePath != nullptr && f_readPath == nullptr)
	{
		printf("data_len is %d\n",data_len_);
		int fd =0;
		int count = 0;
		f_str = new char[data_len_+1];
		if(f_str == nullptr)
		{
			cout << "f_str new write file"<<endl;
			goto err;
		}
		memset(f_str,0,data_len_+1);
		memcpy(f_str,data,data_len_);
		fd = open(f_writePath,O_WRONLY|O_CREAT,0777);
		if(fd < 0)
		{
			cerr<<"open f_writePath "<<endl;
			goto err;
		}
		
		if((count = write(fd,f_str,data_len_))!=data_len_)
		{
			perror("write");
			printf("write count is %d\n",count);
			close(fd);
			goto err;
		}
	}
	else
	{
		goto err;
	}
	return 0;
err:
	return -1;
}
//test  case
int main(int argc,char ** argv)
{
	using namespace std;
	int data_len;
	file f(argv[1]);
	file f1(argv[2]);
	f1.setWritePath(argv[2]);
	f.setReadPath(argv[1]);
	cout <<f.getFileCharaterNumber()<<endl;
	char * str = f.readFile(&data_len); //获得读取数据的长度
	cout<<f1.writeFile(str,data_len)<<endl;
}
