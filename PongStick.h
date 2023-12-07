#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

// 플레이어가 움직이는 스틱이 정의된 클래스
class PongStick : public RectangleShape
{
private:
	static int PlayerCount; //게임에 접속된 플레이어의 수
	const static int StickSpeed = 300; //스틱의 이동 속도

public:
	Vector2f StickPosition; //스틱의 위치 (X좌표, Y좌표)
	Vector2f StickSize; //스틱의 크기 (가로 길이, 세로 길이)
	Vector2f velocity;


	PongStick();
	PongStick(Vector2f Position, Vector2f Size);
	~PongStick();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="VerticalDirection"></param>
	/// <param name="DeltaTime"></param>
	void StickVerticalMove(int VerticalDirection, float DeltaTime);	

};

