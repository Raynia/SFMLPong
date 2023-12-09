#pragma once

#include <SFML/Graphics.hpp>

#define DIRECTION_CHANGE -1

using namespace sf;

class PongBall : public CircleShape
{
public:
	const Vector2f initPosition; // 공의 초기 생성 위치
	const float ballSpeed;
	
	const Vector2f velocityBaseOffset;
	Vector2f velocity;

	PongBall(Vector2f initPosition, float radius, float ballSpeed) : initPosition(initPosition), ballSpeed(ballSpeed), velocityBaseOffset(1.6f, 1.0f)
	{
		this->ResetPosition();
		this->setRadius(radius);
	}
	void ResetPosition()
	{
		this->setPosition(initPosition);
	}	
	void MoveBall(int verticalDirction, int horizontalDirection, float deltaTime)
	{
		this->velocity = velocityBaseOffset;
		velocity.x *= horizontalDirection * ballSpeed * deltaTime;
		velocity.y *= verticalDirction * ballSpeed * deltaTime;
		this->move(velocity);
	}
};

