#include "pch.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <random>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <iterator>
#include <Wincrypt.h>
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "\r\nUSAGE:\t\t\tfsGenCPP.exe rootPath objectCount size\r\n\r\n\tEXAMPLE:\t\tfsGenCPP.exe C:\\testDir 10000 random\r\n\r\n\tEXAMPLE:\t\tfsGenCPP.exe D:\\testDir 500000 100\r\n";
	}
	else
	{
		vector <string> dirs;
		dirs.push_back(argv[1]);
		vector <string> fileExts{ "txt","exe","jpg","docx","mp3","mp4" };
		mt19937 rnd{ random_device()() };
		int count = stoi(argv[2]);
		string mode = argv[3];
		if (mode.compare("random") == 0)
		{
			for (int a = 0; a < count; a = a + 1)
			{
				if (uniform_int_distribution<>(1, 41)(rnd) <= 3)
				{
					string base = dirs[uniform_int_distribution<>(0, dirs.size() - 1)(rnd)];
					string newDir = base + "\\" + to_string(a);
					CreateDirectoryA(("\\\\?\\" + newDir).c_str(), NULL);
					dirs.push_back(newDir);
				}
				else
				{
					string base = dirs[rand() % dirs.size()];
					string newFile = base + "\\" + to_string(a) + "." + fileExts[uniform_int_distribution<>(0, fileExts.size() - 1)(rnd)];

					int size = uniform_int_distribution<>(1024, 1024000)(rnd);
					if (size > 1022000)
					{
						size = uniform_int_distribution<>(1024, 1024000000)(rnd);
					}
					_LARGE_INTEGER li;
					li.QuadPart = size;
					HANDLE fh = CreateFileA(("\\\\?\\" + newFile).c_str(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
					SetFilePointerEx(fh, li, NULL, FILE_BEGIN);
					SetEndOfFile(fh);
				}
				cout << to_string(a) << endl;
			}
		}
		else
		{
			int size = stoi(argv[3]);
			for (int a = 0; a < count; a = a + 1)
			{
				if (uniform_int_distribution<>(1, 41)(rnd) <= 3)
				{
					string base = dirs[uniform_int_distribution<>(0, dirs.size() - 1)(rnd)];
					string newDir = base + "\\" + to_string(a);
					CreateDirectoryA(("\\\\?\\" + newDir).c_str(), NULL);
					dirs.push_back(newDir);
				}
				else
				{
					string base = dirs[rand() % dirs.size()];
					string newFile = base + "\\" + to_string(a) + "." + fileExts[uniform_int_distribution<>(0, fileExts.size() - 1)(rnd)];
					_LARGE_INTEGER li;
					li.QuadPart = size;
					HANDLE fh = CreateFileA(("\\\\?\\" + newFile).c_str(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
					SetFilePointerEx(fh, li, NULL, FILE_BEGIN);
					SetEndOfFile(fh);
				}
				cout << to_string(a) << endl;
			}
		}
	}
}
