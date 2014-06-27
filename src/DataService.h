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
	bool Open(char *filename);//�����ݿ�����
	void Close();//�ر����ݿ�����

	bool Files_Insert(dbFiles f);//�����ļ�
	bool Files_Check(dbFiles f);//����Ƿ��������ļ�(�����Active���ļ�)
	bool Files_UpdatePath(dbFiles f);//�����ļ�·��
	bool Files_DeActive(dbFiles f);//�����ļ���active����=0(�Ƴ�������¼)
	bool Files_GetInfoByName(char* filename, dbFiles *pf);//��ȡ�ļ�����(����ȡactive���ļ�������)
	bool Files_GetInfoByNum(int num, dbFiles *pf);//ͨ����ţ�����id����ȡ�ļ�,����falseΪ��ĩβ

	bool Img_Insert(dbImage *pImg);//����ͼƬ
	bool Img_Get(char *filename, dbImage *pImg, int num);//��ȡͼƬ��Ϣ
	//bool Img_RemoveByID();//ɾ��һ��ͼƬ
	bool Img_RemoveByFileName(char *filename);//ɾ�������FileName����������ͼƬ
};