#include "FileService.h"
#include <windows.h>

void FileService::setNotify(FileService_Notify *notify)
{
	n = notify;
}

void FileService::find(std::wstring rootpath)
{
	std::wstring szfind;
	WIN32_FIND_DATA FindFileData;
	szfind = rootpath;
	szfind += L"*.*";
	HANDLE hFind=::FindFirstFile(szfind.c_str(),&FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
		return;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0]!=L'.')
			{
				std::wstring szfile = rootpath + std::wstring(FindFileData.cFileName) + std::wstring(L"\\");
				find(szfile);
			}
		}
		else
		{
			n->NotifyFind(FindFileData.cFileName, rootpath);
		}
		
		if(!FindNextFile(hFind,&FindFileData))
			break;
	}
	FindClose(hFind);
}

