/*The code below is for the tic - tac - toe game
  For more, read the readme file.
  All rights reserved.
  Enjoy!
*/
#include <iostream>
#include <string>

using namespace std;

void create_tab(string tab[9][9], int state_tab[8][8]) { //creating a new tab
	for (int i = 1; i < 9; i++) { //creating a legend
		tab[0][i] = "   ";
		tab[0][i] += char(i + 64); //cast int to char
		tab[i][0] = to_string(i); //cast int to string
	}
	for (int i = 1; i < 9; i++) {  //creating the map
		for (int j = 1; j < 9; j++) {
			if (j == 8) {
				tab[i][j] = "|___| ";
			}
			else {
				tab[i][j] = "|___";
			}
		}
	}
	for (int i = 0; i < 8; i++) { //creating the state tab
		for (int j = 0; j < 8; j++) {
			state_tab[i][j] = 0;
		}
	}
}
void print_tab(string tab[9][9]) {  //showing the map
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j == 8) {
				cout << tab[i][j] << endl;
			}
			else {
				cout << tab[i][j];
			}
		}
	}
}

class Player {
     private:
		 int *x_ = new int;  //horizontal position
		 int *y_ = new int;  //vertical position
		 int *choice_ = new int; //character selection(X or O)
		 bool *p_ = new bool;  //auxiliary variable
     public:
		 Player(int choice) {
            * choice_ = choice;
		 }
		 bool collide(int state_tab[8][8]) {    //checks if position chosen by the player collides with positions in the map
			 if (state_tab[*y_][*x_] == 0) {
				 return true;
			 }
			 else {
				 return false;
			 }
		 }

		 void print_instuctrions(int state_tab[8][8]) {  //showing specific instructions in case of collide
			 if (*choice_ == 1) { //X case
				 if (state_tab[*y_][*x_] == 1) {
					 cout << "Nie możesz ustawić krzyżyka na krzyżyku!!, Podaj pozycje jeszcze raz" << endl;  
				 }
				 else if (state_tab[*y_][*x_] == 2) {
					 cout << "To pole jest zajete!!, Podaj pozycje jeszcze raz" << endl;

				 }
			 }
			 else if (*choice_ == 2) {  //O case
				 if (state_tab[*y_][*x_] == 2) {
					 cout << "Nie mozesz ustawic kolka na kolku!!, Podaj pozycje jeszcze raz" << endl;
				 }
				 else if (state_tab[*y_][*x_] == 1) {
					 cout << "To pole jest zajete!!, Podaj pozycje jeszcze raz" << endl;
				 }
			 }
		 }

		 void convert_state_into_tab(int state_tab[8][8], string tab[9][9]) {  //convert state tab positions to tab positions
			 for (int i = 0; i < 8; i++) {
				 for (int j = 0; j < 8; j++) {
					 if (state_tab[i][j] == 1) { //X case
						 if (j == 7) {
							 tab[i + 1][j + 1] = "|_X_|";
						 }
						 else {
							 tab[i + 1][j + 1] = "|_X_";
						 }
					 }
					 else if (state_tab[i][j] == 2) {  //O case
						 if (j == 7) {
							 tab[i + 1][j + 1] = "|_O_|";
						 }
						 else {
							 tab[i + 1][j + 1] = "|_O_";
						 }
					 }
				 }
			 }
		 }

		 void move(int state_tab[8][8], string tab[9][9]) {  //set new position for the X or O
			 string position; //position which player will type
			 *p_ = false; 
			 char temp; //number character 
			 while (*p_ == false) {
				 //position choice
				 if (*choice_ == 1) { //X case  
					 cout << "Podaj na jakiej pozycji chcesz ustawic krzyzyk:(notacja szachowa): ";
					 cin >> position;
				 }
				 else if (*choice_ == 2) { //O case
					 cout << "Podaj na jakiej pozycji chcesz ustawic kolko: (notacja szachowa): ";
					 cin >> position;
				 }
				 temp = position[1]; //second character in position
				 *x_ = int(position[0]) - 64 - 1; //set x position by char to int cast
				 *y_ = temp - '0' - 1; //set y position
				 if ((*x_ < 0 || *x_ > 7) || (*y_ < 0 || *y_>7)) { //instruction in case of bad position set by the player
					 cout << "Podales pozycje poza notacja!! Sproboj ponownie. " << endl;
					 continue;
				 }
				 *p_ = collide(state_tab); //call collide function
				 if (*p_ == false) { //in case of collide, print specific instructions
					 print_instuctrions(state_tab); 
					 continue;
				 }
				 //set new position for X or O
				 else {
					 if (*choice_ == 1) { //X case 
						 state_tab[*y_][*x_] = 1;
					 }
					 else if (*choice_ == 2) { //O case
						 state_tab[*y_][*x_] = 2;
					 }
				 }
			 }
			 convert_state_into_tab(state_tab, tab); //call convert function
		 }

