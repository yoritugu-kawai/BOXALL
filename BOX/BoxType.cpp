#include "BoxType.h"


void BoxType::Initialize(Model* model, Vector3& position, uint32_t textureHandle) {
	model_ = model;
	Box_ = textureHandle ;
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	
	worldTransform_.UpdateMatrix();
}


void BoxType::Update(Vector3 move) { 
	worldTransform_.UpdateMatrix();
	if (isShot == 0) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	}
	

}

void BoxType::Draw(const ViewProjection& viewProjection_) {

	model_->Draw(worldTransform_, viewProjection_, Box_); 

}

void BoxType::Stat() { isShot = 1; }
