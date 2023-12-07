#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>

#include <iostream>
#include <windows.h>

#include "PongStick.h"
#include "EnumLibrary.h"

using namespace sf;
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
	String windowTitle(string("Pong")); //윈도우 타이틀

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
	if (!font.loadFromFile("c:/windows/fonts/arial.ttf"))
	{
		MessageBox(NULL, TEXT("Cannot find font"), TEXT("Error"), MB_ICONERROR);
		return EXIT_FAILURE;
	}

	Text text("Hello SFML!", font, 30U);

	//////////////////////////////////////////
	//
	// 윈도우 생성 
	// 
	// 실제로 출력되는 윈도우를 생성합니다 
	//
	//////////////////////////////////////////

	RenderWindow window;
	window.create(VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, windowSettings);

	///////////////////////////////////////////
	//
	// 오브젝트 설정
	// 
	// 게임 내에서 사용되는 오브젝트를 설정합니다
	// 가능하다면 클래스를 통해 인스턴스를 생성해야 합니다
	//
	///////////////////////////////////////////

	Clock UserClock;

	const Vector2u windowSize = window.getSize();

	const Vector2f standardSize(10, 70);
	const Vector2f standardPos(30, (windowSize.y - standardSize.y) / 2);

	Vector2f leftPlayerSize(standardSize);
	Vector2f leftPlayerPosition(standardPos.x, standardPos.y);

	Vector2f rightPlayerSize(standardSize);
	Vector2f rightPlayerPosition(windowSize.x - (standardPos.x * 2), standardPos.y);

	PongStick leftPongStick = PongStick(standardPos, standardSize);
	PongStick rightPongStick = leftPongStick;

	CircleShape ball;
	ball.setRadius(10.0f);
	ball.setPosition((windowSize.x - ball.getRadius()) / 2, (windowSize.y - ball.getRadius()) / 2);

	///////////////////////////////////////////
	//
	// 콘솔 디버그
	// 
	// 콘솔에 출력할 내용은 이곳에서 작성됩니다 
	//
	///////////////////////////////////////////

	std::cout << "Window Size : (" << windowSize.x << ", " << windowSize.y << ")" << std::endl;
	std::cout << "Standard Position : (" << standardPos.x << ", " << standardPos.y << ")" << std::endl;
	std::cout << "Left Player Size : (" << leftPlayerSize.x << ", " << leftPlayerSize.y << ")" << std::endl;
	std::cout << "Left Player Position : (" << leftPlayerPosition.x << ", " << leftPlayerPosition.y << ")" << std::endl;
	std::cout << "Right Player Size : (" << rightPlayerSize.x << ", " << rightPlayerSize.y << ")" << std::endl;
	std::cout << "Right Player Position : (" << rightPlayerPosition.x << ", " << rightPlayerPosition.y << ")" << std::endl;

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

	while (window.isOpen())
	{
		///////////////////////////////////////////
		// 
		// 통상 이벤트 핸들러
		// 
		// window.pollEvent()를 통해 비연속적으로 수행되는 모든 이벤트를 처리합니다
		// 
		///////////////////////////////////////////

		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Unknown) //Except unknown key
					; //do nothing
				else if (event.key.code == Keyboard::Escape)
					window.close();

				std::cout << "Key Pressed! - " << event.key.code << std::endl;
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

		float DeltaTime = UserClock.restart().asSeconds();

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			leftPongStick.StickVerticalMove(VerticalDirection::Up, DeltaTime);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			leftPongStick.StickVerticalMove(VerticalDirection::Down, DeltaTime);
		}

		///////////////////////////////////////////
		//
		// 오브젝트 그리기
		// 
		// 생성된 오브젝트를 윈도우에 그려서 디스플레이로 출력시킵니다
		// 이곳에서 그려지지 않은 오브젝트는 출력되지 않습니다
		// 
		// 오브젝트는 Scene 단위로 그립니다
		// 
		///////////////////////////////////////////

		window.clear();

		window.draw(text);
		window.draw(leftPongStick);
		window.draw(ball);

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