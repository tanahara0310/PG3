#include "StageScene.h"
#include <Novice.h>
#include <cmath>

StageScene::StageScene()
	: isFinished_(false), nextScene_(SceneType::Stage) {

	player_.x = 640.0f;
	player_.y = 600.0f;
	player_.radius = 20.0f;
	player_.color = 0x00FF00FF;

	for (int i = 0; i < kMaxBullets; i++) {
		bullets_[i].isAlive = false;
		bullets_[i].radius = 5.0f;
		bullets_[i].speed = 10.0f;
		bullets_[i].color = 0xFFFF00FF;
	}

	enemy_.x = 640.0f;
	enemy_.y = 100.0f;
	enemy_.radius = 25.0f;
	enemy_.color = 0xFF0000FF;
	enemy_.isAlive = true;

	enemySpeed_ = 3.0f;
	enemyDirection_ = 1.0f;
}

void StageScene::Update(char* keys, char* preKeys) {
	UpdatePlayer(keys, preKeys);
	UpdateBullets();
	UpdateEnemy();
	CheckCollisions();

	if (!enemy_.isAlive) {
		isFinished_ = true;
		nextScene_ = SceneType::Clear;
	}
}

void StageScene::UpdatePlayer(char* keys, char* preKeys) {
	const float speed = 5.0f;

	if (keys[DIK_A] != 0 && player_.x > player_.radius) {
		player_.x -= speed;
	}
	if (keys[DIK_D] != 0 && player_.x < 1280 - player_.radius) {
		player_.x += speed;
	}
	if (keys[DIK_W] != 0 && player_.y > player_.radius) {
		player_.y -= speed;
	}
	if (keys[DIK_S] != 0 && player_.y < 720 - player_.radius) {
		player_.y += speed;
	}

	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		for (int i = 0; i < kMaxBullets; i++) {
			if (!bullets_[i].isAlive) {
				bullets_[i].x = player_.x;
				bullets_[i].y = player_.y;
				bullets_[i].isAlive = true;
				break;
			}
		}
	}
}

void StageScene::UpdateBullets() {
	for (int i = 0; i < kMaxBullets; i++) {
		if (bullets_[i].isAlive) {
			bullets_[i].y -= bullets_[i].speed;
			if (bullets_[i].y < 0) {
				bullets_[i].isAlive = false;
			}
		}
	}
}

void StageScene::UpdateEnemy() {
	if (enemy_.isAlive) {
		enemy_.x += enemySpeed_ * enemyDirection_;

		if (enemy_.x <= enemy_.radius) {
			enemy_.x = enemy_.radius;
			enemyDirection_ = 1.0f;
		} else if (enemy_.x >= 1280 - enemy_.radius) {
			enemy_.x = 1280 - enemy_.radius;
			enemyDirection_ = -1.0f;
		}
	}
}

void StageScene::CheckCollisions() {
	if (!enemy_.isAlive) return;

	for (int i = 0; i < kMaxBullets; i++) {
		if (!bullets_[i].isAlive) continue;

		float dist = Distance(bullets_[i].x, bullets_[i].y, enemy_.x, enemy_.y);
		if (dist < bullets_[i].radius + enemy_.radius) {
			bullets_[i].isAlive = false;
			enemy_.isAlive = false;
		}
	}
}

float StageScene::Distance(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrtf(dx * dx + dy * dy);
}

void StageScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000033FF, kFillModeSolid);
	Novice::ScreenPrintf(10, 10, "Scene: STAGE");
	Novice::ScreenPrintf(10, 30, "Enemy: %s", enemy_.isAlive ? "Alive" : "Defeated");
	Novice::ScreenPrintf(10, 50, "WASD: Move, SPACE: Shoot");

	Novice::DrawEllipse(
		static_cast<int>(player_.x),
		static_cast<int>(player_.y),
		static_cast<int>(player_.radius),
		static_cast<int>(player_.radius),
		0.0f, player_.color, kFillModeSolid
	);

	for (int i = 0; i < kMaxBullets; i++) {
		if (bullets_[i].isAlive) {
			Novice::DrawEllipse(
				static_cast<int>(bullets_[i].x),
				static_cast<int>(bullets_[i].y),
				static_cast<int>(bullets_[i].radius),
				static_cast<int>(bullets_[i].radius),
				0.0f, bullets_[i].color, kFillModeSolid
			);
		}
	}

	if (enemy_.isAlive) {
		Novice::DrawEllipse(
			static_cast<int>(enemy_.x),
			static_cast<int>(enemy_.y),
			static_cast<int>(enemy_.radius),
			static_cast<int>(enemy_.radius),
			0.0f, enemy_.color, kFillModeSolid
		);
	}
}

SceneType StageScene::GetNextScene() const {
	return nextScene_;
}

bool StageScene::IsFinished() const {
	return isFinished_;
}
