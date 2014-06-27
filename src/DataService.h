#pragma once
#include <string>

class dbFiles
{
public:
	int ID;
	std::string FileName;
	std::string Path;
	std::string Note;
	std::string Title;
	int Duration;
	int InDate;
	int Active;
	int Show;
};

class dbImage
{
public:
	int ID;
	int FileID;
	std::string FileName;
	int Time;
	int Show;
	char *pbuf;

	void setBufSize(int sizeinbyte);
	dbImage();
	~dbImage();
};

class DataService
{
public:
	bool Open(char *filename);//打开数据库连接
	void Close();//关闭数据库连接

	bool Files_Insert(dbFiles f);//插入文件
	bool Files_Check(dbFiles f);//检查是否有重名文件(仅检查Active的文件)
	bool Files_UpdatePath(dbFiles f);//更新文件路径
	bool Files_DeActive(dbFiles f);//设置文件的active属性=0(移除该条记录)
	bool Files_GetInfoByName(char* filename, dbFiles *pf);//获取文件属性(仅获取active的文件的属性)
	bool Files_GetInfoByNum(int num, dbFiles *pf);//通过序号（不是id）获取文件,返回false为到末尾

	bool Img_Insert(dbImage *pImg);//插入图片
	bool Img_Get(char *filename, dbImage *pImg, int num);//获取图片信息
	//bool Img_RemoveByID();//删除一张图片
	bool Img_RemoveByFileName(char *filename);//删除与这个FileName关联的所有图片
};