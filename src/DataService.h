#pragma once
#include <string>
#include "SQLiteWrapper.h"

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
	int getBufSize();
	dbImage();
	~dbImage();

private:
	int s;
};

class DataService
{
public:
	bool Open(char *filename);//�����ݿ�����

	bool Files_Insert(dbFiles f);//�����ļ�
	bool Files_Check(char *filename);//����Ƿ��������ļ�(�����Active���ļ�)
	bool Files_UpdatePath(dbFiles f);//�����ļ�·��
	bool Files_DeActive(char *filename);//�����ļ���active����=0(�Ƴ�������¼)
	bool Files_GetInfoByName(char* filename, dbFiles *pf);//��ȡ�ļ�����(����ȡactive���ļ�������)
	bool Files_GetInfoByNum(int num, dbFiles *pf);//ͨ����ţ�����id����ȡ�ļ�,����falseΪ��ĩβ

	bool Img_Insert(dbImage *pImg);//����ͼƬ
	bool Img_Get(char *filename, dbImage *pImg, int num);//��ȡͼƬ��Ϣ
	//bool Img_RemoveByID();//ɾ��һ��ͼƬ
	bool Img_RemoveByFileName(char *filename);//ɾ�������FileName����������ͼƬ

private:
	SQLiteWrapper sqlite;

};