#include "Game.h"
Game::Game() {
	score = 0;								
	chances = 6;							
	limit = 3;
	undoChances = 3;							
	clueChances = 3;
	alphabet = new LinkedList();			
	guestedWord = new LinkedList();			
	history = new LinkedList();
	hiddenWord = "";						
	checkWord = false;										
}
Game::~Game() { 
	free(alphabet); 
	free(guestedWord); 
}
void Game::gotoxy(int x, int y) { 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}
void Game::read_from_file(string filename) {
	string word;
	int random = 0, lines = 0;
	ifstream File(filename);
	random = rand() % 132 + 1;
	while (getline(File, word)) {
		++lines;
		if (lines == random) { hiddenWord = word; }
	}
}
void Game::to_lower(char character) { 
	if (character < 91 && character >= 65) { 
		character += 32; 
	} 
}
void Game::choose_hidden_word() {
	if (hiddenWord != "") {
		for (int i = 0; i < hiddenWord.length(); i++) { 
			history->add_value(hiddenWord[i]); 
		}
	}
	read_from_file("wordlist.txt");
	if (guestedWord->length() > 0) { 
		guestedWord->reset(); 
	}
	if (alphabet->length() > 0) { 
		alphabet->reset(); 
	}
	for (int i = 0; i < hiddenWord.length(); i++) { 
		guestedWord->add_value('_'); 
	}
}
bool Game::check_hidden_word(char word) {
	int check = 0;
	for (int i = 0; i < hiddenWord.length(); i++) {
		if (word == hiddenWord[i]) {
			guestedWord->edit_value(word, i);
			check = 1;
		}
	}
	if (check == 1) { return true; }
	else { return false; }
}
void Game::guess_word(char word) {
	if (alphabet->check_guested_word(word)) {
		cout << word << " has already been guessed!\n\n";
		return;
	}
	alphabet->add_value(word);
	if (!check_hidden_word(word)) {
		chances--;
	}
}
void Game::show_clue() {
	int random = rand() % hiddenWord.length();
	if (clueChances == 0) { cout << "\nOut of chance to show clue . . .\n\n"; }
	else {
		while (alphabet->check_guested_word(hiddenWord[random])) {
			random = rand() % hiddenWord.length();
		}
		for (int i = 0; i < hiddenWord.length(); i++) {
			if (i == random && guestedWord->check_guess()) {
				check_hidden_word(hiddenWord[i]);
				alphabet->add_value(hiddenWord[i]);
			}
		}
		clueChances--;
	}
}
void Game::print_word() { guestedWord->print(); cout << endl; }
void Game::save_highscore_to_textfile(string filename) {
	ofstream file(filename, ios::app);
	if (file.is_open()) {
		vector<pair<int, string>> score_vector;
		file << playerName << " " << score << "\n";
		file.close();
	}
	file.close();
}
void Game::load_highscore_from_textfile(string filename) {
	ifstream file(filename);
	int scores, count = 1;
	string player;
	if (file.is_open()) {
		vector<pair<int, string>> score_vector;
		while (file >> player >> scores) { score_vector.push_back(make_pair(scores, player)); }
		file.close();
		sort(score_vector.begin(), score_vector.end());
		reverse(score_vector.begin(), score_vector.end());
		for (auto i = score_vector.begin(); i != score_vector.end() && count <= 10; ++i) {
			gotoxy(0, count + 1); cout << count << ". " << i->second;
			gotoxy(15, count + 1); cout << "Score : " << i->first << endl;
			count++;
		}
	}
	file.close();
}
bool Game::game_over() {
	if (chances == 0) {
		cin.ignore();
		do {
			system("cls");
			print_hangman();
			cout << "You Lose\n\n"
				<< "The Word is *** " << hiddenWord << " ***\n\n"
				<< "Player Name (MAX 10) : "; getline(cin, playerName);
			cout << "\n";
		} while (playerName.size() > 10);
		save_highscore_to_textfile();
		return true;
	}
	else if (guestedWord->check_guess()) { return false; }
	else {
		score += hiddenWord.length();
		cout << "\nWow, Gratz! You win this time!\n" << endl;
		system("pause>nul | echo Let's see if you can win the next one!");
		choose_hidden_word();
		return false;
	}
}
void Game::print_hangman() {
	cout << endl;
	cout << "Score         : " << score << endl
		<< "\nHealth        : " << chances
		<< "\t\tUndo Chance       : " << undoChances
		<< "\n\nClue Chance   : " << clueChances
		<< "\t\tChange Word Limit : " << limit << endl << endl;
	switch (chances)
	{
	case 6:
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;

	case 5:
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |     O " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;

	case 4:
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |     O " << endl;
		cout << "       |     | " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;

	case 3:
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |     O " << endl;
		cout << "       |    /|" << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;

	case 2:
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |     O " << endl;
		cout << "       |    /|\\" << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;

	case 1:
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |     O " << endl;
		cout << "       |    /|\\" << endl;
		cout << "       |    /  " << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;

	case 0:
		system("cls");
		cout << "       ______  " << endl;
		cout << "       |     | " << endl;
		cout << "       |     O " << endl;
		cout << "       |    /|\\" << endl;
		cout << "       |    / \\" << endl;
		cout << "       |       " << endl;
		cout << "       |       " << endl;
		cout << "  _____|______ " << endl;
		cout << " |___________| " << endl;
		cout << "               " << endl;
		break;
	}
}
void Game::print_guessed_words() {
	cout << "\nGuessed Words : ";
	alphabet->print();
	cout << endl;
}
void Game::undo() {
	if (undoChances > 0) {
		if (alphabet->length() > 0 && chances < 6) {
			bool temp = false;
			char s = alphabet->get_tail_node();
			for (int i = 0; i < hiddenWord.length(); i++) {
				if (s == hiddenWord[i]) {
					guestedWord->edit_value('_', i);
					temp = true;
				}
			}
			if (temp == false) { 
				chances++; 
			}
			alphabet->del();
			undoChances--;
		}
	}
	else { cout << "\nOut of chance to undo . . .\n\n"; }
}
void Game::run() {
	char word;
	int choice;
	cout << "Top 10 Leaderboards";
	load_highscore_from_textfile();
	cout << "\n";
	system("pause");
	choose_hidden_word();
	while (!game_over()) {
		system("CLS");
		print_word();
		print_guessed_words();
		print_hangman();
		cout << "1. Guess\t" << "2. Undo\t\t" << "3. Clue\t\t" << "4. Change Word\t\t" << "0. Exit\n\n"
			<< "Choice : "; cin >> choice;
		if (choice == 0) { _Exit(0); }
		else if (choice == 1) {
			cout << "\nGuess an alphabet (a-z) : ";
			cin >> word;
			tolower(word);
			guess_word(word);
			cout << "\n";
		}
		else if (choice == 2) { 
			undo(); 
		}
		else if (choice == 3) { 
			show_clue();
		}
		else if (choice == 4) {
			if (limit == 0) { 
				cout << "\nOut of chance to change words . . .\n\n"; 
			}
			else { 
				choose_hidden_word(); 
				limit--; 
			}
		}
		system("pause");
	}
}