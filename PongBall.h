#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class PongBall : public CircleShape
{
public:
	const Vector2f initPosition; // 공의 초기 생성 위치
	const float ballSpeed;
	
	const Vector2f velocityBaseOffset;
	Vector2f velocity;

	int currentVerticalDirection;
	int currentHorizontalDirection;

	PongBall(Vector2f initPosition, float radius, float ballSpeed) : initPosition(initPosition), ballSpeed(ballSpeed), velocityBaseOffset(1.f, 1.f)
	{
		this->ResetPosition();
		this->setRadius(radius);
	}
	void ResetPosition()
	{
		this->setPosition(initPosition);
	}	
	void MoveBall(Vector2f velocityOffset, float deltaTime)
	{
		this->velocity = velocityBaseOffset;
		velocity.x *= velocityOffset.x * ballSpeed * deltaTime;
		velocity.y *= velocityOffset.y * ballSpeed * deltaTime;
		this->move(velocity);
	}
};

