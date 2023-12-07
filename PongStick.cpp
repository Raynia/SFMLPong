#include "PongStick.h"

int PongStick::PlayerCount = 0;

PongStick::PongStick() {}

PongStick::PongStick(Vector2f Position, Vector2f Size)
	: StickPosition(Position), StickSize(Size)
{
	this->setPosition(Position);
	this->setSize(Size);
}

PongStick::~PongStick() {}

void PongStick::StickVerticalMove(int VerticalDirection, float DeltaTime)
{
	this->velocity = Vector2f(0.f, 0.f);
	this->velocity.y += static_cast<float>(StickSpeed) * VerticalDirection * DeltaTime;

	this->move(velocity);
}