#include <SFML/System.hpp>
#include <box2d/box2d.h>

#include <iostream>
#include <random>
#include <vector>

#include <windows.h>

#include "PongStick.h"
#include "PongBall.h"
#include "SideWall.h"

#include "EnumLibrary.h"

using namespace std;

int main()
{
	///////////////////////////////////////////
	//
	// 게임 윈도우(Window) 설정
	// 
	// 개발 표준 윈도우 사이즈는 1280 x 720이며,
	// 모든 사이즈와 스케일은 이 사이즈에 맞춰서 이루어져야 합니다
	//
	///////////////////////////////////////////

	Uint32 windowWidth = 1280U; //윈도우 너비
	Uint32 windowHeight = 720U; //윈도우 높이
	String windowTitle("Pong"); //윈도우 타이틀

	// 윈도우 컨텍스트 설정입니다
	// \param depthBits: detph buffer 비트
	// \param stencilBits: stencil bugger 비트
	// \param antialiasingLevel: 안티엘리어싱 레벨
	// \param majorVersion:
	// \param minorVersion:
	ContextSettings windowSettings;
	windowSettings.depthBits = 24U;
	windowSettings.stencilBits = 8U;
	windowSettings.antialiasingLevel = 4U;
	windowSettings.majorVersion = 4U;
	windowSettings.minorVersion = 0U;

	//윈도우 스타일을 지정합니다
	int32_t windowStyle = Style::Close;

	// 폰트
	Font font;
	if ( !font.loadFromFile("c:/windows/fonts/arial.ttf") )
	{
		MessageBox(NULL, TEXT("Cannot find font"), TEXT("Error"), MB_ICONERROR);
		return EXIT_FAILURE;
	}

	//////////////////////////////////////////
	//
	// 윈도우 생성 
	// 
	// 실제로 출력되는 윈도우를 생성합니다 
	//
	//////////////////////////////////////////

	RenderWindow window;
	window.create(VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, windowSettings);
	window.setFramerateLimit(60);

	///////////////////////////////////////////
	//
	// 오브젝트 설정
	// 
	// 게임 내에서 사용되는 오브젝트를 설정합니다
	//
	///////////////////////////////////////////

	// 범용 변수

	Clock UserClock;
	float DeltaTime = 0.f;

	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<> intDist(0, 1);
	uniform_real_distribution<> floatDist;

	const Vector2u windowSize = window.getSize();
	const float windowSize_x = static_cast< float >( windowSize.x );
	const float windowSize_y = static_cast< float >( windowSize.y );

	// 스틱 오브젝트

	const float leftSideStick = windowSize_x * 0.1f;
	const float rightSideStick = windowSize_x * 0.9f;
	const float middleOfStickPositonY = ( windowSize_y - PongStick::defaultPongStickHeight ) / 2;

	const Vector2f pongLeftStickPosition(leftSideStick, middleOfStickPositonY);
	const Vector2f pongRightStickPosition(rightSideStick, middleOfStickPositonY);

	PongStick PongStick1(pongLeftStickPosition, PlayerType::Human);
	PongStick PongStick2(pongRightStickPosition, PlayerType::Computer);

	FloatRect stickAreaTest;
	vector<FloatRect> stickArea;

	// 공 오브젝트

	const float ballRadius = 10.f;
	const float ballSpeed = 500.f;
	const Vector2f ballInitPosition = Vector2f(( windowSize_x - ballRadius ) / 2, ( windowSize_y - ballRadius ) / 2);;

	PongBall pongBall(ballInitPosition, 10.f, ballSpeed);

	float ballMaxOffsetRangeOfX = ( windowSize_x - leftSideStick ) / windowSize_y;
	float ballMaxOffsetRangeOfY = windowSize_y / windowSize_y;
	uniform_real_distribution<> ballYOffestDist(-ballMaxOffsetRangeOfY, ballMaxOffsetRangeOfY);

	Vector2f ballVelocityOffest(ballMaxOffsetRangeOfX, static_cast< float >( ballYOffestDist(gen) ));

	FloatRect ballArea;

	// 스코어 보드 텍스트 오브젝트

	int leftSideScore = 0;
	int rightSideScore = 0;
	unsigned int scoreTextSize = 40U;
	Vector2f leftSideScoreTextPosition(windowSize_x * 0.4f, 20.f);
	Vector2f rightSideScoreTextPosition(windowSize_x * 0.6f, 20.f);

	Text leftSideScoreText(to_string(leftSideScore), font, scoreTextSize);
	Text rightSideScoreText(to_string(rightSideScore), font, scoreTextSize);
	leftSideScoreText.setPosition(leftSideScoreTextPosition);
	rightSideScoreText.setPosition(rightSideScoreTextPosition);

	// 화면 상하에 위치한 충돌 감지용 오브젝트
	// 공이 충돌하면 y축 이동 방향 반전
	Vector2f updownAreaSize(windowSize_x, 1);
	Vector2f upAreaPosition(0, -( updownAreaSize.y ));
	Vector2f downAreaPosition(0, windowSize_y);
	vector<FloatRect> updownWall;
	updownWall.push_back(FloatRect(upAreaPosition, updownAreaSize));
	updownWall.push_back(FloatRect(downAreaPosition, updownAreaSize));


	// 화면 좌우에 위치한 충돌 감지용 오브젝트
	// 공이 충돌하면 공의 위치 초기화, 점수 1점 획득
	Vector2f sideAreaSize(1, windowSize_y);
	Vector2f leftSideAreaPosition(-( sideAreaSize.x ), 0);
	Vector2f rightSideAreaPosition(windowSize_x, 0);
	vector<SideWall> sideWall;

	sideWall.push_back(SideWall(FloatRect(leftSideAreaPosition, sideAreaSize), WallSide::Left));
	sideWall.push_back(SideWall(FloatRect(rightSideAreaPosition, sideAreaSize), WallSide::Right));


	///////////////////////////////////////////
	//
	// 콘솔 디버그
	// 
	// 콘솔에 출력할 내용은 이곳에서 작성됩니다 
	//
	///////////////////////////////////////////


	///////////////////////////////////////////
	// 
	// 기능 테스트
	// 
	// 테스트에 활용되는 변수는 이곳에서 선언되며,
	// 모든 변수에 접두사 "test"가 있어야 합니다
	// 
	///////////////////////////////////////////


	///////////////////////////////////////////
	// 
	// 게임 루프
	// 
	// 인게임 루프가 실행되는 반복문입니다 
	// 오브젝트를 출력과 윈도우 이벤트 핸들러가 실행됩니다
	// 
	///////////////////////////////////////////

	while ( window.isOpen() )
	{
		///////////////////////////////////////////
		// 
		// 통상 이벤트 핸들러
		// 
		// window.pollEvent()를 통해 비연속적으로 수행되는 모든 이벤트를 처리합니다
		// 
		///////////////////////////////////////////

		Event event;

		while ( window.pollEvent(event) )
		{
			switch ( event.type )
			{
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:

				switch ( event.key.code )
				{
				case Keyboard::Unknown:
					//Do Nothing
					break;

				case Keyboard::Escape:
					window.close();
					break;

				default:
					break;
				}

				break;

			default:
				break;
			}
		}

		///////////////////////////////////////////
		// 
		// 키보드 및 마우스 이벤트 핸들러
		// 
		// 일부 키보드와 마우스 이벤트는 별도로 처리되며,
		// deltaTime을 사용해 연속적으로 수행되는 이벤트가 처리됩니다
		// 
		// ex) 막대기를 움직이는 키보드 이벤트
		// 
		///////////////////////////////////////////

		DeltaTime = UserClock.restart().asSeconds();

		if ( Keyboard::isKeyPressed(Keyboard::Up) )
		{
			PongStick1.StickVerticalMove(VerticalDirection::Up, DeltaTime);
		}
		if ( Keyboard::isKeyPressed(Keyboard::Down) )
		{
			PongStick1.StickVerticalMove(VerticalDirection::Down, DeltaTime);
		}

		if ( Keyboard::isKeyPressed(Keyboard::W) )
		{
			PongStick2.StickVerticalMove(VerticalDirection::Up, DeltaTime);
		}
		if ( Keyboard::isKeyPressed(Keyboard::S) )
		{
			PongStick2.StickVerticalMove(VerticalDirection::Down, DeltaTime);
		}

		///////////////////////////////////////////
		// 
		// 콜리전
		// 
		// 오브젝트 간의 충돌에 대해 처리합니다 
		// 
		///////////////////////////////////////////

		// 움직이는 오브젝트의 위치를 갱신합니다

		ballArea = pongBall.getGlobalBounds();

		stickArea.push_back(PongStick1.getGlobalBounds());
		stickArea.push_back(PongStick2.getGlobalBounds());

		for ( const auto& stick : stickArea )
		{
			if ( stick.intersects(ballArea) )
			{
				ballVelocityOffest.x *= -1;
				break;
			}
		}

		for ( const auto& wall : updownWall )
		{
			if ( wall.intersects(ballArea) )
			{
				ballVelocityOffest.y *= -1;
				break;
			}
		}

		for ( const auto& wall : sideWall )
		{
			if ( wall.wallArea.intersects(ballArea) )
			{
				pongBall.ResetPosition(); // 공 위치 초기화
				ballVelocityOffest.x *= -1;// 공 방향 수정
				ballVelocityOffest.y = static_cast< float >( ballYOffestDist(gen) );// 공 방향 수정

				//충돌한 측면 벽의 위치에 따라, 상대편의 점수가 1점 씩 올라갑니다
				switch ( wall.wallSide )
				{
				case WallSide::Left:
					rightSideScoreText.setString(to_string(++rightSideScore));
					break;

				case WallSide::Right:
					leftSideScoreText.setString(to_string(++leftSideScore));
					break;

				default:
					break;
				}

				break;
			}
		}

		///////////////////////////////////////////
		//
		// 오브젝트 그리기
		// 
		// 생성된 오브젝트를 윈도우에 그려서 디스플레이로 출력시킵니다
		// 이곳에서 그려지지 않은 오브젝트는 출력되지 않습니다
		// 
		///////////////////////////////////////////

		window.clear();

		window.draw(PongStick1);
		window.draw(PongStick2);
		window.draw(pongBall);

		window.draw(leftSideScoreText);
		window.draw(rightSideScoreText);

		window.display();

		// 공은 항상 움직이는 상태이기 때문에,
		// MovementOffset 값만 변경해서 공의 궤적만 변경합니다
		pongBall.MoveBall(ballVelocityOffest, DeltaTime);
	}

	///////////////////////////////////////////
	// 
	// 윈도우 종료
	// 
	// 생성된 윈도우를 닫고 응용 프로그램을 종료합니다
	// 
	///////////////////////////////////////////

	window.~RenderWindow();
	return EXIT_SUCCESS;
}