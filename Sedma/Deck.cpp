#include "stdafx.h"
#include "Deck.h"

Deck::Deck(int aux)
{
	if (aux == 2 || aux == 4)
	{
		this->size = 32;
		this->used.resize(32); //0 0 ... 0  => 32 de 0-uri

		vector<string> suits = { "Spades","Diamonds","Clubs","Hearts" };

		int k = 1;
		while (k < 15)
		{
			switch (k)
			{
			case 1:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new PointCard("A", suits[i]));
				break;
			case 7:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new CutCard("7", suits[i]));
				break;
			case 10:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new PointCard("10", suits[i]));
				break;
			case 11:
				break;
			case 12:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card("J", suits[i]));
				break;
			case 13:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card("Q", suits[i]));
				break;
			case 14:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card("K", suits[i]));
				break;
			default:
				if (k > 7)
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card(to_string(k), suits[i]));
				break;
			}
			k++;
		}
	}
	else if(aux == 3)
	{
		this->size = 30;
		this->used.resize(30); //0 0 ... 0  => 30 de 0-uri

		vector<string> suits = { "Spades","Diamonds","Clubs","Hearts" };

		int k = 1;
		while (k < 15)
		{
			switch (k)
			{
			case 1:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new PointCard("A", suits[i]));
				break;
			case 7:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new CutCard("7", suits[i]));
				break;
			case 8:
				this->cards.push_back(new CutCard("8", suits[0]));
				this->cards.push_back(new CutCard("8", suits[3]));
				break;
			case 10:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new PointCard("10", suits[i]));
				break;
			case 11:
				break;
			case 12:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card("J", suits[i]));
				break;
			case 13:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card("Q", suits[i]));
				break;
			case 14:
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card("K", suits[i]));
				break;
			default:
				if(k>8)
				for (int i = 0; i < 4; i++)
					this->cards.push_back(new Card(to_string(k), suits[i]));
				break;
			}

			k++;
		}
	}
}

Card* Deck::operator[](int i)
{
	return this->cards[i];
}
int Deck::getSize()
{
	return this->size;
}
int Deck::getUsed() //Number of used cards in the deck
{
	int val = 0;
	for (int i = 0; i<size; i++)
		if (used[i] != 0)
			val++;
	return val;
}

ostream& operator<<(ostream& os, const Deck& deck)
{
	for (int i = 0 ; i< deck.cards.size() ; i++)
	{
		if (i % 4 == 0 && i!=0)
			cout << endl;
		cout << *deck.cards[i]<<"	";
	}
	cout << endl;
	return os;
}

Deck::Deck(const Deck& A)
{
	this->cards.clear();
	
	this->size = A.size;
	for (int i = 0; i < A.cards.size(); i++)
		this->cards.push_back(A.cards[i]);
		
}
Deck& Deck::operator=(const Deck& A)
{
	if (this == &A)
		return *this;
	this->cards.clear();

	this->size = A.size;
	for (int i = 0; i < A.cards.size(); i++)
		this->cards.push_back(A.cards[i]);

	return *this;
}

Deck::~Deck()
{
}
