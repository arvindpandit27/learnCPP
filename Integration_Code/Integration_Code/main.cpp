#include <SFML/Graphics.hpp.>
#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace sf;

int rolldice()
{
	int dice_value;
	dice_value = (rand() % 5) + 1;
	if (dice_value == 5)
	{
		dice_value = 8;
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
		User[i].colourName = name;
	}

	sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chowka Bhaara");

	sf::Event event;

	sf::CircleShape square(100, 4);
	sf::RectangleShape sq(Vector2f{ 75,75 });
	square.setRotation(45);


	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}
		renderWindow.clear();

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				sq.setFillColor(sf::Color(192, 192, 192));
				sq.setPosition({ (float)(77 * i + 100), (float)(77 * j + 100) });
				renderWindow.draw(sq);
			}
				// renderwindow.draw(line ,2, sf::lines);
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

	char keyboard_input;
	int ascii_code;
	int dice_value;
	while (1)
	{
		for (int i = 0; i < NPlayers; i++)
		{
			cout << User[i].name << " "
				<< "Press r to roll dice" << endl;
			cin >> keyboard_input;
			ascii_code = (int)keyboard_input;
			
			if (ascii_code == 82 || ascii_code == 114)
			{
				dice_value = rolldice();
				if (dice_value == 4 || dice_value == 8)
				{
					User[i].Coin[0].x = 1;
					User[i].Coin[0].y = 3;
					cout << "CHOWKA BARA : You can move your pawn out of quarantine" << endl;
				}
				end_game = 0;
			}
			else
			{
				cout << "r wasn't entered" << endl;
				end_game = 1;
				break;
			}
		}
		if (end_game == 1)
		{
			break;
		}
	}
	return 0;
}
