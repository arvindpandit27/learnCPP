#include <SFML/Graphics.hpp.>
#include <iostream>
#include "typedefs.hpp"

using namespace sf;
RenderWindow renderWindow(VideoMode(800, 800), "Chowka Bhaara");

void moveCoinPosition(CircleShape shape, RenderWindow* renderWindow, int row_value, int column_value, int draw_position, int solo_coin_flag, int coin_blink_flag)
{
	// Input: Coin shape, Graphics board, row and column value
	// Output: Draw the coin shape in the updated position
	// Purpose: To update coin position and interface with graphics
	static Clock clock;
	Color actual_color;

	if (coin_blink_flag == 0) {
		actual_color = shape.getFillColor();
		float test;
		test = clock.getElapsedTime().asSeconds();
		if (clock.getElapsedTime().asSeconds() < 0.5f)
			shape.setFillColor(actual_color);
		else if (clock.getElapsedTime().asSeconds() > 0.5f && clock.getElapsedTime().asSeconds() < 1.0) 
			shape.setFillColor(Color(0,0,0));
		else 
			clock.restart();
	}

	if (solo_coin_flag == 1) {
		shape.setPosition({ (float)(105 * column_value + 137.5), (float)(105 * row_value + 137.5) });
	}
	else {
		switch (draw_position) {
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
		case 4:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 107.5) });
			break;
		case 5:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 167.5) });
			break;
		case 6:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 167.5) });
			break;
		case 7:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 107.5) });
			break;
		case 8:
			shape.setPosition({ (float)(105 * column_value + 122.5), (float)(105 * row_value + 107.5) });
			break;
		case 9:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 122.5) });
			break;
		case 10:
			shape.setPosition({ (float)(105 * column_value + 152.5), (float)(105 * row_value + 107.5) });
			break;
		case 11:
			shape.setPosition({ (float)(105 * column_value + 107.5), (float)(105 * row_value + 152.5) });
			break;
		case 12:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 152.5) });
			break;
		case 13:
			shape.setPosition({ (float)(105 * column_value + 152.5), (float)(105 * row_value + 167.5) });
			break;
		case 14:
			shape.setPosition({ (float)(105 * column_value + 167.5), (float)(105 * row_value + 122.5) });
			break;
		case 15:
			shape.setPosition({ (float)(105 * column_value + 122.5), (float)(105 * row_value + 167.5) });
			break;
		}
	}
	renderWindow->draw(shape);
}

void BoardGraphics(Player User[], int NPlayers)
{
	// Input: Player objects and number of players
	// Output: Display/Draw the main board
	// Purpose: To display visual aspects of Chowka Bhaara
	RenderWindow renderWindow(VideoMode(800, 800), "Chowka Bhaara");
	renderWindow.setFramerateLimit(60);

	RectangleShape player(Vector2f(100.0f, 100.0f));
	player.setPosition(650.0f, 250.0f);
	Texture playerTexture;
	playerTexture.loadFromFile("Dice_sheet.png");
	player.setTexture(&playerTexture);

	Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 4; //x value starts from zero, it goes horizontal
	textureSize.y /= 5; //y value starts from zero 4 coloumns, it goes vertical

	//player.setTextureRect(IntRect(textureSize.x*0,textureSize.y*0,textureSize.x, textureSize.y));

	Clock clock;

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
		Event event;
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
				switch (nc) {
				case 0:
					moveCoinPosition(Triangle[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, User[np].Coin[nc].DrawPosition, User[np].Coin[nc].SoloCoinFlag, User[np].Coin[nc].Select_Other_Coin);
					break;
				case 1:
					moveCoinPosition(Diamond[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, User[np].Coin[nc].DrawPosition, User[np].Coin[nc].SoloCoinFlag, User[np].Coin[nc].Select_Other_Coin);
					break;
				case 2:
					moveCoinPosition(Pentagon[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, User[np].Coin[nc].DrawPosition, User[np].Coin[nc].SoloCoinFlag, User[np].Coin[nc].Select_Other_Coin);
					break;
				case 3:
					moveCoinPosition(Hexagon[np], &renderWindow, User[np].Coin[nc].xPos, User[np].Coin[nc].yPos, User[np].Coin[nc].DrawPosition, User[np].Coin[nc].SoloCoinFlag, User[np].Coin[nc].Select_Other_Coin);
					break;
				}
			}
		}

		//if (clock.getElapsedTime().asSeconds() > 1.0f)
		//{
		//	for (int a = 0; a <= 3; a++)
		//	{
		//		textureSize.x = a;
		//		for (int b = 0; b <= 4; b++)
		//		{
		//			textureSize.y = b;
		//			player.setTextureRect(IntRect(textureSize.x *a, textureSize.y * b, textureSize.x, textureSize.y));
		//		}
		//	}
		//}
		static int select_pos = 0;
		if (clock.getElapsedTime().asSeconds() > 0.05f)
		{
			switch (select_pos)
			{
				case 0:
					player.setTextureRect(IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
					select_pos = 1;
				break;
				case 1 :
					player.setTextureRect(IntRect(textureSize.x * 1, textureSize.y * 0, textureSize.x, textureSize.y));
					select_pos = 2;
				break;
				case 2:
					player.setTextureRect(IntRect(textureSize.x * 2, textureSize.y * 0, textureSize.x, textureSize.y));
					select_pos = 3;
				break;
				case 3:
					player.setTextureRect(IntRect(textureSize.x * 3, textureSize.y * 0, textureSize.x, textureSize.y));
					select_pos = 4;
				break;
				case 4:
					player.setTextureRect(IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
					select_pos = 5;
				break;
				case 5:
					player.setTextureRect(IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
					select_pos = 6;
					break;
				case 6:
					player.setTextureRect(IntRect(textureSize.x * 2, textureSize.y * 1, textureSize.x, textureSize.y));
					select_pos = 7;
					break;
				case 7:
					player.setTextureRect(IntRect(textureSize.x * 3, textureSize.y * 1, textureSize.x, textureSize.y));
					select_pos = 8;
					break;
				case 8:
					player.setTextureRect(IntRect(textureSize.x * 0, textureSize.y * 2, textureSize.x, textureSize.y));
					select_pos = 9;
					break;
				case 9:
					player.setTextureRect(IntRect(textureSize.x * 1, textureSize.y * 2, textureSize.x, textureSize.y));
					select_pos = 0;
					break;

			default:
				break;
			}

			clock.restart();
		}
		//renderWindow.clear();
		//renderWindow.display();
		renderWindow.draw(player);
		renderWindow.display();
	}
}

