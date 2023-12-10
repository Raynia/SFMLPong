#pragma once

enum VerticalDirection // 수직 방향 열거형
{
	Up = -1,
	Down = 1,
};

enum HorizontalDirection // 수평 방향 열거형
{
	Left = -1,
	Right = 1,
};

enum PlayerType // 플레이어 타입 열거혐
{
	Human = 0,
	Computer = 1,
};

enum StickLocation // 스틱 위치 열거형
{
	LeftSide = -1,
	RightSide = 1,
};

enum class WallSide : int // 벽 위치 열거형 클래스
{
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4,
};



