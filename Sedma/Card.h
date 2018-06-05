#pragma once

#include <iostream>
#include <string>
using namespace std;

class Card
{

	friend class Deck;
	friend class Player;
protected:

	string value;
	string suit;
	int point;
public:
	Card(string ="0", string = "0");

	Card& operator=(Card&);

	friend ostream& operator<<(ostream& , const Card&);

	int get_point();

	string get_value();

	void set(string, string);

	virtual void play_card(Card , int , int& , int&);
};

