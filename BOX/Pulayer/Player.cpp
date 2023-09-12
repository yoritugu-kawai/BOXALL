
#include "BOX/Pulayer/Player.h"
#include <ImGuiManager.h>
#include <cassert>
Player::~Player() {
	for (int i = 0; i > 100; i++) {
	for (BoxType* box : REDs_[i]) {
		delete box;
	}
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	/*画像*/
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}
void Player::box() {
	if (tim <= 0) {
		if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
			return;
		}
		// 赤
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			redMove = true;
			blueMove = false;
			// boxSpeedRed = 0.0f;
			tim2 = 20;
			// 右
			if (rLetGo == true) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
					lLetGo = false;
					if (bButtonReleased_) {
						BoxType* boxRed_ = new BoxType;
						bulletOffset.x += 2.0f;
						// 弾の位置を計算してオフセットを適用
						Vector3 bulletPosition = Add(worldTransform_.translation_, bulletOffset);

						boxRed_->Initialize(model_, bulletPosition, redBox_);
						for (int i = 0; i > 100; i++) {
							REDs_[i].push_back(boxRed_);
						}
						bButtonReleased_ = false; // 十字キーが押されたことを記録
						tim = 20;
					}
				} else {
					bButtonReleased_ = true; // 十字キーがリリースされたことを記録
				}
			}
			// 左
			if (lLetGo == true) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
					rLetGo = false;
					if (bButtonReleased_) {
						BoxType* boxRed_ = new BoxType;
						bulletOffset.x -= 2.0f;
						// 弾の位置を計算してオフセットを適用
						Vector3 bulletPosition = Add(worldTransform_.translation_, bulletOffset);

						boxRed_->Initialize(model_, bulletPosition, redBox_);
						for (int i = 0; i > 100; i++) {
							REDs_[i].push_back(boxRed_);
						}
						bButtonReleased_ = false; // 十字キーが押されたことを記録
						tim = 20;
					}
				} else {
					bButtonReleased_ = true; // 十字キーがリリースされたことを記録
				}
			}

		}
		// 動き
		else {
			if (redMove == true) {

				lLetGo = true;
				rLetGo = true;
				bulletOffset.x = 0.0f;
				tim2--;
				// boxSpeedRed = 2.0f;
			}
		}
		// 青
		// if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		//	blueMove = true;
		//	redMove = false;
		//	boxSpeedBulue = 0.0f;
		//	// 右
		//	if (rLetGo == true) {
		//		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		//			lLetGo = false;
		//			if (bButtonReleased_) {
		//				BoxType* boxBlue_ = new BoxType;
		//				bulletOffset.x += 2.0f;
		//				// 弾の位置を計算してオフセットを適用
		//				Vector3 bulletPosition = Add(worldTransform_.translation_, bulletOffset);

		//				boxBlue_->Initialize(model_, bulletPosition, blueBox_);

		//				BLUEs_.push_back(boxBlue_);
		//				bButtonReleased_ = false; // 十字キーが押されたことを記録
		//				tim = 20;
		//			}
		//		} else {
		//			bButtonReleased_ = true;// 十字キーがリリースされたことを記録
		//			RL = true;
		//		}
		//	}
		//	// 左
		//	if (lLetGo == true) {
		//		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		//			rLetGo = false;
		//			if (bButtonReleased_) {
		//				BoxType* boxBlue_ = new BoxType;
		//				bulletOffset.x -= 2.0f;
		//				// 弾の位置を計算してオフセットを適用
		//				Vector3 bulletPosition = Add(worldTransform_.translation_, bulletOffset);

		//				boxBlue_->Initialize(model_, bulletPosition, blueBox_);

		//				BLUEs_.push_back(boxBlue_);
		//				bButtonReleased_ = false; // 十字キーボタンが押されたことを記録
		//				tim = 20;
		//			}
		//		} else {
		//			bButtonReleased_ = true; // 十字キーがリリースされたことを記録
		//			RL = false;
		//		}
		//	}

		//}
		//// 動き
		// else {
		//	if (blueMove == true) {

		//		lLetGo = true;
		//		rLetGo = true;
		//		bulletOffset.x = 0.0f;
		//		boxSpeedBulue = 2.0f;
		//	}
		//}
	}
}

void Player::Update() {
	/*画像*/
	worldTransform_.TransferMatrix();
	/*操作キー*/
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	float inputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbRY / SHRT_MAX * kCharacterSpeed;
	}
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 移動制限
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 18;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	/*弾*/
	box();
	tim--;

	// 赤
	if (tim2 <= 0) {
		for (int i = 0; i > 100; i++) {
			for (BoxType* box : REDs_[i]) {
				box->Update();
			}
		}
	}
	//// 青
	// Vector3 moveBoxBulue = {0, 0, 0};
	//
	// moveBoxBulue.x += boxSpeedBulue;
	//
	// for (BoxType* box : BLUEs_) {
	//	box->Update(moveBoxBulue);
	// }
	//
}

void Player::Draw(ViewProjection viewProjection_) {
	/*画像*/
	model_->Draw(this->worldTransform_, viewProjection_, this->textureHandle_);
	/*操作キー*/
	input_ = Input::GetInstance();
	/*弾*/
	for (int i = 0; i > 100; i++) {
		for (BoxType* box : REDs_[i]) {
			box->Draw(viewProjection_);
		}
	}
	for (BoxType* box : BLUEs_) {
		box->Draw(viewProjection_);
	}
}
