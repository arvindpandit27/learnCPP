#include <SFML/Graphics.hpp.>
#include <iostream>
#include "typedefs.hpp"

using namespace sf;

RenderWindow renderWindow(VideoMode(800, 800), "Chowka Bhaara");


void moveCoinPosition(CircleShape triangle, RenderWindow* renderWindow, int row_value, int column_value)
{
	// Input: Coin shape, Graphics board, row and column value
	// Output: Draw the coin shape in the updated position
	// Purpose: To update coin position and interface with graphics  
	triangle.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 137.5) });
	renderWindow->draw(triangle);
}

void BoardGraphics(Player User[], int NPlayers) 
{
	// Input: Player number
	// Output: Display/Draw the main board
	// Purpose: 
	RenderWindow renderWindow(VideoMode(800, 800), "Chowka Bhaara");
	Event event;

	RectangleShape sq(Vector2f{ 100,100 });
	RectangleShape rectangle1(Vector2f(4, 100 * (float)sqrt(2))); // change the size to 100x100 rectangle.setSize(sf::Vector2f(100, 100));
	RectangleShape rectangle2(Vector2f(4, 100 * (float)sqrt(2)));

	// Initialize triangles
	CircleShape* Triangle;
	Triangle = new CircleShape[NPlayers];
	int ColorMatrix[4][3] = { {255,0,0},{0,0,255},{0,255,0},{255,255,0} };
	for (int n = 0; n < NPlayers; n++) {
		Triangle[n].setPointCount(3);
		Triangle[n].setRadius(15);
		Triangle[n].setFillColor(Color(ColorMatrix[n][0], ColorMatrix[n][1], ColorMatrix[n][2]));
	}

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
		}

		for (int n = 0; n < NPlayers; n++) {
			moveCoinPosition(Triangle[n], &renderWindow, User[n].Coin[0].xPos, User[n].Coin[0].yPos);
		}

		renderWindow.display();
	}
}

