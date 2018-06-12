// Sedma.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"

//vector<string> values = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
//vector<string> suits = { "Spades","Diamonds","Clubs","Hearts" };

int main()
{
	Deck TwoPlayers;
	Player P1, P2;
	P1.Create(TwoPlayers);
	P2.Create(TwoPlayers);

	vector<Player> Players;
	Players.push_back(P1);
	Players.push_back(P2);


	Card downCard;
	int TempWinner = 0; //P1 starts
	int TempScore = 0;
	string value, suit;
	int position;
	int rounds = 0;

	while (TwoPlayers.getUsed() != TwoPlayers.getSize())  // Not all the cards were played
	{
		int StartPlayer = TempWinner;
		if (TempWinner == 0)
		{
			cout << "\n\t\t//------------------------------------------------------------------\\";
			cout << "\n\t\t" << "\t\t\t ~ Player 1 ~";
			cout << "\n\t\t" << Players[0];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P1 chooses a card , it's validated ( It is checked that is a card from his hand ) and we get the position of the card in his hand
			position = Players[0].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[0].Valide(value, suit);
			}

			Players[0].getHand()[position]->playCard(downCard, 0, TempWinner, TempScore);

			downCard = *Players[0].getHand()[position];

			Players[0].Erase(position);

			cout << "\n\n\n";
			cout << "\t\t\t\t\t Down Card : " << downCard << "\n\n";

			cout << "\n\t\t" << "\t\t\t ~ Player 2 ~";
			cout << "\n\t\t" << Players[1];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P2 chooses a card , it's validated ( It is checked that is a card from his hand ) and we get the position of the card in his hand
			position = Players[1].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[1].Valide(value, suit);
			}

			Players[1].getHand()[position]->playCard(downCard, 1, TempWinner, TempScore);

			Players[1].Erase(position);

			cout << "\n\t\t\\------------------------------------------------------------------// \n\n";

		}
		else
		{
			cout << "\n\t\t//------------------------------------------------------------------\\";
			cout << "\n\t\t" << "\t\t\t ~ Player 2 ~";
			cout << "\n\t\t" << Players[1];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P2 chooses a card , it's validated ( It is a card from his hand ) and we get the position of the card in his hand
			position = Players[1].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[1].Valide(value, suit);
			}

			Players[1].getHand()[position]->playCard(downCard, 1, TempWinner, TempScore);

			downCard = *Players[1].getHand()[position];

			Players[1].Erase(position);

			cout << "\n\n\n";
			cout << "\t\t\t\t\t Down Card : " << downCard << endl;

			cout << "\n\t\t" << "\t\t\t ~ Player 1 ~";
			cout << "\n\t\t" << Players[0];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P1 chooses a card , it's validated ( It is a card from his hand ) and we get the position of the card in his hand
			position = Players[0].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[0].Valide(value, suit);
			}

			Players[0].getHand()[position]->playCard(downCard, 0, TempWinner, TempScore);

			Players[0].Erase(position);

			cout << "\n\\------------------------------------------------------------------// \n\n";

		}

		rounds++;

		string answer = "No";
		if (StartPlayer != TempWinner && Players[1 - TempWinner].CanContinue(downCard.getValue()))
		{
			cout << endl << "Player " << 2 - TempWinner << "'s cards: " << Players[1 - TempWinner];
			cout << "\n\n \t\t Player " << 2 - TempWinner << ", do you continue ? < Yes / No > ";
			cin >> answer;
		}

		if (answer == "Yes")
		{
			TempWinner = 1 - TempWinner;
		}
		else
		{
			Players[TempWinner].AddScore(TempScore);

			Players[0].Complete(TwoPlayers, rounds);
			Players[1].Complete(TwoPlayers, rounds);

			TempScore = 0;
			downCard.set("0", "0");
			rounds = 0;
		}

	}

	while (Players[0].Remain() && Players[1].Remain())
	{
		int StartPlayer = TempWinner;
		if (TempWinner == 0)
		{
			cout << "\n\t\t//------------------------------------------------------------------\\";
			cout << "\n\t\t" << "\t\t\t ~ Player 1 ~";
			cout << "\n\t\t" << Players[0];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P1 chooses a card , it's validated ( It is checked that is a card from his hand ) and we get the position of the card in his hand
			position = Players[0].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[0].Valide(value, suit);
			}

			Players[0].getHand()[position]->playCard(downCard, 0, TempWinner, TempScore);

			downCard = *Players[0].getHand()[position];

			Players[0].Erase(position);

			cout << "\n\n\n";
			cout << "\t\t\t\t\t Down Card : " << downCard << "\n\n";

			cout << "\n\t\t" << "\t\t\t ~ Player 2 ~";
			cout << "\n\t\t" << Players[1];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P2 chooses a card , it's validated ( It is checked that is a card from his hand ) and we get the position of the card in his hand
			position = Players[1].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[1].Valide(value, suit);
			}

			Players[1].getHand()[position]->playCard(downCard, 1, TempWinner, TempScore);

			Players[1].Erase(position);

			cout << "\n\t\t\\------------------------------------------------------------------// \n\n";

		}
		else
		{
			cout << "\n\t\t//------------------------------------------------------------------\\";
			cout << "\n\t\t" << "\t\t\t ~ Player 2 ~";
			cout << "\n\t\t" << Players[1];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P2 chooses a card , it's validated ( It is a card from his hand ) and we get the position of the card in his hand
			position = Players[1].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[1].Valide(value, suit);
			}

			Players[1].getHand()[position]->playCard(downCard, 1, TempWinner, TempScore);

			downCard = *Players[1].getHand()[position];

			Players[1].Erase(position);

			cout << "\n\n\n";
			cout << "\t\t\t\t\t Down Card : " << downCard << endl;

			cout << "\n\t\t" << "\t\t\t ~ Player 1 ~";
			cout << "\n\t\t" << Players[0];

			cout << "\n\t\t" << "Card: \n";
			cout << "\t\t Value: "; cin >> value;
			cout << "\t\t  Suit: "; cin >> suit;

			//P1 chooses a card , it's validated ( It is a card from his hand ) and we get the position of the card in his hand
			position = Players[0].Valide(value, suit);
			while (position == -1)
			{
				cout << "\n\t\t" << "Card: \n";
				cout << "\t\t Value: "; cin >> value;
				cout << "\t\t  Suit: "; cin >> suit;
				position = Players[0].Valide(value, suit);
			}

			Players[0].getHand()[position]->playCard(downCard, 0, TempWinner, TempScore);

			Players[0].Erase(position);

			cout << "\n\t\t\\------------------------------------------------------------------// \n\n";

		}

		rounds++;

		string answer = "No";
		if (StartPlayer != TempWinner && Players[1 - TempWinner].CanContinue(downCard.getValue()))
		{
			cout << "Player " << 2 - TempWinner << "'s cards: " << Players[1 - TempWinner];
			cout << "\n\n Player " << 2 - TempWinner << ", do you continue ? < Yes / No > ";
			cin >> answer;
		}

		if (answer == "Yes")
		{
			TempWinner = 1 - TempWinner;
		}
		else
		{
			Players[TempWinner].AddScore(TempScore);
			TempScore = 0;
			downCard.set("0", "0");
			rounds = 0;
		}
	}

	if (Players[0].getScore() >= Players[1].getScore())
		cout << "\t\t!!! The winner is Player 1 with " << Players[0].getScore() << " points agains " << Players[1].getScore() << " points of Player 2 !!!\n";
	else
		cout << "\t\t!!! The winner is Player 2 with " << Players[1].getScore() << " points agains " << Players[0].getScore() << " points of Player 1 !!!\n";

	getchar();
	cout << "Press any key to continue ...";
	getchar();
	return 0;
}

