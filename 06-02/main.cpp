#include <Novice.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>

const char kWindowTitle[] = "学籍番号";

std::mutex mtx;
std::vector<std::vector<int>> mapData;
bool isLoading = true;
bool loadComplete = false;
int loadingFrame = 0;

void CreateCSVFile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
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
}

void LoadCSVInBackground(const std::string& filename) {
	// ファイル読み込みをシミュレート
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::lock_guard<std::mutex> lock(mtx);
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
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	const std::string csvFilename = "map_data.csv";
	const int TILE_SIZE = 50;
	const int MAP_OFFSET_X = 340;
	const int MAP_OFFSET_Y = 110;

	// CSVファイルを生成
	CreateCSVFile(csvFilename);

	// バックグラウンドでCSV読み込み開始
	std::thread loadThread(LoadCSVInBackground, csvFilename);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		{
			std::lock_guard<std::mutex> lock(mtx);
			if (isLoading) {
				loadingFrame++;
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// タイトル表示
		Novice::ScreenPrintf(10, 10, "=== Map Chip Loader with std::thread ===");

		bool currentlyLoading = false;
		bool currentlyComplete = false;
		{
			std::lock_guard<std::mutex> lock(mtx);
			currentlyLoading = isLoading;
			currentlyComplete = loadComplete;
		}

		if (currentlyLoading) {
			// ローディングアニメーション
			const char* animation[] = { "|", "/", "-", "\\" };
			int animIndex = (loadingFrame / 10) % 4;

			Novice::ScreenPrintf(10, 50, "Loading... %s", animation[animIndex]);
			Novice::ScreenPrintf(10, 80, "Reading CSV file in background...");
		} else if (currentlyComplete) {
			Novice::ScreenPrintf(10, 50, "Loading Complete!");

			// マップデータを描画
			{
				std::lock_guard<std::mutex> lock(mtx);

				if (!mapData.empty()) {
					for (size_t y = 0; y < mapData.size(); ++y) {
						for (size_t x = 0; x < mapData[y].size(); ++x) {
							int drawX = MAP_OFFSET_X + static_cast<int>(x) * TILE_SIZE;
							int drawY = MAP_OFFSET_Y + static_cast<int>(y) * TILE_SIZE;

							unsigned int color = 0x000000FF;

							switch (mapData[y][x]) {
							case 0: // 空白
								color = 0xFFFFFFFF;
								break;
							case 1: // 壁
								color = 0x333333FF;
								break;
							case 2: // 道
								color = 0xCCCCCCFF;
								break;
							case 3: // 特殊
								color = 0xFF6600FF;
								break;
							default:
								color = 0xFF00FFFF;
								break;
							}

							Novice::DrawBox(drawX, drawY, TILE_SIZE, TILE_SIZE, 0.0f, color, kFillModeSolid);
							Novice::DrawBox(drawX, drawY, TILE_SIZE, TILE_SIZE, 0.0f, 0x000000FF, kFillModeWireFrame);
						}
					}
				}
			}

			// 凡例表示
			Novice::ScreenPrintf(10, 80, "Legend:");
			Novice::DrawBox(20, 110, 30, 30, 0.0f, 0xFFFFFFFF, kFillModeSolid);
			Novice::DrawBox(20, 110, 30, 30, 0.0f, 0x000000FF, kFillModeWireFrame);
			Novice::ScreenPrintf(60, 115, "0: Empty");

			Novice::DrawBox(20, 150, 30, 30, 0.0f, 0x333333FF, kFillModeSolid);
			Novice::DrawBox(20, 150, 30, 30, 0.0f, 0x000000FF, kFillModeWireFrame);
			Novice::ScreenPrintf(60, 155, "1: Wall");

			Novice::DrawBox(20, 190, 30, 30, 0.0f, 0xCCCCCCFF, kFillModeSolid);
			Novice::DrawBox(20, 190, 30, 30, 0.0f, 0x000000FF, kFillModeWireFrame);
			Novice::ScreenPrintf(60, 195, "2: Path");

			Novice::DrawBox(20, 230, 30, 30, 0.0f, 0xFF6600FF, kFillModeSolid);
			Novice::DrawBox(20, 230, 30, 30, 0.0f, 0x000000FF, kFillModeWireFrame);
			Novice::ScreenPrintf(60, 235, "3: Special");
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// スレッドの完了を待つ
	if (loadThread.joinable()) {
		loadThread.join();
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
