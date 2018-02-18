#include "GameControls.h"

/******************************
		Public Functions
******************************/

void GameControls::display_menu()
{
	using namespace std;
	hide_cursor();
	int num_players, speed;
	gotoxy(0, 0);
	cout << "Hi! Welcome to my snake game."<< endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "Warning";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << ": this game contains sounds." << endl;
	cout << "Press Enter to start!" << endl;
	/****
	gotoxy(0, 1);
	cout << "         /^\/^\\" << endl
		<< "        |__| O|_" << endl
		<< "\\/     /~   \\_/  \\" << endl
		<< " \\____|__________/  \\" << endl
		<< "        \\_______      \\" << endl
		<< "                `\     \\                    \\" << endl
		<< "                 |     |                    \\" << endl
		<< "                /      /                     \\\\" << endl
		<< "               /     /                        \\\\" << endl
		<< "              /      /                         \\ \\" << endl
		<< "             /     /                            \\  \\" << endl
		<< "            /     /             _----_            \\  \\" << endl
		<< "           /     /           _-~      ~-_          |  |" << endl
		<< "           (      (        _-~    _--_    ~-_     _/   |" << endl
		<< "            \\      ~-____-~    _-~    ~-_    ~-_-~    /" << endl
		<< "              ~-_           _-~          ~-_       _-~   - art by jurcy -" << endl
		<< "                ~--______-~                ~-___-~" << endl;
	**/
	while (1)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			break;
		}
	}
}

int GameControls::get_number_of_players()
{
	using namespace std;
	int arrow_position = 1;

	Sleep(750);		// sleep to ignore the enter key from the display menu enter press.
	system("cls");
	gotoxy(0, 0);
	cout << "Choose the amount of players" << endl;
	gotoxy(0, 1);
	cout << ">";
	gotoxy(3, 1);
	cout << "1 player";
	gotoxy(3, 2);
	cout << "2 players";
	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN)|| GetAsyncKeyState(VK_UP))		
		{
			gotoxy(0, arrow_position);
			cout << " ";
			gotoxy(0, arrow_position % 2 + 1);		//if at 1, then go to 2. If at 2, then go to 1.
			cout << ">";
			arrow_position = arrow_position % 2 + 1;	// update new arrow position
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			return arrow_position;
		}
		Sleep(250);
	}
}

int GameControls::get_speed()
{
	using namespace std;
	int speed;
	Sleep(750);
	system("cls");
	gotoxy(0, 0);
	cout << "Enter your desired refresh rate(25-500): ";
	cin >> speed;


	while (speed < 25 || speed > 500)
	{
		gotoxy(0, 0);
		Sleep(300);
		cout << "Please enter a valid number!             ";
		Sleep(1000);
		gotoxy(0, 0);
		system("cls");		// clears screen
		cout << "Enter your desired refresh rate(25-500): ";
		gotoxy(42, 0);
		cin >> speed;
		cin.clear();
		cin.ignore(999, '\n');
		fflush(stdin);
	}

	return speed;
}

