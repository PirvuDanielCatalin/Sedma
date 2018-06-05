#pragma once
#include "Card.h"
class PointCard :
	public Card
{
public:
	PointCard(string , string);
	void play_card(Card , int , int& , int&);
	~PointCard();
};

