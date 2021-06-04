#include <SFML/Graphics.hpp.>
#include <iostream>
#include "typedefs.hpp"

using namespace sf;

RenderWindow renderWindow(VideoMode(800, 800), "Chowka Bhaara");


void moveCoinPosition(CircleShape shape, RenderWindow* renderWindow, int row_value, int column_value, int player_number, int coin_number)
{
	// Input: Coin shape, Graphics board, row and column value
	// Output: Draw the coin shape in the updated position
	// Purpose: To update coin position and interface with graphics  
	switch (coin_number) {
	case 0:
		switch (player_number) {
		case 0:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 137.5) });
			break;
		case 1:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 137.5) });
			break;
		case 2:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 107.5) });
			break;
		case 3:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 167.5) });
			break;
		}
		break;
	case 1:
		switch (player_number) {
		case 0:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 137.5) });
			break;
		case 1:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 107.5) });
			break;
		case 2:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 167.5) });
			break;
		case 3:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 137.5) });
			break;
		}
		break;
	case 2:
		switch (player_number) {
		case 0:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 107.5) });
			break;
		case 1:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 167.5) });
			break;
		case 2:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 137.5) });
			break;
		case 3:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 137.5) });
			break;
		}
		break;
	case 3:
		switch (player_number) {
		case 0:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 167.5) });
			break;
		case 1:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 137.5) });
			break;
		case 2:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 137.5) });
			break;
		case 3:
			shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 107.5) });
			break;
		}
		break;
	}
	renderWindow->draw(shape);
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

	// Initialize Triangles
	CircleShape* Triangle;
	Triangle = new CircleShape[NPlayers];
	int ColorMatrix[4][3] = { {255,0,0},{0,0,255},{0,255,0},{255,255,0} };
	for (int n = 0; n < NPlayers; n++) {
		Triangle[n].setPointCount(3);
		Triangle[n].setRadius(15);
		Triangle[n].setFillColor(Color(ColorMatrix[n][0], ColorMatrix[n][1], ColorMatrix[n][2]));
	}

	// Initialize Diamonds
	CircleShape* Diamond;
	Diamond = new CircleShape[NPlayers];
	for (int n = 0; n < NPlayers; n++) {
		Diamond[n].setPointCount(4);
		Diamond[n].setRadius(15);
		Diamond[n].setFillColor(Color(ColorMatrix[n][0], ColorMatrix[n][1], ColorMatrix[n][2]));
	}

	// Initialize Pentagons
	CircleShape* Pentagon;
	Pentagon = new CircleShape[NPlayers];
	for (int n = 0; n < NPlayers; n++) {
		Pentagon[n].setPointCount(5);
		Pentagon[n].setRadius(15);
		Pentagon[n].setFillColor(Color(ColorMatrix[n][0], ColorMatrix[n][1], ColorMatrix[n][2]));
	}

	// Initialize Hexagons
	CircleShape* Hexagon;
	Hexagon = new CircleShape[NPlayers];
	for (int n = 0; n < NPlayers; n++) {
		Hexagon[n].setPointCount(6);
		Hexagon[n].setRadius(15);
		Hexagon[n].setFillColor(Color(ColorMatrix[n][0], ColorMatrix[n][1], ColorMatrix[n][2]));
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
					rectangle2.setFillColor(sf::Color(255, 215, 0));
					renderWindow.draw(rectangle2);
				}

			}
		}

		for (int np = 0; np < NPlayers; np++) {
			for (int nc = 0; nc < 4; nc++) {
				if (User[np].Coin[nc].isDrawn == 0) {
					User[np].Coin[nc].isDrawn == 1;
					switch (nc) {
					case 0:
						moveCoinPosition(Triangle[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, np, nc);
						break;
					case 1:
						moveCoinPosition(Diamond[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, np, nc);
						break;
					case 2:
						moveCoinPosition(Pentagon[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, np, nc);
						break;
					case 3:
						moveCoinPosition(Hexagon[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, np, nc);
						break;
					}
				}
			}
		}

		renderWindow.display();
	}
}

