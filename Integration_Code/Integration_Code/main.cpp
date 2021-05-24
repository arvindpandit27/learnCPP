#include <SFML/Graphics.hpp.>
#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>


using namespace sf;
using namespace std::literals::chrono_literals;

char keyboard_input;
int ascii_code;
int dice_value;
bool end_game;
int NPlayers;
Player* User;

static bool Finished = false;

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


void BoardGraphics() {
	sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chowka Bhaara");

	sf::Event event;

	sf::CircleShape square(100, 4);
	sf::RectangleShape sq(Vector2f{ 100,100 });
	sf::RectangleShape rectangle1(sf::Vector2f(4, 100 * (float) sqrt(2))); // change the size to 100x100 rectangle.setSize(sf::Vector2f(100, 100));
	sf::RectangleShape rectangle2(sf::Vector2f(4, 100 * (float) sqrt(2)));
	square.setRotation(45);
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
		renderWindow.display();
	}
}

void GamePlay() {
	while (!Finished)
	{
		cout << "Game play working..." << endl;
		std::this_thread::sleep_for(1s);
		//for (int i = 0; i < NPlayers; i++)
		//{
		//	cout << User[i].name << " "
		//		<< "Press r to roll dice" << endl;
		//	cin >> keyboard_input;
		//	ascii_code = (int)keyboard_input;

		//	if (ascii_code == 82 || ascii_code == 114)
		//	{
		//		dice_value = rolldice();
		//		if (dice_value == 4 || dice_value == 8)
		//		{
		//			User[i].Coin[0].x = 1;
		//			User[i].Coin[0].y = 3;
		//			cout << "CHOWKA BARA : You can move your pawn out of quarantine" << endl;
		//		}
		//		end_game = 0;
		//	}
		//	else
		//	{
		//		cout << "r wasn't entered" << endl;
		//		end_game = 1;
		//		break;
		//	}
		//}
		//if (end_game == 1)
		//{
		//	break;
		//}
	}
}

int main(int argc, char** argv)
{

	srand((unsigned)time(0));
	cout << "Enter number of players" << endl;
	cin >> NPlayers;
	User = new Player[NPlayers];
	Player PlayerA;
	Coins Coin[4];

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

	thread t1(BoardGraphics);
	thread t2(GamePlay);


	t1.join();
	t2.join();


	return 0;
}
