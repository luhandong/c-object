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
			fp = fopen(f_readPath,"r");
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
			fp = fopen(f_writePath,"r");
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

char * file::readFile(){
	using namespace std;
	if(f_readPath != nullptr && f_writePath == nullptr)
	{
		FILE * fp;
		fp = fopen(f_readPath,"r");
		if(fp == nullptr)
		{
			cerr<<"fopen f_readPath "<<endl;
			goto err;
		}

		getFileCharaterNumber();

		f_str = new char[str_num];

		if(fread(f_str,str_num,1,fp)<=0)
		{
			cout<<"fread f_readPath"<<endl;
			fclose(fp);
			goto err;
		}

	}
	else
	{
		cout<<"filePath is err,"<<endl;
		goto err;
	}

	return f_str;
err:
	return nullptr;

}

int file::writeFile(char *  data)
{
	using namespace std;
	if(f_writePath != nullptr && f_readPath == nullptr)
	{
		FILE * fp;
		int data_len=0;
		f_str = new char[strlen(data)];
		if(f_str == nullptr)
		{
			cout << "f_str new write file"<<endl;
			goto err;
		}
		strcpy(f_str,data);
		fp = fopen(f_writePath,"w");
		if(fp == nullptr)
		{
			cerr<<"fopen f_readPath "<<endl;
			goto err;
		}
		if(fwrite(f_str,strlen(f_str),1,fp)<=0)
		{
			cerr<<"fwrite write file"<< endl;
			fclose(fp);
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
int main()
{
	using namespace std;
	file f("cfg.h");
	file f1("cfg.h.bak");
	f1.setWritePath("./cfg.h.bak");
	f.setReadPath("./cfg.h");
	cout <<f.getFileCharaterNumber()<<endl;
	cout<<f.readFile()<<endl;
	cout<<f1.writeFile(f.readFile())<<endl;
}
