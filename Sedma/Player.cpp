#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	score = 0;
}
int Player::getScore()
{
	return this->score;
}
vector<Card*> Player::getHand()
{
	return this->hand;
}

void Player::AddScore(int val)
{
	score += val;
}
void Player::create(Deck& ob)
{
	srand(time(NULL));
	int nr = ob.size;
	for (int i = 0; i<4; i++)
	{
		int r = rand() % nr;
		while (ob.used[r] == 1)
			r = rand() % nr;

		if (ob[r]->value == "7")
			hand.push_back( new CutCard(ob[r]->value, ob[r]->suit));
		else if (ob[r]->value == "A" || ob[r]->value == "10")
			hand.push_back(new PointCard(ob[r]->value, ob[r]->suit));
		else
			hand.push_back(new Card(ob[r]->value, ob[r]->suit));
		ob.used[r] = 1;

	}

}
void Player::erase(int i)
{
	hand[i] = NULL;
}

void Player::complete(Deck& ob,int nr)
{
	srand(time(NULL));
	int size = ob.size;
	//int used = ob.getUsed();
	int j = 0;
	for (int i = 0; i<4 && j<nr; i++,j++)
		if (hand[i] == NULL)
		{
			int r = rand() % size ;
			while (ob.used[r] == 1)
				r = rand() % size;

			if (ob[r]->value == "7")
				hand[i] = new CutCard(ob[r]->value, ob[r]->suit);
			else if (ob[r]->value == "A" || ob[r]->value == "10")
				hand[i] = new PointCard(ob[r]->value, ob[r]->suit);
			else
				hand[i] = new Card(ob[r]->value, ob[r]->suit);
			ob.used[r] = 1;

		}
}
int Player::valide(string a, string b)
{
	for (int i = 0; i<4; i++)
		if (hand[i]->value == a && hand[i]->suit == b)
			return i;
	return -1;

}
bool Player::CanContinue(string downValue)
{
	for (int i = 0; i<4; i++)
		if (hand[i] != NULL && (hand[i]->value == "7" || hand[i]->value == downValue))
			return true;
	return false;
}

ostream& operator<<(ostream& os, const Player& player)
{
	for (int i = 0; i<4; i++)
		if (player.hand[i] != NULL)
			os << *player.hand[i];
	cout << endl;
	return os;
}

int Player::remain()
{
	int s = 0;
	for (int i = 0; i<4; i++)
		if (hand[i] != NULL)
			s++;
	return s;
}

Player::~Player()
{
}
