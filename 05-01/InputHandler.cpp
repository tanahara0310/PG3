#include "InputHandler.h"
#include <Novice.h>

void InputHandler::AssignMoveLeftCommand2PressKeyA() {
	ICommand* command = new MoveLeftCommand();
	pressKeyA_ = command;
}

void InputHandler::AssignMoveRightCommand2PressKeyD() {
	ICommand* command = new MoveRightCommand();
	pressKeyD_ = command;
}

ICommand* InputHandler::HandleInput() {
	if (Novice::CheckHitKey(DIK_D)) {
		return pressKeyD_;
	}
	
	if (Novice::CheckHitKey(DIK_A)) {
		return pressKeyA_;
	}
	
	return nullptr;
}
