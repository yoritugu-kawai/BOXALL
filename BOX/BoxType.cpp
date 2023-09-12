#include "BoxType.h"


void BoxType::Initialize(Model* model, Vector3& position, uint32_t textureHandle) {
	model_ = model;
	Box_ = textureHandle ;
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	
	worldTransform_.UpdateMatrix();
}


void BoxType::Update() { 
	worldTransform_.UpdateMatrix();
	Vector3 move = {0, 0, 0};
	float boxSpeed = 2.0f;
	move.y += boxSpeed;
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	

}



void BoxType::Draw(const ViewProjection& viewProjection_) {

	model_->Draw(worldTransform_, viewProjection_, Box_); 

}

void BoxType::Stat() { isShot = 1; }
