#include <SFML/Graphics.hpp.>

using namespace sf;

void BoardGraphics() {
	sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chowka Bhaara");

	sf::Event event;

	sf::CircleShape square(100, 4);
	sf::RectangleShape sq(Vector2f{ 100,100 });
	sf::RectangleShape rectangle1(sf::Vector2f(4, 100 * (float)sqrt(2))); // change the size to 100x100 rectangle.setSize(sf::Vector2f(100, 100));
	sf::RectangleShape rectangle2(sf::Vector2f(4, 100 * (float)sqrt(2)));
	sf::RectangleShape rectangleCoin(sf::Vector2f(4, 20*(float) sqrt(2)));
	//sf::RectangleShape sq(Vector2f{ 100,100 });

	square.setRotation(45);
	rectangle1.setRotation(-45);
	rectangle2.setRotation(45);
	rectangleCoin.setRotation(45);

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
				sq.setFillColor(sf::Color(192, 192, 192));
				sq.setPosition({ (float)(105 * i + 100), (float)(105 * j + 100) });
				renderWindow.draw(sq);
				if ((i % 2 == 0 && j % 2 == 0 && (((i + j) == 2) || ((i + j) == 6))) || (i == 2 && j == 2))
				{
					rectangle1.setPosition({ (float)(105 * i + 100), (float)(105 * j + 100) });
					rectangle1.setFillColor(sf::Color(0, 0, 0));
					renderWindow.draw(rectangle1);
					rectangle2.setPosition({ (float)(105 * i + 200), (float)(105 * j + 100) });
					rectangle2.setFillColor(sf::Color(0, 0, 0));
					renderWindow.draw(rectangle2);




				}

			}
			// renderwindow.draw(line ,2, sf::lines);
		}
		rectangleCoin.setPosition({ (float)(105 *(0+1) + 50), (float)(105 * 0  + 150) });
		rectangleCoin.setFillColor(sf::Color(255, 0, 0));
		renderWindow.draw(rectangleCoin);
		renderWindow.display();
	}
}