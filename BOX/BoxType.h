#pragma once
#include "BOX/math/math.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class BoxType {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Vector3& position, uint32_t textureHandle);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>

	void Update(Vector3 move);
	/// <summary>
	/// 画像
	/// </summary>
	void Draw(const ViewProjection& viewProjection_);
	/// <summary>
	///
	/// </summary>
	void Stat();

private:
	uint32_t Box_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	XINPUT_STATE joyState;
	bool isShot = 0;
};
