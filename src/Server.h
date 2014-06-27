#pragma once
#include <string>
#include "DataService.h"
#include "FileService.h"
#include "VideoService.h"
#include "UniService.h"

class Server : public FileService_Notify
{
public:
	void run(std::wstring rootPath);

	virtual void NotifyFind(std::wstring filename, std::wstring path);

private:
	DataService ds;
	FileService fs;
	VideoService vs;
};