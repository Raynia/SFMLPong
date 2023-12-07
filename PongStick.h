#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

// 플레이어가 움직이는 스틱이 정의된 클래스
class PongStick : public RectangleShape
{
private:
	const static int StickSpeed = 300; // 스틱의 이동 속도

public:
	const static int defaultPongStickWidth = 10;
	const static int defaultPongStickHeight = 70;

	int PlayerType;	// 스틱을 조종하는 플레이어의 타입, PlayerType enum으로 지정
	Vector2f velocity;

	PongStick(Vector2f Position, int PlayerType);
	PongStick(Vector2f Size, Vector2f Position, int PlayerType);
	~PongStick();

	void StickVerticalMove(int VerticalDirection, float DeltaTime);	
};

