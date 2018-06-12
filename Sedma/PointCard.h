#pragma once
#include "Card.h"
class PointCard :
	public Card
{
public:
	PointCard(string , string);
	void playCard(Card , int , int& , int&);
	~PointCard();
};

