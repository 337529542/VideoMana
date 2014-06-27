#include "Server.h"

void wmain( int argc, wchar_t *argv[ ], wchar_t *envp[ ] )
{
	setlocale(LC_CTYPE, "");

	if(argc < 2)
	{
		wprintf(L"\n未指定扫描目录\n");
		return;
	}

	Server app;
	app.run(argv[1]);

	system("pause");
}

















//#include "DataService.h"
//#include "FileService.h"
//#include "VideoService.h"
//#include "UniService.h"
//#include <iostream>
//#include <windows.h>


//DataService ds;
//FileService fs;
//VideoService vs;
//
//class abc : public FileService_Notify
//{
//public:
//	virtual void NotifyFind(std::wstring filename, std::wstring path)
//	{
//		wprintf(L"%s  ||  %s\n", path.c_str(), filename.c_str());
//	}
//};
//
//abc myabc;
//
//void main()
//{
//	printf("helloworld\n");
//	ds.Open("MediaData");
//	
//	dbFiles f;
//	f.Duration = 20;
//	f.FileName = "te  st.wmv";
//	f.InDate = 12345678;
//	f.Path = "tes  tpath/";
//	f.Title = "tit  le1";
//
//	//ds.Files_Insert(f);
//	//ds.Files_Check("te  st.wmv");
//	//ds.Files_Check("1test.wmv");
//	//ds.Files_UpdatePath(f);
//	//ds.Files_DeActive("te  st.wmv");
//	//ds.Files_GetInfoByName("test.wmv", &f);
//	//ds.Files_GetInfoByNum(1, &f);
//
//	dbImage img;
//	//img.setBufSize(1000);
//	//img.FileName = "te st.wmv";
//	//img.Time = 10;
//
//	//ds.Img_Insert(&img);
//	//ds.Img_Get("te st.wmv", &img, 0);
//	//ds.Img_RemoveByFileName("te st.wmv");
//
//	//fs.setNotify(&myabc);
//	//fs.find(L"D:\\proj\\VideoMana\\");
//	//vs.getDuration(L"D:\\迅雷下载\\私人空间\\[克里斯·波提].Chris.Botti.in.Boston.2008.x264.AC3-WAF\\Chris.Botti.in.Boston.2008.x264.AC3-WAF.mkv");
//	//vs.getDuration(L"D:\\迅雷下载\\私人空间\\Josh Groban - Awake Live\\Awake Live CD\\02. JOSH GROBAN.mp3");
//	/*VideoImage vimg;
//	vs.getImage(L"D:\\迅雷下载\\私人空间\\[克里斯·波提].Chris.Botti.in.Boston.2008.x264.AC3-WAF\\Chris.Botti.in.Boston.2008.x264.AC3-WAF.mkv"
//		,50, &vimg);
//
//	FILE *fp = fopen("t.jpg", "wb");
//	int nWrite = 0;
//	while(nWrite < vimg.sizeinbyte)
//	{
//		nWrite = fwrite(vimg.buf+nWrite, 1, vimg.sizeinbyte - nWrite, fp);
//	}
//	fclose(fp);*/
//
//
//
//	system("pause");
//}