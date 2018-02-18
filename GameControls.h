#ifndef GAMECONTROLS_H
#define GAMECONTROLS_H
#include <iostream>
#include <Windows.h>
#include <deque>
#include <algorithm>
#include <deque>
#include <ctime>
#include <cstdlib>
//#include <MMSystem.h>
#include <string>
#include <conio.h>
struct Snakecoord
{
	int x, y;
	bool operator ==(Snakecoord right) { return (x == right.x && y == right.y); }	// return true if two snakes are in same coord (have to overload == for algorithm lib)
};

class GameControls
{
public:
	void display_menu();
	int get_number_of_players();
	int get_speed();
	void play_game_one_player(int speed);
	void play_game_two_players(int speed);

private:
	void gotoxy(int x, int y);
	void hide_cursor();
	void player_lost(std::deque<Snakecoord> player1);
	void player_lost(int player_number, std::deque<Snakecoord> player1, std::deque<Snakecoord>player2);
	void clear_message(char My_map[][22]);
	void setup_snake(int x, int y, std::deque<Snakecoord>& My_snake);
	void setup_map(char My_map[][22], std::deque<Snakecoord> player1, int& number_of_apples);	// 1 snake
	void setup_map(char My_map[][22], std::deque<Snakecoord> player1, std::deque<Snakecoord> player2, int& number_of_apples);	// 2 snakes
	void move_snake(std::deque<Snakecoord>& player, int x_direct_player, int y_direct_player, int player_number);
	void spawn_apple(char My_map[][22], std::deque<Snakecoord> player1,int& number_of_apples); // 1 snake
	void spawn_apple(char My_map[][22], std::deque<Snakecoord> player1, std::deque<Snakecoord> player2, int& number_of_apples);	// 2 snakes
	bool check_if_hit(char My_map[][22], std::deque<Snakecoord>& player1, int& number_of_apples);	// 1 snake
	bool check_if_hit(char My_map[][22], std::deque<Snakecoord>& player1, std::deque<Snakecoord>& player2, int& number_of_apples);	// 2 snakes
	bool user_wishes_to_continue();
	void reset_game(char My_map[][22], std::deque<Snakecoord>& player1, int& number_of_apples);	// 1 snake
	void reset_game(char My_map[][22], std::deque<Snakecoord>& player1, std::deque<Snakecoord>& player2, int& number_of_apples);	// 2 snakes
};


#endif
