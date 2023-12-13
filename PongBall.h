#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class PongBall : public CircleShape
{
public:
	const Vector2f initPosition; // 공의 초기 생성 위치
	const float ballSpeed; // 공의 속도
	
	const Vector2f velocityBaseOffset; // 공의 속도 오프셋 기본값
	Vector2f velocity; // 공의 속도

	PongBall(Vector2f initPosition, float radius, float ballSpeed) : initPosition(initPosition), ballSpeed(ballSpeed), velocityBaseOffset(1.f, 1.f)
	{
		this->ResetPosition();
		this->setRadius(radius);
	}
	// 공의 위치 초기화
	void ResetPosition()
	{
		this->setPosition(initPosition);
	}	
	// 공 위치 이동
	void MoveBall(Vector2f velocityOffset, float deltaTime)
	{
		this->velocity = velocityBaseOffset;
		velocity.x *= velocityOffset.x * ballSpeed * deltaTime;
		velocity.y *= velocityOffset.y * ballSpeed * deltaTime;
		this->move(velocity);
	}
};

