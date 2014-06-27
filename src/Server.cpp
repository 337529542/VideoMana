#include "Server.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>


void Server::run(std::wstring rootPath)
{
	wprintf(L"\nBegin........%s\n", rootPath.c_str());

	//�����������
	srand( (unsigned)time( 0 ) );

	//�������ݿ�
	ds.Open("MediaData");

	//�����ļ���
	fs.setNotify(this);
	fs.find(rootPath + L"\\");

	wprintf(L"\nFinish........\n");
}

void Server::NotifyFind(std::wstring filename, std::wstring path)
{
	bool isFind = false;
	//����ƥ��
	isFind = isFind 
		|| (filename.find(L".avi") != std::wstring::npos)
		|| (filename.find(L".wmv") != std::wstring::npos)
		|| (filename.find(L".mp4") != std::wstring::npos)
		|| (filename.find(L".mov") != std::wstring::npos)
		|| (filename.find(L".rm") != std::wstring::npos)
		|| (filename.find(L".rmvb") != std::wstring::npos)
		|| (filename.find(L".mkv") != std::wstring::npos)
		|| (filename.find(L".asf") != std::wstring::npos)
		|| (filename.find(L".AVI") != std::wstring::npos)
		|| (filename.find(L".WMV") != std::wstring::npos)
		|| (filename.find(L".MP4") != std::wstring::npos)
		|| (filename.find(L".MOV") != std::wstring::npos)
		|| (filename.find(L".RM") != std::wstring::npos)
		|| (filename.find(L".RMVB") != std::wstring::npos)
		|| (filename.find(L".MKV") != std::wstring::npos)
		|| (filename.find(L".ASF") != std::wstring::npos);

	if(isFind)
	{
		//��ȡʱ��
		int tim = vs.getDuration(path+filename);
		if(tim <= 0)
		{
			wprintf(L"��ȡʱ���쳣 %s | %s\n", filename.c_str(), path.c_str());
		}

		//���ļ�����·��ת��Ϊutf8��ʽ
		std::string name8, path8;
		name8 = UniService::Unicode2UTF8(filename);
		path8 = UniService::Unicode2UTF8(path);

		//������ݿ����Ƿ��и��ļ�
		if(ds.Files_Check((char *)name8.c_str()))
		{
			//ɾ���ļ�
			wprintf(L"�ҵ������ļ� %s | %s\n", filename.c_str(), path.c_str());
			ds.Files_DeActive((char *)name8.c_str());
			ds.Img_RemoveByFileName((char *)name8.c_str());
		}

		//��������
		dbFiles f;
		f.Duration = tim;
		f.FileName = name8;
		f.InDate = 0;
		f.Path = path8;
		f.Title = name8;

		ds.Files_Insert(f);

		//ÿ����Ƶץȡ10��ͼƬ
		int lastt = -1000;
		for(int i=0; i<10; i++)
		{
			//��ʱ����Χ���������ʱ��
			int t;
			for(int j=0; j<10; j++)//������ϴν��̫���������������������10��
			{
				t = tim>300 ? rand()%(tim-120) + 60 : rand()%tim  ;//���ڴ�������ӵ���Ƶ����ʼ�ͽ�β��60s��Ҫ

				if(abs(t - lastt) > 60)
					break;
			}

			lastt = t;

			//����ͼƬ
			VideoImage vimg;
			if(vs.getImage(path + filename, t, &vimg))
			{
				//��ͼƬ���浽���ݿ�
				dbImage dbimg;
				dbimg.setBufSize(vimg.sizeinbyte);
				memcpy(dbimg.pbuf, vimg.buf, vimg.sizeinbyte);
				dbimg.FileID = 0;
				dbimg.FileName = name8;
				dbimg.Show = 1;
				dbimg.Time = t;
				ds.Img_Insert(&dbimg);
			}
		}

		wprintf(L"����ļ�:%s| ʱ��:%d | ·��| %s\n", filename.c_str(), tim, path.c_str());
	}
}