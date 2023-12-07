#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <box2d/box2d.h>

#include "PongStick.h"
#include "EnumLibrary.h"

using namespace sf;
using namespace std;

int main()
{
	///////////////////////////////////////////
	////
	//// 게임 윈도우(Window) 설정
	////
	///////////////////////////////////////////


	Uint32 windowWidth = 1280U; //set screen width
	Uint32 windowHeight = 720U; //set screen height
	String windowTitle(string("Pong")); //set title

	ContextSettings windowSettings;
	windowSettings.depthBits = 24U;
	windowSettings.stencilBits = 8U;
	windowSettings.antialiasingLevel = 4U;
	windowSettings.majorVersion = 4U;
	windowSettings.minorVersion = 0U;

	int32_t windowStyle = sf::Style::Close;

	sf::Font font;
	if (!font.loadFromFile("c:/windows/fonts/arial.ttf"))
		return -1;

	sf::Text text("Hello SFML!", font, 30U);

	//////////////////////////////////////////
	///
	/// 게임 창 생성 
	///
	//////////////////////////////////////////

	sf::RenderWindow window;

	window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, windowSettings);

	///////////////////////////////////////////
	////
	//// 게임 오브젝트 설정
	////
	///////////////////////////////////////////

	Clock UserClock;


	const sf::Vector2u windowSize = window.getSize();

	const sf::Vector2f standardSize(10, 70);
	const sf::Vector2f standardPos(30, (windowSize.y - standardSize.y) / 2);

	sf::Vector2f leftPlayerSize(standardSize);
	sf::Vector2f leftPlayerPosition(standardPos.x, standardPos.y);

	sf::Vector2f rightPlayerSize(standardSize);
	sf::Vector2f rightPlayerPosition(windowSize.x - (standardPos.x * 2), standardPos.y);

	PongStick leftPongStick = PongStick(standardPos, standardSize);
	PongStick rightPongStick = leftPongStick;

	sf::CircleShape ball;
	ball.setRadius(10.0f);
	ball.setPosition((windowSize.x - ball.getRadius()) / 2, (windowSize.y - ball.getRadius()) / 2);


	///////////////////////////////////////////
	////
	//// Values Debug
	////
	///////////////////////////////////////////

	std::cout << "Window Size : (" << windowSize.x << ", " << windowSize.y << ")" << std::endl;
	std::cout << "Standard Position : (" << standardPos.x << ", " << standardPos.y << ")" << std::endl;
	std::cout << "Left Player Size : (" << leftPlayerSize.x << ", " << leftPlayerSize.y << ")" << std::endl;
	std::cout << "Left Player Position : (" << leftPlayerPosition.x << ", " << leftPlayerPosition.y << ")" << std::endl;
	std::cout << "Right Player Size : (" << rightPlayerSize.x << ", " << rightPlayerSize.y << ")" << std::endl;
	std::cout << "Right Player Position : (" << rightPlayerPosition.x << ", " << rightPlayerPosition.y << ")" << std::endl;

	//std::cout << "Window Size : (" << windowSize.x << ", " << windowSize.y << ")" << std::eendl;

	///////////////////////////////////////////
	//// 
	//// 기능 테스트 용
	//// 
	///////////////////////////////////////////


	///////////////////////////////////////////
	// 
	// 게임 루프
	// 
	///////////////////////////////////////////
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Unknown) //Except unknown key
					; //do nothing
				else if (event.key.code == sf::Keyboard::Escape)
					window.close();

				std::cout << "Key Pressed! - " << event.key.code << std::endl;
				break;

			default:
				break;
			}
		}

		///
		float DeltaTime = UserClock.restart().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			leftPongStick.StickVerticalMove(VerticalDirection::Up, DeltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			leftPongStick.StickVerticalMove(VerticalDirection::Down, DeltaTime);
		}

		window.clear();
		window.draw(text);
		window.draw(leftPongStick);
		window.draw(ball);
		window.display();
	}


	window.~RenderWindow();

	return 0;
}