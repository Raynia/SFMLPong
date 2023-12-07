#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


// �÷��̾ �����̴� ��ƽ�� ���ǵ� Ŭ����
class PongStick : public RectangleShape
{
private:
	static int PlayerCount; //���ӿ� ���ӵ� �÷��̾��� ��
	const static int StickSpeed = 300; //��ƽ�� �̵� �ӵ�

public:
	Vector2f StickPosition; //��ƽ�� ��ġ (X��ǥ, Y��ǥ)
	Vector2f StickSize; //��ƽ�� ũ�� (���� ����, ���� ����)
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

