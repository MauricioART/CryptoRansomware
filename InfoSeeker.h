#pragma once
#pragma comment(lib, "iphlpapi.lib")
#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <string>
#include <lmcons.h>
#include <iostream>

class InfoSeeker
{
private:
	std::string macAddress;
	std::string userName;
public:
	char* getMAC();
	std::string getUserName();
	std::string getMacAddress() { return this->macAddress; }
};

