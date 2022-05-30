#include <Windows.h>
#include <iostream>

HKEY OpenRegistryKey(HKEY hRootKey, const char* strSubKey)
{
	HKEY hKey;
	LONG lError = RegOpenKeyEx(hRootKey, strSubKey, NULL, KEY_ALL_ACCESS, &hKey);

	if (ERROR_FILE_NOT_FOUND == lError)
	{
		//Create a key
		//lError = RegCreateKeyEx(hRootKey, strSubKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		std::cout << "\nKey not found";
	}
	else 
		std::cout << "\nKey found";

	if (lError != ERROR_SUCCESS)
	{
		std::cout << "\nSomething is wrong. Could not Open or Create the Key";
	}

	return hKey;
}

void SetRegistryValuesDWord(HKEY hRootKey, LPCTSTR lpVal, DWORD data)
{
	LONG nErr = RegSetValueEx(hRootKey, lpVal, NULL, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));
	if (nErr != ERROR_SUCCESS)
	{
		std::cout << "\nNot able to set teh Registry Value.";
	}
}

void SetRegistryValues(HKEY hRootKey, LPCTSTR lpVal, LPCTSTR data,size_t size)
{
	LONG nErr = RegSetValueEx(hRootKey, lpVal, NULL, REG_SZ, (LPBYTE)data, size);
	if (nErr != ERROR_SUCCESS)
	{
		std::cout << "\nNot able to set the Registry Value.";
	}
	else
		std::cout << "\nAble to set the Registry Value.";
}

void DeleteRegistryKeyAndConfirm(HKEY hRootKey,const char* strSubKey)
{
	LONG lRes = RegDeleteKey(hRootKey, strSubKey);
	if (ERROR_SUCCESS == lRes)
	{
		MessageBox(NULL, "Key Successfully Deleted", "Delete Key", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(NULL, "Could Not Delete the Key", "Deletion Failed", MB_ICONINFORMATION);
	}
}

DWORD GetValueFromRegistry(HKEY hRootKey, LPCTSTR lpValue)
{
	DWORD data = 0;
	DWORD dtype = REG_DWORD;
	DWORD dSize = sizeof(data);
	LONG lErr = RegQueryValueEx(hRootKey, lpValue, NULL, &dtype, (LPBYTE)&data, &dSize);

	if (ERROR_SUCCESS != lErr)
	{
		std::cout << "\nCould Not find any Value.";
	}

	return data;
}

int main()
{
	//1. Open Registry Key.
		//a. If a key is already Present ? If yes, do nothing
		//else, Create a key ..
	HKEY hKey = OpenRegistryKey(HKEY_CURRENT_USER, "Control Panel\\Desktop");

	//DWORD dMyValue1, dMyValue2;
	
	LPCTSTR wallpaper = TEXT("C:\\Users\\52551\\Downloads\\wallpaper.png\0");

	//Get the Values
	//dMyValue1 = GetValueFromRegistry(hKey, "My_Value_1");
	//dMyValue2 = GetValueFromRegistry(hKey, "My_Value_2");

	//dMyValue1 += 11;
	//dMyValue2 += 9;

	//const

	SetRegistryValues(hKey, "Wallpaper", wallpaper, strlen(wallpaper) + 1);
	//SetRegistryValues(hKey, "My_Value_2", dMyValue2);

	//std::cout << "My_Value_1: " << dMyValue1 << std::endl;
	//std::cout << "My_Value_2: " << dMyValue2 << std::endl;

	//DeleteRegistryKeyAndConfirm(HKEY_LOCAL_MACHINE,  "SOFTWARE\\MyCompany");

	RegCloseKey(hKey);

	system("pause");

	return 0;
}