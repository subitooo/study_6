#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>


namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;

		Ship m_ship;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Setup(int n)
		{

			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);

			// Загрузка текстуры фона
			if (!m_textureBackground.loadFromFile("assets\\background.jpg")) {
				std::cout << "Error while loading background.jpg!";
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			// Создание корабля игрока

			if (!m_ship.Setup(100, 100)) {
				return false;
			};

			srand(time(0));
		}



		void LifeCycle()
		{
			sf::Clock clock;

			while (m_window.isOpen())
			{
				// Обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					m_ship.setVelocity(0.0001);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					m_ship.setVelocity(-0.0001);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					m_ship.Rotate(-0.1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					m_ship.Rotate(0.1);
				}


				// Логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				m_ship.Move();

				// Отображение

				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_ship.Get());
				m_window.display();
			}
		}
	};

}