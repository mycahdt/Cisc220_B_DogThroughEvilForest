/*
 * Board.cpp
 *
 *  Created on: Sep 14, 2021
 *      Partners: Mycah Detorres and Karl Antonio
 */

#include "Board.hpp"
#include <iostream>
using namespace std;

Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {

	bool keepPlaying = true;
	while (keepPlaying) {

		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size;
		starty = 0;
		endx = rand() % size;
		endy = size-1;

		mydog.x = startx;
		mydog.y = starty;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();


		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}
void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}

}

void Board::addFood() {

	int food = 0;
	if(level == 'e'){
		food = size;
	} else if (level == 'm'){
		food = size - 2;
	} else if (level == 'h'){
		food = size - 4;
	}

	for(int i = 0; i<food; i++){
		int x = -1;
		int y = -1;
		while(x == -1 || y==-1 || board[x][y] != '+') {
			x = rand()%size;
			y = rand()%size;
		}
		board[x][y] = 'F';
	}



}







void Board::addTraps() {

	int trap = 0;
	if(level == 'e'){
		trap = size-6;
	} else if (level == 'm'){
		trap = size - 8;
	} else if (level == 'h'){
		trap = size - 10;
	}

	for(int i = 0; i<trap; i++){
		int x = -1;
		int y = -1;
		while(x == -1 || y==-1 || board[x][y] != '+') {
			x = rand()%size;
			y = rand()%size;
		}
		board[x][y] = 'T';
	}

}






void Board::boardConfig() {

	for(int i = 0; i<size; i++){
		for(int j = 0; j<size; j++){
			board[i][j] = '+';
		}
	}




	//6 easy, 12 medium, 18 hard
	for(int a = 0; a<size; a++){
		int maxWalls = 0;
		if(level == 'e'){
			maxWalls = 6;
		} else if (level == 'm'){
			maxWalls = 12;
		} else if (level == 'h'){
			maxWalls = 16;
		}

		if(a%2 == 1) {
			for(int b = 0; b<maxWalls; b++){

				int myColumn = rand()%21;
				while(board[a][myColumn] != '+' && myColumn%2 != 1){
					myColumn = rand()%21;
				}

				int wallType = rand()%2;
				if(wallType == 0){
					board[a][myColumn] = '|';
				} else {
					board[a][myColumn] = '_';
				}
			}
		}
	}

	board[startx][starty] = 'D';
	board[endx][endy] = 'E';



}






void Board::printBoard() {


	/*prints top of box*/
	cout << "          ";
	for(int w = 0; w<21; w++){
		cout << " _";
	}
	cout << endl;


	for(int i = 0; i<size; i++){

		if(i == startx){
			cout << "          ->";      //prints start arrow
		} else {
			cout << "           |";   //prints left of box
		}

		for(int j = 0; j<size; j++){
			//cout << board[i][j];
			if(board[i][j] == '+' || (board[i][j] == 'T' && (!debug))){
				cout << ' ';
				cout << ' ';
			} else {
				cout << board[i][j];
				cout << ' ';
			}
			//cout << ' ';
		}

		if(i == endx){
			cout << "->" << endl;   //prints end arrow
		} else {
			cout << "|" << endl;      // prints right of box
		}

	}




	/*prints bottom of box*/
	cout << "          ";
	for(int w = 0; w<21; w++){
		cout << " _";
	}
	cout << endl;

}







bool Board::moveDog(char c) {

	bool strengthStatus = true;
	char nextPos = ' ';

	board[mydog.x][mydog.y] = '+';

	if(c == 'u'){



		if(board[mydog.x-1][mydog.y] == '|' || board[mydog.x-1][mydog.y] == '_'){
			if(mydog.strength > 6){
				cout << "Do you want to knock down that wall? (costs 6) " << endl;
				string s = "no";
				cin>>s;
				if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
					/*
					 then the wall is knocked down,
					 the dog moves into that square,
					  the dog's strength decreases by 6.
					 */

					if((mydog.x-1) != -1){
						mydog.x-=1;
					}

					strengthStatus = mydog.changeStrength(-6);

				} else {
					strengthStatus = mydog.changeStrength(-1);
				}
			}

		} else {
			if((mydog.x-1) != -1){
				mydog.x-=1;
			}
		}






	}

	if(c == 'd'){



		if(board[mydog.x+1][mydog.y] == '|' || board[mydog.x+1][mydog.y] == '_'){
			if(mydog.strength > 6){
				cout << "Do you want to knock down that wall? (costs 6) " << endl;
				string s = "no";
				cin>>s;
				if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
					/*
					 then the wall is knocked down,
					 the dog moves into that square,
					  the dog's strength decreases by 6.
					 */

					if((mydog.x+1) != 20){
						mydog.x+=1;
					}

					strengthStatus = mydog.changeStrength(-6);

				} else {
					strengthStatus = mydog.changeStrength(-1);
				}
			}

		} else {
			if((mydog.x+1) != 20){
				mydog.x+=1;
			}
		}




	}

	if(c == 'l'){



		if(board[mydog.x][mydog.y-1] == '|' || board[mydog.x][mydog.y-1] == '_'){
			if(mydog.strength > 6){
				cout << "Do you want to knock down that wall? (costs 6) " << endl;
				string s = "no";
				cin>>s;
				if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {

					if((mydog.y-1) != -1){
						mydog.y-=1;
					}

					strengthStatus = mydog.changeStrength(-6);

				} else {
					strengthStatus = mydog.changeStrength(-1);
				}
			}

		} else {
			if((mydog.y-1) != -1){
				mydog.y-=1;
			}
		}




	}


	if(c == 'r'){



		if(board[mydog.x][mydog.y+1] == '|' || board[mydog.x][mydog.y+1] == '_'){
			if(mydog.strength > 6){
				cout << "Do you want to knock down that wall? (costs 6) " << endl;
				string s = "no";
				cin>>s;
				if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {


					if((mydog.y+1) != 20){
						mydog.y+=1;
					}

					strengthStatus = mydog.changeStrength(-6);

				} else {
					strengthStatus = mydog.changeStrength(-1);
				}
			}

		} else {
			if((mydog.y+1) != 20){
				mydog.y+=1;
			}
		}


	}


	nextPos = board[mydog.x][mydog.y];
	board[mydog.x][mydog.y] = 'D';


	if(nextPos == 'F'){
		int val = rand()%15+2;
		strengthStatus = mydog.changeStrength(val);
	}


	if(nextPos == 'E'){
		mydog.won();
		strengthStatus = false;
	}



	if(nextPos == 'T'){
		int val = (rand()%15+2)*-1;
		strengthStatus = mydog.changeStrength(val);
		cout<< "OH NO, " << mydog.name << " HIT A TRAP! " << mydog.name <<  " lost " << val << " strength. :(" << endl;
	}


	if(nextPos == '+'){
		strengthStatus = mydog.changeStrength(-2);
	}


	return strengthStatus;



}
