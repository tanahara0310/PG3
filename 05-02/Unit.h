#pragma once

// 前方宣言
class Selector;

class Unit {
private:
	// ユニットの位置情報
	int mapX_ = 0;      // マップ上のX座標（グリッド単位）
	int mapY_ = 0;      // マップ上のY座標（グリッド単位）
	int mapSize_ = 32;  // グリッド1マスのサイズ（ピクセル）
	
	// ユニットの識別情報
	int id_ = 0;  // ユニットの固有ID
	
	// ユニットの状態
	bool isSelected_ = false;  // 選択されているかどうか

public:
	// デフォルトコンストラクタ
	Unit() = default;
	
	// 初期化処理
	void Init(int idxerI);
	
	// 更新処理
	void Update();
	
	// 描画処理
	void Draw();
	
	// 移動処理
	void Move(int x, int y);
	
	// Getter各種
	int GetMapX() const { return mapX_; }
	int GetMapY() const { return mapY_; }
	int GetMapSize() const { return mapSize_; }
	int GetId() const { return id_; }
	bool GetIsSelected() const { return isSelected_; }
	
	// Setter各種
	void SetMapX(int x) { mapX_ = x; }
	void SetMapY(int y) { mapY_ = y; }
	void SetIsSelected(bool selected) { isSelected_ = selected; }
};
