#include "stdafx.h"
#include "CutCard.h"


CutCard::CutCard(string value = "0", string suit = "0"):Card(value,suit)
{
}

void CutCard::play_card(Card card, int ord, int& winner, int& sum)
{
	if (card.get_value() != "0")
		winner = ord;
}

CutCard::~CutCard()
{
}
