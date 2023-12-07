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
	// ���� ������(Window) ����
	// 
	// ���� ǥ�� ������ ������� 1280 x 720�̸�,
	// ��� ������� �������� �� ����� ���缭 �̷������ �մϴ�
	//
	///////////////////////////////////////////

	Uint32 windowWidth = 1280U; //������ �ʺ�
	Uint32 windowHeight = 720U; //������ ����
	String windowTitle(string("Pong")); //������ Ÿ��Ʋ

	// ������ ���ؽ�Ʈ �����Դϴ�
	// \param depthBits: detph buffer ��Ʈ
	// \param stencilBits: stencil bugger ��Ʈ
	// \param antialiasingLevel: ��Ƽ������� ����
	// \param majorVersion:
	// \param minorVersion:
	ContextSettings windowSettings;
	windowSettings.depthBits = 24U;
	windowSettings.stencilBits = 8U;
	windowSettings.antialiasingLevel = 4U;
	windowSettings.majorVersion = 4U;
	windowSettings.minorVersion = 0U;

	//������ ��Ÿ���� �����մϴ�
	int32_t windowStyle = Style::Close;

	// ��Ʈ
	Font font;
	if (!font.loadFromFile("c:/windows/fonts/arial.ttf"))
	{
		MessageBox(NULL, TEXT("Cannot find font"), TEXT("Error"), MB_ICONERROR);
		return EXIT_FAILURE;
	}

	Text text("Hello SFML!", font, 30U);

	//////////////////////////////////////////
	//
	// ������ ���� 
	// 
	// ������ ��µǴ� �����츦 �����մϴ� 
	//
	//////////////////////////////////////////

	RenderWindow window;
	window.create(VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, windowSettings);

	///////////////////////////////////////////
	//
	// ������Ʈ ����
	// 
	// ���� ������ ���Ǵ� ������Ʈ�� �����մϴ�
	// �����ϴٸ� Ŭ������ ���� �ν��Ͻ��� �����ؾ� �մϴ�
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
	// �ܼ� �����
	// 
	// �ֿܼ� ����� ������ �̰����� �ۼ��˴ϴ� 
	//
	///////////////////////////////////////////

	std::cout << "Window Size : (" << windowSize.x << ", " << windowSize.y << ")" << std::endl;
	std::cout << "Standard Position : (" << standardPos.x << ", " << standardPos.y << ")" << std::endl;
	std::cout << "Left Player Size : (" << leftPlayerSize.x << ", " << leftPlayerSize.y << ")" << std::endl;
	std::cout << "Left Player Position : (" << leftPlayerPosition.x << ", " << leftPlayerPosition.y << ")" << std::endl;
	std::cout << "Right Player Size : (" << rightPlayerSize.x << ", " << rightPlayerSize.y << ")" << std::endl;
	std::cout << "Right Player Position : (" << rightPlayerPosition.x << ", " << rightPlayerPosition.y << ")" << std::endl;

	//std::cout << "Window Size : (" << windowSize.x << ", " << windowSize.y << ")" << std::eendl;

	///////////////////////////////////////////
	// 
	// ��� �׽�Ʈ
	// 
	// �׽�Ʈ�� Ȱ��Ǵ� ������ �̰����� ����Ǹ�,
	// ��� ������ ���λ� "test"�� �־�� �մϴ�
	// 
	///////////////////////////////////////////


	///////////////////////////////////////////
	// 
	// ���� ����
	// 
	// �ΰ��� ������ ����Ǵ� �ݺ����Դϴ� 
	// ������Ʈ�� ��°� ������ �̺�Ʈ �ڵ鷯�� ����˴ϴ�
	// 
	///////////////////////////////////////////

	while (window.isOpen())
	{
		///////////////////////////////////////////
		// 
		// ��� �̺�Ʈ �ڵ鷯
		// 
		// window.pollEvent()�� ���� �񿬼������� ����Ǵ� ��� �̺�Ʈ�� ó���մϴ�
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
		// Ű���� �� ���콺 �̺�Ʈ �ڵ鷯
		// 
		// �Ϻ� Ű����� ���콺 �̺�Ʈ�� ������ ó���Ǹ�,
		// deltaTime�� ����� ���������� ����Ǵ� �̺�Ʈ�� ó���˴ϴ�
		// 
		// ex) ����⸦ �����̴� Ű���� �̺�Ʈ
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
		// ������Ʈ �׸���
		// 
		// ������ ������Ʈ�� �����쿡 �׷��� ���÷��̷� ��½�ŵ�ϴ�
		// �̰����� �׷����� ���� ������Ʈ�� ��µ��� �ʽ��ϴ�
		// 
		// ������Ʈ�� Scene ������ �׸��ϴ�
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
	// ������ ����
	// 
	// ������ �����츦 �ݰ� ���� ���α׷��� �����մϴ�
	// 
	///////////////////////////////////////////

	window.~RenderWindow();
	return EXIT_SUCCESS;
}