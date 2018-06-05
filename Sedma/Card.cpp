#include "stdafx.h"
#include "Card.h"

Card::Card(string _value , string _suit)
{
	this->value = _value;
	this->suit = _suit;
	this->point = 0;
}

Card& Card::operator=(Card& aux)
{
	this->value = aux.value;
	this->suit = aux.suit;
	this->point = aux.point;
	return aux;
}

ostream& operator<<(ostream& os, const Card& card)
{
	os << "| " << card.value <<" of " << card.suit << " | ";
	return os;
}

int Card::get_point()
{
	return this->point;
}

string Card::get_value()
{
	return this->value;
}

void Card::set(string _value, string _suit)
{
	this->value = _value;
	this->suit = _suit;
}

void Card::play_card(Card card, int ord, int& winner, int& sum)
{
	if (card.get_value() == this->value)
		winner = ord;
}