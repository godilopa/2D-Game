#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(){}

Sprite::Sprite(Image* image) : image(image) {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->colx = 0;
	this->coly = 0;
	this->colwidth = 0;
	this->colheight = 0;
	this->angle = 0;
	this->scalex = 1;
	this->scaley = 1;
	this->radius = 0;
	this->animFPS = 32;
	this->firstFrame = 0;
	this->lastFrame = 0;
	this->currentFrame = 0;
	this->blendMode = Renderer::ALPHA;
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->collision = nullptr;
	this->colPixelData = nullptr;
	this->colSprite = nullptr;
	this->collided = false;

	this->userData = nullptr;
}


Sprite::~Sprite() {
    // TAREA: Implementar
}

//void Sprite::SetCollision(CollisionMode mode) {
//	// TAREA: Implementar
//}
//
//bool Sprite::CheckCollision(Sprite* sprite) {
//	// TAREA: Implementar
//}
//
//bool Sprite::CheckCollision(const Map* map) {
//	// TAREA: Implementar
//}
//
void Sprite::RotateTo(int32 angle, double speed) {
	if (WrapValue(GetAngle(),360) == WrapValue(angle,360) || speed == 0) {
		rotating = false;
	}
	else {
		rotating = true;
		double ccw = WrapValue(angle - GetAngle(), 360);
		double cw = WrapValue(GetAngle() - angle, 360);
		if (ccw <= cw) {
			degreesToRotate = ccw;
			rotatingSpeed = abs(speed);
		}
		else {
			degreesToRotate = cw;
			rotatingSpeed = -abs(speed);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speed) {
	if (x == GetX() && y == GetY()|| speed == 0) {
		moving = false;
	}
	else {
		moving = true;
		endX = x;
		endY = y;
		vector.x = x - GetX();
		vector.y = y - GetY();
		distancia = sqrt((vector.x * vector.x) + (vector.y * vector.y));
		vectorNormalizado.x = vector.x / distancia;
		vectorNormalizado.y = vector.y / distancia;
		movingSpeedX = vectorNormalizado.x * speed;
		movingSpeedY = vectorNormalizado.y * speed;
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	/*colSprite = NULL;
	collided = false;*/

	// TAREA: Actualizar animacion
	if (currentFrame){
		currentFrame += animFPS * elapsed;
		if (currentFrame > lastFrame) {
			currentFrame -= (lastFrame - firstFrame); //o = firstFrame (pero velocidad no lineal);
		}
		if (currentFrame < firstFrame){
			currentFrame += (firstFrame - lastFrame); // o = lastFrame(pero velocidad no lineal);
		}
	}

	// TAREA: Actualizar rotacion animada
	if (IsRotating()) {
		double e = rotatingSpeed * elapsed;
		degreesToRotate -= abs(e);
		if (degreesToRotate <= 0){
			rotating = false;
			SetAngle(GetAngle() + (e - degreesToRotate)); //sumamos lo que le falta para llegar
		}
		else {
			SetAngle(GetAngle() + e);
		}
	}

	// TAREA: Actualizar movimiento animado
	if (IsMoving()){
		double eX = movingSpeedX * elapsed;
		double eY = movingSpeedY * elapsed;
		if (eX > 0){
			if (GetX() + eX > endX){
				moving = false;
				SetX(endX);
				SetY(endY);
			}
			else{
				SetPosition(GetX() + eX, GetY() + eY);
			}
		}

		if (eX < 0){
			if (GetX() + eX < endX){
				moving = false;
				SetX(endX);
				SetY(endY);
			}
			else{
				SetPosition(GetX() + eX, GetY() + eY);
			}
		}

		if (eX == 0){
			if (eY > 0){
				if (GetY() + eY > endY){
					moving = false;
					SetY(endY);
				}
				else{
					SetPosition(GetX() + eX, GetY() + eY);
				}
			}

			if (eY < 0){
				if (GetY() + eY < endY){
					moving = false;
					SetY(endY);
				}
				else{
					SetPosition(GetX() + eX, GetY() + eY);
				}
			}
		}
	}

	// Informacion final de colision
	/*UpdateCollisionBox();*/
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(blendMode);
	Renderer::Instance().SetColor(r, g, b, a);
	Renderer::Instance().DrawImage(image, x, y, currentFrame, image->GetWidth()*scalex, image->GetHeight()*scaley, GetAngle());
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
