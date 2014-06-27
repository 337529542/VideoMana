#pragma once

#include <windows.h>
#include <string>

class UniService
{
public:
	static std::wstring ANSI2Unicode(const std::string & strin)
            {
                std::wstring strout;

                // 预计算所需空间大小（已包含结束字符）,单位wchar_t
                int dwNum = MultiByteToWideChar (CP_ACP, 0,strin.c_str(), -1, 0 , 0);
                wchar_t * pBuffer = new wchar_t[dwNum];
                if (!pBuffer)
                {
                    return strout;
                }
                memset(pBuffer,0,(dwNum)*sizeof(wchar_t));

                if(MultiByteToWideChar(CP_ACP, 0, strin.c_str(),-1,pBuffer,dwNum) >= 0)
                {
                    strout = pBuffer;
                }

                delete[] pBuffer;
                return strout;
            }

static std::string  Unicode2UTF8(const std::wstring & strin)
            {
                std::string strout;

                //测试所需存储空间大小（已包含结束字符）,单位char
                int dwNum = WideCharToMultiByte(CP_UTF8,0,strin.c_str(),-1,0,0,0,0);
                char* pBuffer = new char[dwNum];
                if (!pBuffer)
                {
                    return strout;
                }
                memset(pBuffer,0,dwNum);
               
                if(WideCharToMultiByte(CP_UTF8,0,strin.c_str(),-1,pBuffer,dwNum,0,0) >= 0)
                {
                    strout = pBuffer;
                }

                delete[] pBuffer;
                return strout;
            }

static std::string  ANSI2UTF8(const std::string & strin)
            {
                return Unicode2UTF8(ANSI2Unicode(strin));
            }

static std::string  Unicode2ANSI(const std::wstring & strin)
            {
                std::string strout;

                //测试所需存储空间大小（已包含结束字符）,单位char
                int dwNum = WideCharToMultiByte(CP_ACP,0,strin.c_str(),-1,0,0,0,0);
                char* pBuffer = new char[dwNum];
                if (!pBuffer)
                {
                    return strout;
                }
                memset(pBuffer,0,dwNum);

                BOOL use_def_char = FALSE;
                if(WideCharToMultiByte(CP_ACP,0,strin.c_str(),-1,pBuffer,dwNum,"?",&use_def_char) >= 0)
                {
                    strout = pBuffer;
                }

                delete[] pBuffer;
                return strout;
            }

static std::wstring UTF82Unicode(const std::string & strin)
            {
                std::wstring strout;

                // 预计算所需空间大小（已包含结束字符）,单位wchar_t
                int dwNum = MultiByteToWideChar (CP_UTF8, 0,strin.c_str(), -1, 0 , 0);
                wchar_t* pBuffer = new wchar_t[dwNum];
                if (!pBuffer)
                {
                    return strout;
                }
                memset(pBuffer,0,dwNum*sizeof(wchar_t));

                if(MultiByteToWideChar(CP_UTF8,0,strin.c_str(),-1,pBuffer,dwNum) >= 0)
                {
                    strout = pBuffer;
                }

                delete[] pBuffer;
                return strout;
            }

static std::string  UTF82ANSI(const std::string & strin)
            {
                return Unicode2ANSI(UTF82Unicode(strin));
            }

};