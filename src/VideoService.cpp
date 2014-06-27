#include "VideoService.h"
#include <windows.h>

VideoImage::VideoImage()
{
	sizeinbyte = 0;
	buf = 0;
}

VideoImage::~VideoImage()
{
	if(buf != 0)
		delete[] buf;
}

void VideoImage::setBufSize(int size)
{
	if(buf != 0)
		delete[] buf;

	buf = new char[size];
	sizeinbyte = size;
}

int VideoService::getDuration(std::wstring filename)
{
	std::wstring strCmd = L"bin\\ffmpeg.exe -i \""+ filename + std::wstring(L"\"");//cmd命令
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL; //使用系统默认的安全描述符
	sa.bInheritHandle = TRUE; //创建的进程继承句柄

	if (!CreatePipe(&hRead,&hWrite,&sa,0)) //创建匿名管道
	{
		return -1;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si,sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite; //新创建进程的标准输出连在写管道一端
	si.wShowWindow = SW_HIDE; //隐藏窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	//char cmdline[200];
	//sprintf(cmdline,"%s",strCmd);

	if (!CreateProcess(NULL,(LPWSTR)strCmd.c_str(),NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) //创建子进程
	{
		return -1;
	}
	CloseHandle(hWrite); //关闭管道句柄

	char buffer[4096] = {0};
	DWORD bytesRead;

	std::string str = "";

	while (true)
	{
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL) //读取管道
			break;
		//strOutput += buffer;
		//UpdateWindow();
		//wprintf(L"%s", buffer);
		//printf("%s", (char*)buffer);
		str += buffer;
		Sleep(100);
	}
	CloseHandle(hRead);

	int duration = 0;
	//解析，获得Duration
	int pos = str.find("Duration:");
	if(pos != std::string::npos)
	{
		//printf("\n\n====Find %s", str.substr(pos+10, 20).c_str());
		//转换为时间格式
		int h, m, s;
		sscanf(str.substr(pos+10, 20).c_str(), "%d:%d:%d", &h, &m, &s);
		duration = h*3600 + m * 60 + s;
		printf("\nresult is %d, %d, %d, %d\n", h, m, s, duration);
	}

	return duration;
}

bool VideoService::getImage(std::wstring filename, int time, VideoImage *vimg)
{
	//删除之前的图片
	DeleteFile(L"tmp.jpg");

	//生成图片
	wchar_t aaa[20];
	wsprintf(aaa, L"%d", time);
	std::wstring strCmd = L"bin\\ffmpeg.exe -i \""+ filename + std::wstring(L"\" -y -ss ") + std::wstring(aaa) + std::wstring(L" -t 0.001 tmp.jpg");//cmd命令
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL; //使用系统默认的安全描述符
	sa.bInheritHandle = TRUE; //创建的进程继承句柄

	if (!CreatePipe(&hRead,&hWrite,&sa,0)) //创建匿名管道
	{
		return false;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si,sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite; //新创建进程的标准输出连在写管道一端
	si.wShowWindow = SW_HIDE; //隐藏窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	//char cmdline[200];
	//sprintf(cmdline,"%s",strCmd);

	if (!CreateProcess(NULL,(LPWSTR)strCmd.c_str(),NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) //创建子进程
	{
		return false;
	}
	CloseHandle(hWrite); //关闭管道句柄

	char buffer[4096] = {0};
	DWORD bytesRead;

	while (true)
	{
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL) //读取管道
			break;
		//strOutput += buffer;
		//UpdateWindow();
		//wprintf(L"%s", buffer);
		//printf("%s", (char*)buffer);
		//str += buffer;
		Sleep(100);
	}
	CloseHandle(hRead);

	//打开文件，将文件读入内存并返回
	FILE *fp = fopen("tmp.jpg", "rb");
	if(fp == 0)
		return false;

	//获取文件尺寸
	fseek(fp,0,SEEK_END);
	int size = ftell(fp);

	vimg->setBufSize(size);

	fseek(fp, 0,SEEK_SET);

	int nRead = 0;
	while(nRead < size)
	{
		nRead = fread(vimg->buf + nRead, 1, size - nRead, fp);
	}

	fclose(fp);

	return true;
}