void GameControls::play_game_one_player(int speed)
{
	using namespace std;

	bool user_wants_to_continue = false;
	deque<Snakecoord> player1;
	char My_map[80][22];	//map 80x22
	int player1_x_direct = 0, player1_y_direct = 0;
	int number_of_apples = 0, apple_counter = 0;
	Sleep(500);		//ignore enter keypress from earlier set speed
	reset_game(My_map, player1, number_of_apples);

	while (1)
	{

		if (GetAsyncKeyState(VK_UP))	// Up
		{
			if (player1_y_direct == 0)
			{
				player1_x_direct = 0;
				player1_y_direct = -1;
			}
		}
		if (GetAsyncKeyState(VK_DOWN)) // Down
		{
			if (player1_y_direct == 0)
			{
				player1_x_direct = 0;
				player1_y_direct = 1;
			}
		}
		if (GetAsyncKeyState(VK_LEFT))	// Left
		{
			if (player1_x_direct == 0)
			{
				player1_x_direct = -1;
				player1_y_direct = 0;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) // Right
		{
			if (player1_x_direct == 0)
			{
				player1_x_direct = 1;
				player1_y_direct = 0;
			}
		}
		move_snake(player1, player1_x_direct, player1_y_direct, 1);
		if (check_if_hit(My_map, player1, number_of_apples))
		{
			if (user_wishes_to_continue())
			{
				reset_game(My_map, player1, number_of_apples);
				player1_x_direct = player1_y_direct = 0;
			}
			else
			{
				break;
			}
		}

		if ((number_of_apples < 1) || (number_of_apples < 6 && apple_counter >= 50))	// pawns an apple if less than 1 apple, or less than 6 apples and timer is up
		{
			spawn_apple(My_map, player1, number_of_apples);
			apple_counter = 0;
		}
		apple_counter += 1;
		Sleep(speed);
	}
}

void GameControls::play_game_two_players(int speed)
{
	using namespace std;

	GameControls GameControls;

	bool user_wants_to_continue = false;
	deque<Snakecoord> player1, player2;
	char My_map[80][22];	//map 80x22
	int player1_x_direct = 0, player1_y_direct = 0, player2_x_direct = 0, player2_y_direct = 0;
	int number_of_apples = 0, apple_counter = 0;
	Sleep(500);//ignore enter keypress from earlier set speed
	reset_game(My_map, player1, player2, number_of_apples);

	while (1)
	{
		if (GetAsyncKeyState(0x57))	//W
		{
			if (player1_y_direct == 0)
			{
				player1_x_direct = 0;
				player1_y_direct = -1;
			}
		}
		if (GetAsyncKeyState(0x53)) //S
		{
			if (player1_y_direct == 0)
			{
				player1_x_direct = 0;
				player1_y_direct = 1;
			}
		}
		if (GetAsyncKeyState(0x41))	// A
		{
			if (player1_x_direct == 0)
			{
				player1_x_direct = -1;
				player1_y_direct = 0;
			}
		}
		if (GetAsyncKeyState(0x44)) //D
		{
			if (player1_x_direct == 0)
			{
				player1_x_direct = 1;
				player1_y_direct = 0;
			}
		}

		/**************************
		Player 2 Controls
		**************************/

		if (GetAsyncKeyState(VK_UP))	// Up
		{
			if (player2_y_direct == 0)
			{
				player2_x_direct = 0;
				player2_y_direct = -1;
			}
		}
		if (GetAsyncKeyState(VK_DOWN)) // Down
		{
			if (player2_y_direct == 0)
			{
				player2_x_direct = 0;
				player2_y_direct = 1;
			}
		}
		if (GetAsyncKeyState(VK_LEFT))	// Left
		{
			if (player2_x_direct == 0)
			{
				player2_x_direct = -1;
				player2_y_direct = 0;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) // Right
		{
			if (player2_x_direct == 0)
			{
				player2_x_direct = 1;
				player2_y_direct = 0;
			}
		}
		move_snake(player1, player1_x_direct, player1_y_direct, 1);
		move_snake(player2, player2_x_direct, player2_y_direct, 2);

		if (check_if_hit(My_map, player1, player2, number_of_apples))
		{
			if (user_wishes_to_continue())
			{
				reset_game(My_map, player1, player2, number_of_apples);
				player1_x_direct = player1_y_direct = player2_x_direct = player2_y_direct = 0;
			}
			else
			{
				break;
			}
		}

		if ((number_of_apples < 1) || (number_of_apples < 6 && apple_counter >= 50))	// pawns an apple if less than 1 apple, or less than 6 apples and timer is up
		{
			spawn_apple(My_map, player1, number_of_apples);
			apple_counter = 0;
		}
		apple_counter += 1;
		Sleep(speed);
	}
}

/******************************
	Private Functions
******************************/

void GameControls::gotoxy(int x, int y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameControls::hide_cursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;			//hides the cursor from appearing on screen
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void GameControls::player_lost(std::deque<Snakecoord> player1)
{
	using namespace std;
	//PlaySound(TEXT("Sounds/SadTrombone.wav"), NULL, SND_ASYNC);
	gotoxy(0, 23);
	cout << "You lost!" << endl;
	cout << "You picked up " << player1.size() - 1 << " apples" << endl;
}

void GameControls::player_lost(int player_number, std::deque<Snakecoord> player1, std::deque<Snakecoord>player2)
{
	using namespace std;
	//PlaySound(TEXT("Sounds/SadTrombone.wav"), NULL, SND_ASYNC);
	if (player_number == 1)
	{
		gotoxy(0, 23);
		cout << "Player 1 has lost!" << endl;
		cout << "Player 1 has picked up " << player1.size() - 1 << " apples" << endl;
		cout << "Player 2 has picked up " << player2.size() - 1<< " apples" << endl;
	}
	else
	{
		gotoxy(0, 23);
		cout << "Player 2 has lost!" << endl;
		cout << "Player 1 has picked up " << player1.size() - 1<< " apples" << endl;
		cout << "Player 2 has picked up " << player2.size() - 1<< " apples" << endl;
	}
}

void GameControls::clear_message(char My_map[][22])
{
	using namespace std;		//clears the messages under the play area
	for (int i = 22; i < 26; i++)
	{
		gotoxy(0, i);
		cout << "                                                                        ";
	}
}

void GameControls::setup_snake(int x, int y, std::deque<Snakecoord>& My_snake)
{
	Snakecoord temp;
	temp.x = x;
	temp.y = y;
	My_snake.push_back(temp);
}

void GameControls::setup_map(char My_map[][22], std::deque<Snakecoord> player1, int& number_of_apples)
{
	using namespace std;
	int randomx, randomy;
	srand(time(NULL));
	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			if (x == 0 || x == 79 || y == 0 || y == 21)	//draw boundaries
			{
				My_map[x][y] = '-';
			}
			else
			{
				My_map[x][y] = ' ';
			}
			gotoxy(x, y);
			cout << My_map[x][y];
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	gotoxy(player1[0].x, player1[0].y);
	cout << 'O';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	while (number_of_apples < 6)
	{
		spawn_apple(My_map, player1, number_of_apples);
	}
}

void GameControls::setup_map(char My_map[][22], std::deque<Snakecoord> player1, std::deque<Snakecoord> player2, int& number_of_apples)		//overloaded setup for 2 players
{
	using namespace std;
	int randomx, randomy;
	srand(time(NULL));
	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			if (x == 0 || x == 79 || y == 0 || y == 21)	//draw boundaries
			{
				My_map[x][y] = '-';
			}
			else
			{
				My_map[x][y] = ' ';
			}
			gotoxy(x, y);
			cout << My_map[x][y];
		}
	}

	for (int i = 0; i < player1.size(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		gotoxy(player1[i].x, player1[i].y);
		cout << 'O';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	for (int i = 0; i < player2.size(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		gotoxy(player2[i].x, player2[i].y);
		cout << 'O';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	while (number_of_apples < 6)
	{
		spawn_apple(My_map, player1, player2, number_of_apples);
	}

}

void GameControls::move_snake(std::deque<Snakecoord>& player, int x_direct_player, int y_direct_player, int player_number)
{
	using namespace std;

	int new_head_x, new_head_y;
	int tailx = player[player.size() - 1].x;
	int taily = player[player.size() - 1].y;

	gotoxy(tailx, taily);	//go to tail
	cout << ' ';	//set it to empty

	new_head_x = player[0].x + x_direct_player;			//get new head coord
	new_head_y = player[0].y + y_direct_player;

	Snakecoord temp;
	temp.x = new_head_x;
	temp.y = new_head_y;

	player.push_front(temp);	//insert new head into beginning of deque
	player.pop_back();			//remove the old tail

	if (player_number == 1)		//if 1st player
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	}
	else						//if 2nd player
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	}
	gotoxy(new_head_x, new_head_y);
	cout << 'O';						//draw head
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void GameControls::spawn_apple(char My_map[][22], std::deque<Snakecoord> player1, int& number_of_apples)
{
	using namespace std;
	int randomx, randomy;

	do
	{
		randomx = 1 + (rand() % 79);
		randomy = 1 + (rand() % 21);
	} while (My_map[randomx][randomy] != ' ' || (randomx == player1[0].x && randomy == player1[0].y));	//get random coord for apple

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	My_map[randomx][randomy] = '@';
	gotoxy(randomx, randomy);
	cout << '@';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	number_of_apples += 1;
}


void GameControls::spawn_apple(char My_map[][22], std::deque<Snakecoord> player1, std::deque<Snakecoord> player2, int& number_of_apples)
{
	using namespace std;
	int randomx, randomy;

	do
	{
		randomx = 1 + (rand() % 79);
		randomy = 1 + (rand() % 21);
	} while (My_map[randomx][randomy] != ' ' || (randomx == player1[0].x && randomy == player1[0].y) || (randomx == player2[0].x && randomy == player2[0].y));	//get random coord for apple

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	My_map[randomx][randomy] = '@';
	gotoxy(randomx, randomy);
	cout << '@';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	number_of_apples += 1;
}

bool GameControls::check_if_hit(char My_map[][22], std::deque<Snakecoord>& player1, int& number_of_apples)
{
	using namespace std;

	int randomx, randomy;
	Snakecoord p1_headcoord;
	p1_headcoord.x = player1[0].x;	//get head coord for player 1
	p1_headcoord.y = player1[0].y;

	deque<Snakecoord>::iterator p1_finder;

	/**************************************************
	Check losing conditions
	**************************************************/

	if (My_map[p1_headcoord.x][p1_headcoord.y] == '-')	// if a snake hit the border
	{
		player_lost(player1);	// player_lost takes int player
		return true;
	}
	if (player1.size() > 3)			// if player1 hit itself
	{
		p1_finder = find(player1.begin() + 1, player1.end(), p1_headcoord);		//if head coord already exists inside of snake
		if (p1_finder != player1.end())
		{
			player_lost(player1);
			return true;
		}
	}

	/**************************************************
	Check if snake ate an apple
	**************************************************/
	if (My_map[p1_headcoord.x][p1_headcoord.y] == '@')	//if player 1 ate an apple
	{
		My_map[p1_headcoord.x][p1_headcoord.y] = ' ';	//set empty
		Snakecoord temp;
		temp.x = player1[player1.size() - 1].x;
		temp.y = player1[player1.size() - 1].y;
		player1.push_back(temp);	//push back old coordinates

		number_of_apples -= 1;
	}
	return false;
}

bool GameControls::check_if_hit(char My_map[][22], std::deque<Snakecoord>& player1, std::deque<Snakecoord>& player2, int& number_of_apples)
{
	using namespace std;
	int randomx, randomy;
	Snakecoord p1_headcoord;
	p1_headcoord.x = player1[0].x;	//get head coord for player 1
	p1_headcoord.y = player1[0].y;

	Snakecoord p2_headcoord;
	p2_headcoord.x = player2[0].x;	//head coord for player 2
	p2_headcoord.y = player2[0].y;

	deque<Snakecoord>::iterator p1_finder;
	deque<Snakecoord>::iterator p2_finder;

	/**************************************************
		Check losing conditions 
	**************************************************/

	/******************************************************
		To make better code, instead of using an iterator,
		could change the map to actually hold 'O' (instead of just printing 'O' out on the board)
		then check if headcoord of p1 is at an O
	******************************************************/
	p1_finder = find(player2.begin(), player2.end(), p1_headcoord);	// find if p1 head coord is in p2

	if (p1_finder != player2.end())
	{
		player_lost(1, player1, player2);
		return true;
	}

	p2_finder = find(player1.begin(), player1.end(), p2_headcoord); // find if p2 head coord is in p1
	if (p2_finder != player1.end())
	{
		player_lost(2, player1, player2);
		return true;
	}

	else if (My_map[p1_headcoord.x][p1_headcoord.y] == '-' || My_map[p2_headcoord.x][p2_headcoord.y] == '-')	// if a snake hit the border
	{
		if (My_map[p1_headcoord.x][p1_headcoord.y] == '-')
		{
			player_lost(1, player1, player2);
		}
		else
		{
			player_lost(2, player1, player2);
		}
		return true;
	}
	if (player1.size() > 3)			// if player1 hit itself
	{
		p1_finder = find(player1.begin() + 1, player1.end(), p1_headcoord);
		if (p1_finder != player1.end())
		{
			player_lost(1, player1, player2);
			return true;
		}
	}
	if (player2.size() > 3)			// if player 2 hit itself
	{
		p2_finder = find(player2.begin() + 1, player2.end(), p2_headcoord);
		if (p2_finder != player2.end())
		{
			player_lost(2, player1, player2);
			return true;
		}
	}

	/**************************************************
		Check if snake ate an apple
	**************************************************/
	if (My_map[p1_headcoord.x][p1_headcoord.y] == '@')	//if player 1 ate an apple
	{
		My_map[p1_headcoord.x][p1_headcoord.y] = ' ';	//set empty
		Snakecoord temp;
		temp.x = player1[player1.size() - 1].x;
		temp.y = player1[player1.size() - 1].y;
		player1.push_back(temp);	//push back old coordinates
		
		number_of_apples -= 1;
	}
	else if (My_map[p2_headcoord.x][p2_headcoord.y] == '@') //if player 2 ate an apple
	{
		My_map[p2_headcoord.x][p2_headcoord.y] = ' ';	//set empty
		Snakecoord temp;
		temp.x = player2[player2.size() - 1].x;
		temp.y = player2[player2.size() - 1].y;
		player2.push_back(temp);	//pushes back old coordinates

		do
		{
			randomx = 1 + (rand() % 79);
			randomy = 1 + (rand() % 21);
		} while (My_map[randomx][randomy] != ' ');	//get random coord for apple
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		My_map[randomx][randomy] = '@';
		gotoxy(randomx, randomy);
		cout << '@';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |FOREGROUND_BLUE | FOREGROUND_GREEN);
	}
	return false;
}
bool GameControls::user_wishes_to_continue()
{
	using namespace std;
	char test;

	gotoxy(0, 28);
	cout << "                                                                        "<<endl;	//clear message
	cout << "                                                                        ";	//clear message
	gotoxy(0, 26);
	Sleep(1000);
	cout << "Press Enter to play again, else press Escape to stop playing ";

	while (1)
	{
		// & 0x8000 to check signed bit(if key is being pressed down at the exact moment). Had issues where if didnt include the 0x8000 would check the buffer? to see if enter was pressed earlier
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			return true;
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			cout << endl;		// gets the "Press anything to continue..." on next line
			return false;
		}
	}	

}

void GameControls::reset_game(char My_map[][22], std::deque<Snakecoord>& player1, int& number_of_apples)
{
	using namespace std;
	midiOutSetVolume(NULL, 0);
	srand(time(NULL));
	player1.clear();	// empty the snake vector
	system("cls");
	number_of_apples = 0; // sets number of apples back to 0
	setup_snake(rand() % 78 + 1, rand() % 20 + 1, player1);	// x coord(1-78), y coord 1 - 20
	setup_map(My_map, player1, number_of_apples);

	gotoxy(0, 23);
	cout << "Press enter to begin!";
	while (1)
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			gotoxy(0, 23);
			cout << "                        ";
			break;
		}
	}

	for (int i = 3; i > 0; i--)
	{
		gotoxy(0, 23);
		cout << i << endl;
		Sleep(1000);
	}
	gotoxy(0, 23);
	cout << "Go!" << endl;
	//PlaySound(TEXT("Sounds/KirbyDreamland.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void GameControls::reset_game(char My_map[][22], std::deque<Snakecoord>& player1, std::deque<Snakecoord>& player2, int& number_of_apples)
{
	using namespace std;

	srand(time(NULL));
	player1.clear();
	player2.clear();
	system("cls");
	setup_snake(rand() % 78 + 1, rand() % 20 + 1, player1);	// x coord(1-78), y coord 1 - 23
	setup_snake(rand() % 78 + 1, rand() % 20 + 1, player2);
	number_of_apples = 0;
	setup_map(My_map, player1, player2, number_of_apples);

	gotoxy(0, 23);
	cout << "Press enter to begin!";
	while (1)
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			gotoxy(0, 23);
			cout << "                        ";
			break;
		}
	}
	for (int i = 3; i > 0; i--)
	{
		gotoxy(0, 23);
		cout << i << endl;
		Sleep(1000);
	}
	gotoxy(0, 23);
	cout << "Go!" << endl;
	//PlaySound(TEXT("Sounds/KirbyDreamland.wav"), NULL, SND_ASYNC | SND_LOOP);
}
