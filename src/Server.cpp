#include "Server.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>


void Server::run(std::wstring rootPath)
{
	wprintf(L"\nBegin........%s\n", rootPath.c_str());

	//设置随机种子
	srand( (unsigned)time( 0 ) );

	//连接数据库
	ds.Open("MediaData");

	//遍历文件夹
	fs.setNotify(this);
	fs.find(rootPath + L"\\");

	wprintf(L"\nFinish........\n");
}

void Server::NotifyFind(std::wstring filename, std::wstring path)
{
	bool isFind = false;
	//类型匹配
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
		//获取时长
		int tim = vs.getDuration(path+filename);
		if(tim <= 0)
		{
			wprintf(L"获取时间异常 %s | %s\n", filename.c_str(), path.c_str());
		}

		//将文件名和路径转换为utf8格式
		std::string name8, path8;
		name8 = UniService::Unicode2UTF8(filename);
		path8 = UniService::Unicode2UTF8(path);

		//检查数据库中是否有该文件
		if(ds.Files_Check((char *)name8.c_str()))
		{
			//删除文件
			wprintf(L"找到重名文件 %s | %s\n", filename.c_str(), path.c_str());
			ds.Files_DeActive((char *)name8.c_str());
			ds.Img_RemoveByFileName((char *)name8.c_str());
		}

		//插入数据
		dbFiles f;
		f.Duration = tim;
		f.FileName = name8;
		f.InDate = 0;
		f.Path = path8;
		f.Title = name8;

		ds.Files_Insert(f);

		//每个视频抓取10张图片
		int lastt = -1000;
		for(int i=0; i<10; i++)
		{
			//在时长范围内随机生成时间
			int t;
			for(int j=0; j<10; j++)//如果与上次结果太近，则重新随机，最多持续10次
			{
				t = tim>300 ? rand()%(tim-120) + 60 : rand()%tim  ;//对于大于五分钟的视频，开始和结尾的60s不要

				if(abs(t - lastt) > 60)
					break;
			}

			lastt = t;

			//生成图片
			VideoImage vimg;
			if(vs.getImage(path + filename, t, &vimg))
			{
				//将图片保存到数据库
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

		wprintf(L"添加文件:%s| 时长:%d | 路径| %s\n", filename.c_str(), tim, path.c_str());
	}
}