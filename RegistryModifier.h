#pragma once
#include <Windows.h>
#include <iostream>

class RegistryModifier
{
public:
	HKEY OpenRegistryKey(HKEY hRootKey, const char* strSubKey);
	void SetRegistryValuesDWord(HKEY hRootKey, LPCTSTR lpVal, DWORD data);
	void SetRegistryValues(HKEY hRootKey, LPCTSTR lpVal, LPCTSTR data, size_t size);
	void DeleteRegistryKeyAndConfirm(HKEY hRootKey, const char* strSubKey);
	DWORD GetValueFromRegistry(HKEY hRootKey, LPCTSTR lpValue);
};


