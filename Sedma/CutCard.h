#pragma once
#include "Card.h"
class CutCard :
	public Card
{
public:
	CutCard(string , string);
	void play_card(Card , int , int& , int&);
	~CutCard();
};

