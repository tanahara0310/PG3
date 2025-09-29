#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>


/// @brief テキストファイルからアドレスを読み込む関数
/// @param filename　読み込む関数
/// @return アドレス格納された文字列
std::vector<std::string> LoadStudentAddress(const std::string& filename) {

	std::vector<std::string> addresses;
	std::ifstream file(filename);
	if (!file) {
		return addresses; // ファイルが開けなかった場合、空のベクターを返す
	}

	std::string line;
	while (getline(file, line)) {
		std::stringstream ss(line);
		std::string address;

		while (getline(ss, address, ',')) {
			if (!address.empty()) {
				addresses.push_back(address);
			}
		}

	}

	return addresses;
}

int main() {

	//ファイル読み込み
	std::vector<std::string> studentAddress = LoadStudentAddress("PG3_2025_01_02.txt");

	//昇順にソート
	std::sort(studentAddress.begin(), studentAddress.end());

	//読み込んだアドレスを表示
	for (const auto& addr : studentAddress) {

		std::cout << addr << std::endl;
	}

	return 0;
}