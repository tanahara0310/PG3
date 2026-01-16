#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>

std::mutex mtx;
std::vector<std::vector<int>> mapData;
bool isLoading = true;
bool loadComplete = false;

void CreateCSVFile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "CSVファイルの作成に失敗しました: " << filename << std::endl;
		return;
	}

	// サンプルマップデータを生成
	std::vector<std::vector<int>> sampleMap = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 2, 2, 2, 2, 2, 2, 0, 1},
		{1, 0, 2, 0, 0, 0, 0, 2, 0, 1},
		{1, 0, 2, 0, 3, 3, 0, 2, 0, 1},
		{1, 0, 2, 0, 3, 3, 0, 2, 0, 1},
		{1, 0, 2, 0, 0, 0, 0, 2, 0, 1},
		{1, 0, 2, 2, 2, 2, 2, 2, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	// CSVファイルに書き込み
	for (const auto& row : sampleMap) {
		for (size_t i = 0; i < row.size(); ++i) {
			file << row[i];
			if (i < row.size() - 1) {
				file << ",";
			}
		}
		file << "\n";
	}

	file.close();
	std::cout << "CSVファイルを生成しました: " << filename << std::endl;
}

void LoadCSVInBackground(const std::string& filename) {
	std::cout << " [スレッド] CSVファイルの読み込みを開始します..." << std::endl;
	
	// ファイル読み込みをシミュレート
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::lock_guard<std::mutex> lock(mtx);
		std::cerr << "[スレッド] CSVファイルを開けませんでした: " << filename << std::endl;
		isLoading = false;
		return;
	}

	std::vector<std::vector<int>> tempData;
	std::string line;

	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string value;

		while (std::getline(ss, value, ',')) {
			row.push_back(std::stoi(value));
		}
		tempData.push_back(row);

		// 読み込み中の進捗をシミュレート
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	file.close();

	// 排他制御を使用してデータを安全に更新
	{
		std::lock_guard<std::mutex> lock(mtx);
		mapData = tempData;
		loadComplete = true;
		isLoading = false;
	}

	std::cout << " [スレッド] CSVファイルの読み込みが完了しました" << std::endl;
}

void DisplayMap() {
	std::lock_guard<std::mutex> lock(mtx);
	
	if (mapData.empty()) {
		std::cout << "マップデータがありません" << std::endl;
		return;
	}

	std::cout << "\n=== マップチップ表示 ===" << std::endl;
	for (const auto& row : mapData) {
		for (int cell : row) {
			switch (cell) {
			case 0:
				std::cout << "  "; // 空白
				break;
			case 1:
				std::cout << "##";
				break;
			case 2:
				std::cout << "..";
				break;
			case 3:
				std::cout << "**";
				break;
			default:
				std::cout << "??";
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << "=====================\n" << std::endl;
}

void ShowLoadingAnimation() {
	const char animation[] = { '|', '/', '-', '\\' };
	int index = 0;

	while (true) {
		{
			std::lock_guard<std::mutex> lock(mtx);
			if (!isLoading) break;
		}

		std::cout << "\r読み込み中 " << animation[index % 4] << std::flush;
		index++;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "\r読み込み完了！    " << std::endl;
}

int main()
{
	const std::string csvFilename = "map_data.csv";

	std::cout << "=== マップチップ読み込みプログラム ===" << std::endl;
	std::cout << "std::threadを使用した並列処理デモ\n" << std::endl;

	// CSVファイルを生成
	CreateCSVFile(csvFilename);

	std::cout << "\nバックグラウンドでCSVを読み込みます...\n" << std::endl;

	// バックグラウンドでCSV読み込み
	std::thread loadThread(LoadCSVInBackground, csvFilename);

	// ローディングアニメーション表示
	std::thread animationThread(ShowLoadingAnimation);

	// スレッドの完了を待つ
	loadThread.join();
	animationThread.join();

	// マップを表示
	DisplayMap();

	std::cout << "プログラムを終了します。" << std::endl;

	return 0;
}