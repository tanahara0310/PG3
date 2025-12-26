#include "Player.h"
#include <Novice.h>

Player::Player() {
	pos_.x = 640.0f;
	pos_.y = 360.0f;
	speed_ = 5.0f;
}

void Player::Init() {
	pos_.x = 640.0f;
	pos_.y = 360.0f;
	speed_ = 5.0f;
}

void Player::Update() {

}

void Player::Draw() {
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, 30, 30, 0.0f, WHITE, kFillModeSolid);
}

void Player::MoveRight() {
	pos_.x += speed_;
}

void Player::MoveLeft() {
	pos_.x -= speed_;
}
