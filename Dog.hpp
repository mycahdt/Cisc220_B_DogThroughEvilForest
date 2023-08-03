/*
 * Dog.hpp
 *
 *  Created on: Sep 14, 2021
 *      Partners: Mycah Detorres and Karl Antonio
 */

#include <iostream>
#ifndef DOG_HPP_
#define DOG_HPP_
using namespace std;

class Dog {

	friend class Board; //by making the Board a friend of this class, the
						//Dog class is allowing the board class and objects
						//to access all of the dog class' private fields

	string name; // for the dog's name
	int strength;  //for the dog's current strength
	int x;  // the x coordinate of where the dog is currently on the board
	int y;  // the y coordinate of where the dog is currently on the board

public:
	Dog(string n); //constructor
	Dog();  //constructor
	bool changeStrength(int amt);  //changes dog’s strength field
	void die();  //die message when strength at or below 0
	void printDog();  // prints out info about dog
	void won(); //won message for when dog is at end of evil forest
	void reset();  //resets dog for restarting a new game

};


#endif /* DOG_HPP_ */
