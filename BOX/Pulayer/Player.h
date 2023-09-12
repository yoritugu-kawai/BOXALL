#pragma once
#include "BOX/BoxType.h"
#include "BOX/math/math.h"
#include "Input.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Player {
public:
	~Player();
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void box();

private:
	/*画像*/
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	/*操作キー*/
	Input* input_ = nullptr;
	//
	BoxType* RED = nullptr;
	std::list<BoxType*> REDs_[100];
	BoxType* BLUE = nullptr;
	std::list<BoxType*> BLUEs_;
	//
	XINPUT_STATE joyState;
	XINPUT_STATE prejoyState;
	int32_t tim = 20;
	Vector3 bulletOffset = {0.0f, 0.0f, 0.0f};
	bool ButtonReleased_ = true;

	bool bButtonReleased_ = true;

	bool lLetGo = true;
	bool rLetGo = true;

	uint32_t redBox_ = TextureManager::Load("red.png");
	float boxSpeedRed = 0.0f;
	bool redMove = true;
	int cut = 0;
	


	uint32_t blueBox_ = TextureManager::Load("blue.png");
	 float boxSpeedBulue = 0.0f;
	bool blueMove = true;
	 bool RL = true;
};
