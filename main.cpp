#include <SFML/System.hpp>
#include <box2d/box2d.h>

#include <iostream>
#include <random>
#include <vector>

#include <windows.h>

#include "PongStick.h"
#include "PongBall.h"
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
	uniform_real_distribution<> dist(-5.0f, 5.0f);

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

	Vector2f ballInitPosition;

	CircleShape ball;

	ball.setRadius(10.0f);
	ballInitPosition = Vector2f(( windowSize_x - ball.getRadius() ) / 2, ( windowSize_y - ball.getRadius() ) / 2);
	ball.setPosition(ballInitPosition);

	//Vector2f ballMovementOffest(static_cast< float >( dist(gen) ), static_cast< float >( dist(gen) ));
	Vector2f ballMovementOffest(-5.f, 5.f);

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
	Vector2f updownWallSize(windowSize_x, 1);
	Vector2f upWallPosition(0, -( updownWallSize.y ));
	Vector2f downWallPosition(0, windowSize_y);
	vector<FloatRect> updownWall;
	updownWall.push_back(FloatRect(upWallPosition, updownWallSize));
	updownWall.push_back(FloatRect(downWallPosition, updownWallSize));


	// 화면 좌우에 위치한 충돌 감지용 오브젝트
	// 공이 충돌하면 공의 위치 초기화, 점수 1점 획득
	Vector2f sideWallSize(1, windowSize_y);
	Vector2f leftSideWallPosition(-( sideWallSize.x ), 0);
	Vector2f rightSideWallPosition(windowSize_x, 0);
	vector<FloatRect> sideWall;
	sideWall.push_back(FloatRect(leftSideWallPosition, sideWallSize));
	sideWall.push_back(FloatRect(rightSideWallPosition, sideWallSize));

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

		///////////////////////////////////////////
		// 
		// 콜리전
		// 
		// 오브젝트 간의 충돌에 대해 처리합니다 
		// 
		///////////////////////////////////////////

		// 움직이는 오브젝트의 위치를 갱신합니다

		ballArea = ball.getGlobalBounds();

		stickArea.push_back(PongStick1.getGlobalBounds());
		stickArea.push_back(PongStick2.getGlobalBounds());

		for ( auto& stick : stickArea )
		{
			if ( stick.intersects(ballArea) )
			{
				ballMovementOffest.x = -ballMovementOffest.x;
			}
		}

		for ( auto& wall : updownWall )
		{
			if ( wall.intersects(ballArea) )
			{
				ballMovementOffest.y = -ballMovementOffest.y;
			}
		}

		for ( auto& wall : sideWall )
		{
			if ( wall.intersects(ballArea) )
			{
				ball.setPosition(ballInitPosition); // 공 위치 초기화
				ballMovementOffest.x = -ballMovementOffest.x;// 공 방향 수정
				ballMovementOffest.y = static_cast< float >( dist(gen) );// 공 방향 수정

				// 점수 획득
			}
		}

		// 공은 항상 움직이는 상태이기 때문에,
		// MovementOffset 값만 변경해서 공의 궤적만 변경합니다
		ball.move(ballMovementOffest);

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
		window.draw(ball);

		window.draw(leftSideScoreText);
		window.draw(rightSideScoreText);

		window.display();
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