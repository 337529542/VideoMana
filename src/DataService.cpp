#include "DataService.h"

dbImage::dbImage()
{
	pbuf = 0;
	s = 0;
}

dbImage::~dbImage()
{
	if(pbuf != 0)
		delete [] pbuf;
}

void dbImage::setBufSize(int sizeinbyte)
{
	if(pbuf != 0)
		delete [] pbuf;

	pbuf = new char[sizeinbyte];
	s = sizeinbyte;
}

int dbImage::getBufSize()
{
	return s;
}


bool DataService::Open(char *filename)
{
	return sqlite.Open(filename);
}

bool DataService::Files_Insert(dbFiles f)
{
	SQLiteStatement* stmt = sqlite.Statement("insert into cy_files(FileName, Path, Title, Duration, InDate, Active, Show) values (?, ?, ?, ?, ?, ?, ?)");
	stmt->Bind(0, f.FileName);
	stmt->Bind(1, f.Path);
	stmt->Bind(2, f.Title);
	stmt->Bind(3, f.Duration);
	stmt->Bind(4, f.InDate);
	stmt->Bind(5, 1);
	stmt->Bind(6, 1);
	bool res = stmt->Execute();

	delete stmt;

	return res;
}

bool DataService::Files_Check(char *filename)
{
	bool res = false;
	std::string str;
	str = "select * from cy_files where FileName=\"" + std::string(filename) +  std::string("\" AND Active=1");
	SQLiteStatement* stmt = sqlite.Statement(str);
	if (stmt->NextRow())
	{
		res = true;
    }

	delete stmt;
	return res;
}

bool DataService::Files_UpdatePath(dbFiles f)
{
	return sqlite.DirectStatement(
		std::string("update cy_files set Path = \"")
		+ f.Path + std::string("\" where FileName=\"")
		+ f.FileName +std::string("\" AND Active=1"));
}

bool DataService::Files_DeActive(char *filename)
{
	return sqlite.DirectStatement(
		std::string("update cy_files set Active = 0 where FileName=\"")
		+ filename +std::string("\""));
}

bool DataService::Files_GetInfoByName(char* filename, dbFiles *pf)
{
	bool res = true;
	SQLiteStatement* stmt = sqlite.Statement(std::string("select * from cy_files where Active=1 AND FileName = \"") + filename + std::string("\""));

	if(stmt->NextRow())
	{
		pf->ID = stmt->ValueInt(0);
		pf->FileName = stmt->ValueString(1);
		pf->Path = stmt->ValueString(2);
		pf->Note = stmt->ValueString(3);
		pf->Title = stmt->ValueString(4);
		pf->Duration = stmt->ValueInt(5);
		pf->InDate = stmt->ValueInt(6);
		pf->Active = stmt->ValueInt(7);
		pf->Show = stmt->ValueInt(8);
	}
	else
	{
		res = false;
	}

	delete stmt;
	return res;
}

bool DataService::Files_GetInfoByNum(int num, dbFiles *pf)
{
	bool res = true;
	char buf[512];
	sprintf(buf,"select * from cy_files where Active=1 Order By ID desc limit %d, 1" ,num); 
	SQLiteStatement* stmt = sqlite.Statement(buf);

	if(stmt->NextRow())
	{
		pf->ID = stmt->ValueInt(0);
		pf->FileName = stmt->ValueString(1);
		pf->Path = stmt->ValueString(2);
		pf->Note = stmt->ValueString(3);
		pf->Title = stmt->ValueString(4);
		pf->Duration = stmt->ValueInt(5);
		pf->InDate = stmt->ValueInt(6);
		pf->Active = stmt->ValueInt(7);
		pf->Show = stmt->ValueInt(8);
	}
	else
	{
		res = false;
	}

	delete stmt;
	return res;
}

bool DataService::Img_Insert(dbImage *pImg)
{
	SQLiteStatement* stmt = sqlite.Statement("insert into cy_image(FileID, FileName, Time, Show, Data) values (?, ?, ?, ?, ?)");
	stmt->Bind(0, 0);
	stmt->Bind(1, pImg->FileName);
	stmt->Bind(2, pImg->Time);
	stmt->Bind(3, 1);
	stmt->BindBlob(4, pImg->getBufSize(), pImg->pbuf);
	bool res = stmt->Execute();
	delete stmt;

	return res;
}

bool DataService::Img_Get(char *filename, dbImage *pImg, int num)
{
	bool res = true;
	char buf[2048];
	sprintf(buf,"select * from cy_image where FileName = \"%s\" Order By ID asc limit %d, 1" , filename, num); 
	SQLiteStatement* stmt = sqlite.Statement(buf);

	if(stmt->NextRow())
	{
		pImg->FileName = stmt->ValueString(2);
		pImg->Time = stmt->ValueInt(3);
		pImg->setBufSize(stmt->ValueBlobSize(5));
		memcpy(pImg->pbuf, stmt->ValueBlob(5), stmt->ValueBlobSize(5));
		pImg->ID = stmt->ValueInt(0);
	}
	else
	{
		res = false;
	}

	delete stmt;
	return res;
}

bool DataService::Img_RemoveByFileName(char *filename)
{
	return sqlite.DirectStatement(
		std::string("delete from cy_image where FileName=\"")
		+ filename +std::string("\""));
}



