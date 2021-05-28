#include <SFML/Graphics.hpp.>
#include <iostream>

using namespace sf;
using namespace std;


void init_coin_position(CircleShape triangle, RenderWindow* renderWindow)
{
	triangle.setFillColor(sf::Color(255, 0, 0));
	triangle.setPosition({ (float)(105 * 2 + 100), (float)(105 * 0 + 100) });
	//triangle.setOutlineThickness(2);
	//triangle.setFillColor(sf::Color(0,255,0));
	renderWindow->draw(triangle);
}

void coin_position_move(CircleShape triangle, RenderWindow* renderWindow, float row_value, float column_value)
{
	triangle.setFillColor(sf::Color(255, 0, 0));
	triangle.setPosition({ (float)(105 * column_value + 100), (float)(105 * row_value + 100) });
	//triangle.setOutlineThickness(2);
	//triangle.setFillColor(sf::Color(0,255,0))
	renderWindow->draw(triangle);
}

void BoardGraphics() {
	
	sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chowka Bhaara");
	sf::Event event;

	//sf::CircleShape square(100, 4);
	sf::RectangleShape sq(Vector2f{ 100,100 });
	sf::RectangleShape rectangle1(sf::Vector2f(4, 100 * (float)sqrt(2))); // change the size to 100x100 rectangle.setSize(sf::Vector2f(100, 100));
	sf::RectangleShape rectangle2(sf::Vector2f(4, 100 * (float)sqrt(2)));
	sf::CircleShape triangle(30, 3);

	

	//sf::RectangleShape sq(Vector2f{ 100,100 });
	//square.setRotation(45);
	rectangle1.setRotation(-45);
	rectangle2.setRotation(45);

	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}
		renderWindow.clear();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				sq.setFillColor(sf::Color(0, 0, 0));
				sq.setPosition({ (float)(105 * i + 100), (float)(105 * j + 100) });
				sq.setOutlineThickness(5);
				sq.setOutlineColor(sf::Color(255, 215, 0));

				//triangle.setFillColor(sf::Color(255, 0, 0));
				//triangle.setPosition({ (float)(105 * 2.25 + 100), (float)(105 * 0 + 100) });
				//triangle.setOutlineThickness(2);
				//triangle.setFillColor(sf::Color(0,255,0));
				//renderWindow.draw(triangle);
				//init_coin_position(triangle,  &renderWindow);


				renderWindow.draw(sq);
				if ((i % 2 == 0 && j % 2 == 0 && (((i + j) == 2) || ((i + j) == 6))) || (i == 2 && j == 2))
				{
					rectangle1.setPosition({ (float)(105 * i + 100), (float)(105 * j + 100) });
					rectangle1.setFillColor(sf::Color(255, 215, 0));
					renderWindow.draw(rectangle1);
					rectangle2.setPosition({ (float)(105 * i + 200), (float)(105 * j + 100) });
					rectangle2.setFillColor(sf::Color(255,215, 0));
					renderWindow.draw(rectangle2);




				}

			}
			// renderwindow.draw(line ,2, sf::lines);
		}

		//float row_value, column_value;
		//cout << "enter row value" << endl;
		//cin >> row_value;
		//cout << "enter column value" << endl;
		//cin >> column_value;
		//triangle.setPosition({ (float)(105 * column_value + 100), (float)(105 * row_value + 100) });
		////renderWindow.draw(triangle);
		coin_position_move( triangle, &renderWindow, 2.0f, 3.0f);
		renderWindow.display();
	}
}

