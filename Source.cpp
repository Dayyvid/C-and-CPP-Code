#include <iostream>
#include <Windows.h>
#include <deque>
#include <deque>
#include "GameControls.h"
#include <string>
using namespace std;

int main()
{
	int num_of_players, speed;
	GameControls GameControls;

	/**************************************************************
	To Do List: 
	- Make the user wishes to continue function in
	 main instead of in play_game_#_player function
	- More snakes? Different snake types
	***************************************************************/
	GameControls.display_menu();
	num_of_players = GameControls.get_number_of_players();
	speed = GameControls.get_speed();

	if (num_of_players == 1)
	{
		GameControls.play_game_one_player(speed);
	}
	else
	{
		GameControls.play_game_two_players(speed);
	}
}