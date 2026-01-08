#pragma once
#include "Unit.h"

// セレクタのモード
enum SelectMode {
	SELECTOR,  // セレクタ単体で移動中
	UNIT      // ユニットを選択して移動中
};

class Selector {
private:
	// セレクタの位置情報
	int mapX_;     // マップ上のX座標
	int mapY_;     // マップ上のY座標
	int mapSize_;  // グリッド1マスのサイズ
	
	// セレクタの状態
	int selectMode_;  // 現在のモード
	
	// 包含するユニット
	Unit* units_;           // 全ユニットの配列へのポインタ
	int unitCount_;         // 全ユニットの数
	Unit* selectedUnit_;    // 現在選択中のユニット

public:
	Selector();
	
	// 初期化
	void Init();
	
	// 更新処理
	void Update();
	
	// 描画処理
	void Draw();
	
	// セレクタの移動
	void Move(int x, int y);
	
	// ユニット選択処理
	void SelectUnit();
	
	// ユニット配列の設定
	void SetUnits(Unit* units, int count) { 
		units_ = units; 
		unitCount_ = count;
	}
	
	// Getter各種
	int GetMapX() const { return mapX_; }
	int GetMapY() const { return mapY_; }
	int GetMapSize() const { return mapSize_; }
	int GetSelectMode() const { return selectMode_; }
	Unit* GetSelectedUnit() const { return selectedUnit_; }
	Unit* GetSelectedUnitAddress() { return selectedUnit_; }
	
	// Setter各種
	void SetMapX(int x) { mapX_ = x; }
	void SetMapY(int y) { mapY_ = y; }
	void SetSelectMode(int mode) { selectMode_ = mode; }
	void SetSelectedUnit(Unit* unit) { selectedUnit_ = unit; }
};
