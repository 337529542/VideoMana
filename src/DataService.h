#pragma once

class DataService
{
public:
	bool Open(char *filename);
	void Close();

	bool Files_Insert();//�����ļ�
	bool Files_Check();//����Ƿ��������ļ�(�����Active���ļ�)
	bool Files_UpdatePath();//�����ļ�·��
	bool Files_DeActive();//�����ļ���active����=0(�Ƴ�������¼)
	bool Files_GetInfoByName();//��ȡ�ļ�����(����ȡactive���ļ�������)
	bool Files_GetInfoByNum();//ͨ����ţ�����id����ȡ�ļ�,����falseΪ��ĩβ

	bool Img_Insert();//����ͼƬ
	bool Img_Get();//��ȡͼƬ��Ϣ
	//bool Img_RemoveByID();//ɾ��һ��ͼƬ
	bool Img_RemoveByFileName();//ɾ�������FileName����������ͼƬ
};