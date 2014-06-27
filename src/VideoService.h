#pragma once

#include <string>

class VideoImage
{
public:
	int sizeinbyte;
	char *buf;

	VideoImage();
	~VideoImage();
	void setBufSize(int size);
};

class VideoService
{
public:
	int getDuration(std::wstring filename);
	bool getImage(std::wstring filename, int time, VideoImage *vimg);

private:

};