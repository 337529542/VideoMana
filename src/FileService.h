#pragma once
#include <string>

class FileService_Notify
{
public:
	virtual void NotifyFind(std::wstring filename, std::wstring path) = 0;
};

class FileService
{
public:
	void setNotify(FileService_Notify *notify);
	void find(std::wstring rootpath);

private:
	FileService_Notify *n;
	
};