		 bool check_winner(int state_tab[8][8]) { //checks if someone is winning
			 *p_ = false;
			 for (int i = 0; i < 8; i++) {
				 for (int j = 0; j < 8; j++) {
					 if ((state_tab[i][j] == state_tab[i + 1][j]) && state_tab[i][j] != 0) { //checks vertical win
						 if (state_tab[i][j] == state_tab[i + 2][j]) {
							 if (state_tab[i][j] == state_tab[i + 3][j]) {
								 *p_ = true;
								 return *p_;
							 }
							 else {
								 *p_ = false;
							 }
						 }
						 else {
							 *p_ = false;
						 }
					 }
					 if ((state_tab[i][j] == state_tab[i][j + 1]) && state_tab[i][j] != 0) { //checks horizantal win
						 if (state_tab[i][j] == state_tab[i][j + 2]) {
							 if (state_tab[i][j] == state_tab[i][j + 3]) {
								 *p_ = true;
								 return *p_;
							 }
							 else {
								 *p_ = false;
							 }
						 }
						 else {
							 *p_ = false;
						 }
					 }
					 if (state_tab[i][j] == state_tab[i + 1][j + 1] && i<5 && state_tab[i][j] != 0) { //checks right slant win
						 if (state_tab[i][j] == state_tab[i + 2][j + 2]) {
							 if (state_tab[i][j] == state_tab[i + 3][j + 3]) {
								 *p_ = true;
								 return *p_;
							 }
							 else {
								 *p_ = false;
							 }
						 }
						 else {
							 *p_ = false;
						 }
					 }
					 }
				 }
			 for (int i = 0; i < 8; i++) {
				 for (int j = 7; j > -1; j--) {
					 if (state_tab[i][j] == state_tab[i + 1][j - 1] && state_tab[i][j] != 0) { //checks left slant win
						 if (state_tab[i][j] == state_tab[i + 2][j - 2]) {
							 if (state_tab[i][j] == state_tab[i + 3][j - 3]) {
								 *p_ = true;
								 return *p_;
							 }
							 else {
								 *p_ = false;
							 }
						 }
						 else {
							 *p_ = false;
						 }

					 }
				 }
			 }
			 if (*p_ == false) { //if function didn`t return a value
			    return *p_;
			 }
		 }
 		 
		 ~Player() {
			 delete x_, y_, choice_, p_; //deletes dynamic values
		 }
};


int main() {
	string tab[9][9]; //declares a map which shows the game
	int state_tab[8][8]; //declares a array of states(0 - clear, 1 - X, 2 - O)
	int choice1, choice2; //declares a value which represent choice of the playing character(1 - X, 2 - O)
	string name1, name2; //declares names of players
	bool is_win = false;  //declares bool variable which inform if the game is over
	create_tab(tab, state_tab);  //creates tab and state tab
	print_tab(tab);  //showing tab
	//Initial welcome to the game in polish
	cout << "Witajcie w swiatecznej grze kolko i krzyzyk!!" << endl;
	cout << "Graczu nr 1, podaj swoj nick: ";
	cin >> name1;
	cout << "Graczu nr 2, teraz twoja kolej: ";
	cin >> name2;
	while (true) {
		cout << name1 << " Podaj czym chcesz grac: (1-krzyzyk, 2-kolko): "; //making a choice
		cin >> choice1; 
		if (choice1 != 1 && choice1 != 2) { //in case of bad choice number
			cout << "Wybrales za duzy numer! Sproboj ponownie!" << endl;
			continue;
		}
		else if (choice1 == 1) { //X case
			cout << "Wybrales krzyzyk, zatem " << name2 << " zagra kolkiem. " << endl;
			choice2 = 2;
		}
		else if (choice1 == 2) { //O case
			cout << "Wybrales kolko, zatem " << name2 << " zagra krzyzykiem. " << endl;
			choice2 = 1;
		}
		break;
	}
	Player first(choice1); //declares first player
	Player second(choice2); //declares second player
	while (is_win == false) {
		first.move(state_tab, tab); //set new position to first player
		print_tab(tab); //showing map
		is_win = first.check_winner(state_tab); //check if the game is over
		if (is_win == true) { //if yes, end the game
			cout << "Brawo " << name1 << " wygrales/as!!!" << endl;
			continue;
		}
		//same for the O
		second.move(state_tab, tab);
		print_tab(tab);
		is_win = second.check_winner(state_tab);
		if (is_win == true) {
			cout << "Brawo " << name2 << " wygrales/as!!!" << endl;
			continue;
		}
	}
	return 0;
}
//Blazej Pajor, thanks for reading my code :D