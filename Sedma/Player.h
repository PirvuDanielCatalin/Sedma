#pragma once
#include "Deck.h"
#include <stdlib.h>
#include <time.h>
class Player
{
	vector<Card*> hand;
	int score;
public:
	Player();
	int getScore();
	vector<Card*> getHand();

	void AddScore(int);
	void create(Deck&);
	void erase(int);

	void complete(Deck&,int);
	int valide(string , string);
	bool CanContinue(string);

	friend ostream& operator<<(ostream& , const Player&);

	int remain();
	
	~Player();
};

