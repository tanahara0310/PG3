#pragma once
#include "IScene.h"

struct Player {
	float x;
	float y;
	float radius;
	int color;
};

struct Enemy {
	float x;
	float y;
	float radius;
	int color;
	bool isAlive;
};

struct Bullet {
	float x;
	float y;
	float radius;
	float speed;
	int color;
	bool isAlive;
};

class StageScene : public IScene {
public:
	StageScene();
	~StageScene() override = default;

	void Update(char* keys, char* preKeys) override;
	void Draw() override;
	SceneType GetNextScene() const override;
	bool IsFinished() const override;

private:
	void UpdatePlayer(char* keys, char* preKeys);
	void UpdateBullets();
	void UpdateEnemy();
	void CheckCollisions();
	float Distance(float x1, float y1, float x2, float y2);

	Player player_;
	static const int kMaxBullets = 10;
	Bullet bullets_[kMaxBullets];
	Enemy enemy_;
	
	float enemySpeed_;
	float enemyDirection_;
	
	bool isFinished_;
	SceneType nextScene_;
};
