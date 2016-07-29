#include "../include/camera.h"

void Camera::Update(){

	if (followingSprite && followingSprite->IsMoving()){

		SetPosition(followingSprite->GetX() - (Screen::Instance().GetWidth()/2), followingSprite->GetY() - (Screen::Instance().GetHeight() / 2));

	}
}

void Camera::SetPosition(double x, double y){

	if (x < boundx0){
		this->x = GetMinX();
	}
	else if (x > boundx1 - Screen::Instance().GetWidth()){
		this->x = GetMaxX();
	}
	else{
		this->x = x;
	}

	if (y < boundy0){
		this->y = GetMinY();
	}
	else if (y > boundy1 - Screen::Instance().GetHeight()){
		this->y = GetMaxY();
	}
	else{
		this->y = y;
	}
}
