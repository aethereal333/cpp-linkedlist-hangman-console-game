#pragma once
#include "Linkedlist.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
class Game {
	LinkedList* alphabet, * guestedWord, *history;
	string hiddenWord, playerName;
	int chances, undoChances, score, clueChances, limit;
	bool checkWord;
public:
	Game();
	~Game();
	void read_from_file(string filename);
	void to_lower(char character);
	void choose_hidden_word();
	bool check_hidden_word(char word);
	void guess_word(char word);
	void show_clue();
	void load_highscore_from_textfile(string filename = "highscore.txt");
	void save_highscore_to_textfile(string filename = "highscore.txt");
	void print_word();
	void gotoxy(int x, int y);
	bool game_over();
	void print_hangman();
	void print_guessed_words();
	void undo();
	void run();
};