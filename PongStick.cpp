#include "PongStick.h"

PongStick::PongStick(Vector2f Position, int PlayerType) : PlayerType(PlayerType)
{
	this->setSize(Vector2f(defaultPongStickWidth, defaultPongStickHeight));
	this->setPosition(Position);
}

PongStick::PongStick(Vector2f Size, Vector2f Position, int PlayerType) :PlayerType(PlayerType)
{
	this->setSize(Size);
	this->setPosition(Position);
}

PongStick::~PongStick() {}

void PongStick::StickVerticalMove(int VerticalDirection, float DeltaTime)
{
	this->velocity = Vector2f(0.f, 0.f);
	this->velocity.y += static_cast<float>(StickSpeed) * VerticalDirection * DeltaTime;

	this->move(velocity);
}