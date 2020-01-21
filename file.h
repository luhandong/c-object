#ifndef FILE_H
#define FILE_H
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"cfg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>


namespace file_{
	class file
	{
		/*
		 * 数据 存储文件数据 char * f_str
		 * 	文件名字 char * f_name
		 * 	文件描述符 int fd
		 * 	文件字符数目 int str_num
		 * 	文件读取的路径 char * f_readPath
		 * 	文件写入的路径 char * f_writePath
		 *
		 * 方法
		 * 	构造 file(const char * name):f_name(name){f_str = nullptr;} --初始化存储文件的数据的空间，若是后面没有分配空间给f_str 那么这个指针的值就是nullptr
		 * 	析构 ~file(){if(f_str != nullptr){delete f_str;}}
		 * 	设置文件读取路径 setReadPath(const char * readPath) 
		 * 	设置文件写入路径 setWritePath(const char * writePath)
		 * 	文件字符数目获取 getFileCharacterNumber()
		 * 	文件读取 readFile()
		 *	文件写  writeFile()
		 */
		public:

			file(const char *  name);
			~file();
			int setReadPath(const char * readPath);
			int setWritePath(const char * writePath);
			int getFileCharaterNumber();
			char * readFile(int * data_len);
			int writeFile(char *  data,int data_len);

		private:
			int fd;
			int str_num;
			char * f_str;
			const char * f_name;
			char * f_readPath;
			char * f_writePath;	
	};
} //namespace file_




#endif
