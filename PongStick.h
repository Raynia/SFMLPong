#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

// 플레이어가 움직이는 스틱이 정의된 클래스
class PongStick : public RectangleShape
{
private:
	const static int StickSpeed = 300; // 스틱의 빠르기

public:
	const static int defaultPongStickWidth = 10; // 스틱 너비 기본값
	const static int defaultPongStickHeight = 70; // 스틱 너비 기본값

	int PlayerType;	// 스틱을 조종하는 플레이어의 타입
	Vector2f velocity; // 스틱의 이동 속도

	PongStick(Vector2f Position, int PlayerType);
	PongStick(Vector2f Size, Vector2f Position, int PlayerType);
	~PongStick();

	// 스틱 상하 방향으로 이동
	void StickVerticalMove(int VerticalDirection, float DeltaTime);	
};

