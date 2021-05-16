#include <SFML/Graphics.hpp.>
#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "CheckUserInputs.hpp"

using namespace sf;

int rolldice()
{
	int dice_value;
	char keyboard_input;
	int ascii_code;

	cout << "Press r to roll dice" << endl;
	cin >> keyboard_input;
	ascii_code = (int)keyboard_input;

	if (ascii_code == 82 || ascii_code == 114)
	{
		dice_value = (rand() % 5) + 1;
		if (dice_value == 5)
		{
			dice_value = 8;
		}
	}
	else
	{
		cout << "r wasn't entered" << endl;
		dice_value = 0;
	}
	return dice_value;
}



int main(int argc, char** argv)
{
	srand((unsigned)time(0));
	int NPlayers;
	cout << "Enter number of players" << endl;
	cin >> NPlayers;
	Player* User;
	User = new Player[NPlayers];
	//Player User[NPlayers];
	Player PlayerA;
	Coins Coin[4];
	bool end_game;

	for (int i = 0; i < NPlayers; i++)
	{
		string name;
		cout << "Enter"
			<< " " << i + 1 << " "
			<< "player's name" << endl;
		cin >> name;
		User[i].name = name;
		cout << "Choose the color RED, BLUE, GREEN OR YELLOW" << endl;
		cout << "Enter"
			<< " " << i + 1 << " "
			<< " player colour" << endl;
		cin >> name;

		while (CheckColorValidity(name, i, User)) {
			cin >> name;
		}
		User[i].colourName = name;
	}

	sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chowka Bhaara");

	sf::Event event;

	sf::CircleShape square(100, 4);
	sf::RectangleShape sq(Vector2f{ 100,100 });
	square.setRotation(45);


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
				if (((i % 2 == 0) && (j % 2 != 0)) || ((i % 2 != 0) && (j % 2 == 0))) {
					sq.setFillColor(sf::Color(245, 222, 179));
				}
				else {
					sq.setFillColor(sf::Color(218, 165,32));
				}

				sq.setPosition({ (float)(100 * i + 100), (float)(100.0 * j + 100) });
				renderWindow.draw(sq);

				// renderwindow.draw(line ,2, sf::lines);
			}
		}
		// line->a = 10;
	   // renderWindow.draw(line, 2, sf::Lines); 
		// renderWindow.draw(lines);//Chetan
		 //circleShape.setPosition({ 0,500 });
		 //renderWindow.draw(circleShape);
		 //rectShape.setPosition({ 0,100 });
		 //renderWindow.draw(rectShape);
		 //renderWindow.draw(triangle);
		 //renderWindow.draw(square);
		renderWindow.display();
	}

	int dice_value;
	while (1)
	{
		for (int i = 0; i < NPlayers; i++)
		{
			cout << User[i].name << "'s turn" << endl;
			do {
				dice_value = rolldice();
				cout << dice_value << endl;
				User[i].Coin[0].x = 1;
				User[i].Coin[0].y = 3;
				end_game = 0;
			} while (dice_value == 4 || dice_value == 8 || dice_value == 0);
		}
		if (end_game == 1)
		{
			break;
		}
	}
	return 0;
}
