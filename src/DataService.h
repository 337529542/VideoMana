#pragma once

class DataService
{
public:
	bool Open(char *filename);
	void Close();

	bool Files_Insert();//插入文件
	bool Files_Check();//检查是否有重名文件(仅检查Active的文件)
	bool Files_UpdatePath();//更新文件路径
	bool Files_DeActive();//设置文件的active属性=0(移除该条记录)
	bool Files_GetInfoByName();//获取文件属性(仅获取active的文件的属性)
	bool Files_GetInfoByNum();//通过序号（不是id）获取文件,返回false为到末尾

	bool Img_Insert();//插入图片
	bool Img_Get();//获取图片信息
	//bool Img_RemoveByID();//删除一张图片
	bool Img_RemoveByFileName();//删除与这个FileName关联的所有图片
};