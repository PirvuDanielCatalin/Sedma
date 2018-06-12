#pragma once
#include "Card.h"
class CutCard :
	public Card
{
public:
	CutCard(string , string);
	void playCard(Card , int , int& , int&);
	~CutCard();
};

