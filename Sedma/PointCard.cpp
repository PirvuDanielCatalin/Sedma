#include "stdafx.h"
#include "PointCard.h"


PointCard::PointCard(string value = "0", string suit = "0"):Card(value,suit)
{
	this->point = 1;
}

void PointCard::play_card(Card card, int ord, int& winner, int& sum)
{
	sum++;
	if (card.get_value() == this->value)
		winner = ord;

}

PointCard::~PointCard()
{
}
