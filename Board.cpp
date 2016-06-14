#include <iostream>
#include <map>
#include <string>
#include "Board.h"
#include "Player.h"

/***********************************************************************************
 * Purpose: Constructor for Board, sets up a Board for a game
 * In: Takes a number of players, number of Decks, and a game name
 * Out: Assigns each variable passed to its member, creates a game deck, and creates
 *		the players in the game
***********************************************************************************/
Board::Board(int nPlayers, int nDecks, std::string gameName)
{
	if(nPlayers < 2 || nDecks < 1)
	{
		std::cout << "Invalid number of players or decks passed.\n";
		return;
	}

	m_nPlayers = nPlayers;
	m_nDecks = nDecks;
	m_gameName = gameName;
	m_play = true;

	m_gameDeck = MakeGameDeck();

	Player* player;

	for(int i = 0; i <= nPlayers; i++)
	{
		player = new Player(i);
		m_players.insert(std::pair<int, Player*>(i, player));
	}
}

/***********************************************************************************
 * Purpose: Destructor for Board
 * Out: Deletes the players and the games deck
***********************************************************************************/
Board::~Board()
{
	for(int i = 0; i < m_players.size(); i++)
	{
		delete m_players[i];
	}

	delete m_gameDeck;
}

/***********************************************************************************
 * Purpose: Deals the starting hands (used at the start of a game)
 * Out: Adds a starting hand for each of the players (see MakeStartingHand())
***********************************************************************************/
void Board::DealStartingHands()
{
	for(int i = 0; i < m_players.size(); i++)
	{
		m_players[i]->AddStartingHand(MakeStartingHand());
	}
}

/***********************************************************************************
 * Purpose: Creates a starting hand with two dealt cards from the deck
 * Out: Will remove two cards off the deck and return a pointer to the hand
***********************************************************************************/
Hand* Board::MakeStartingHand()
{
	Hand* h = new Hand(0);
	for(int i = 0; i < 2; i++)
	{
		h->m_hand.push_back(m_gameDeck->DealCard());
	}

	return h;
}

/***********************************************************************************
 * Purpose: Creates a new deck for a game
 * Out: Creates a new deck with n size then shuffles and returns the deck 
***********************************************************************************/
Deck* Board::MakeGameDeck()
{
	Deck* d = new Deck(m_nDecks);
	d->Shuffle();
	return d;
}

/***********************************************************************************
 * Purpose: Deals a card to a player from the deck
 * In: A player that is recieving the card and the hand a card will be put in
 * Out: A player's hand will recieve a card from a deck of cards
***********************************************************************************/
void Board::DealCard(int player, int hand)
{
	m_players[player]->m_handList[hand]->m_hand.push_back(m_gameDeck->DealCard());
}

/***********************************************************************************
* Purpose: Will split a players hand
* In: A player and the index of the handList will be passed
* Out: A players hand at a particular index will be split into different hands in 
*		the handList
***********************************************************************************/
//void Board::SplitHand(int player, int index)
void Board::SplitHand(Player* player, int index)
{
	player->Split(index);

	player->m_handList[index]->m_hand.push_back(m_gameDeck->DealCard());
	player->m_handList.back()->m_hand.push_back(m_gameDeck->DealCard());
}

/***********************************************************************************
 * Purpose: Print all players on the board
 * Out: Prints each players hand
***********************************************************************************/
void Board::PrintAllPlayers()
{
	for(int i = 1; i < m_players.size(); i++)
	{
		m_players[i]->PrintHands();
	}

	std::cout << std::endl;
}

//void Board::PrintPlayerHand(int player, int iHand)
//{
//	m_players[player]->PrintHand(iHand);
//}

/***********************************************************************************
 * Purpose: Prints the current plays
 * In: The current player 
 * Out: Will print the current players hand
***********************************************************************************/
void Board::PrintCurPlayer(int player)
{
	m_players[player]->PrintHands();
}

/***********************************************************************************
 * Purpose: Prints the dealers hand
 * In: Hide is a boolean used to hide the dealers initial hand
 * Out: The function will print out a dealers first card while it is called when hide 
 *		is true. When hide is false, the dealers current hand will be printed
***********************************************************************************/
void Board::PrintDealer(bool hide)
{
	int sum = 0;
	std::cout << "\n### TABLE ###\n";

	if(hide)
	{
		std::cout << "Dealer : ";  
		m_players[0]->m_handList[0]->m_hand[0]->PrintCard();
		std::cout << " *\n";
	}else{

		std::cout << "Dealer : ";  
		m_players[0]->m_handList[0]->PrintHand();
		sum = m_players[0]->m_handList[0]->SumHand();

	}
}

/***********************************************************************************
 * Purpose: Determines if a player has split their hand
 * In: A player and the players hand
 * Out: Will return true or false if a player has split their hand
***********************************************************************************/
//bool Board::PlayerHasSplit(int iPlayer, int iHand)
bool Board::PlayerHasSplit(Player* player, int iHand)
{
	return player->CanSplit(iHand);
}

/***********************************************************************************
 * Purpose: Dumps all players hands for a board
 * Out: Sets all players hands to a size of 0
***********************************************************************************/
void Board::ClearBoard()
{
	for(int i = 0; i < m_players.size(); i++)
	{
		m_players[i]->DumpHands();
	}
}

/***********************************************************************************
 * Purpose: At the start of a game will clear a board, also creates a loop that	
 *		determines if a game is in play (boolean m_play)
 * Out: Clears a board and starts the game loop
***********************************************************************************/
void Board::StartGame()
{
	int option, ch;

	while(m_play)
	{
		CheckDeck();
		std::cout << "\n#### " << m_gameName << " Menu ###\n";
		std::cout << "\nPlease select an option below...\n";
		std::cout << "1) Start A Round\n";
		std::cout << "2) Pause game\n";
		std::cout << "3) End Game\n";
		std::cin >> option;

		while ((ch = std::cin.get()) != '\n' && ch != EOF);

		switch(option)
		{
			case 1:
				StartRound();
				break;
			case 2:
				PauseGame();
				break;
			case 3:
				EndGame();
				break;
			default:
				std::cout << "This is default.....\n\n\n\n\n";
				break;
		}
	}
}

void Board::CheckSplit(Player* player)
{
	bool split = true;
	std::string option;

	while(split)
	{
		for(int i = 0; i < player->m_handList.size(); i++)
		{
			if(player->CanSplit(i))
			{
				player->PrintHand(i);
				std::cout << "Would you like to split this hand (y/n): ";
				std::getline(std::cin, option);

				std::cout << std::endl;

				if(tolower(option[0]) == 'y')
				{
					SplitHand(player, i);//Split hand and deal two cards
					split = false;//We want to exit while loop and j for loop
					i--;//Restart split check at current hand
				}else if(tolower(option[0]) == 'n'){
					split = false;
				}else{
					std::cout << "Not a valid option, try again.\n";
					i--;
				}
			}

			split = false;
		}
	}
}

void Board::StartRound()
{
	ClearBoard();
	DealStartingHands();
	PrintDealer(true);
	PrintAllPlayers();

	for(int i = 1; i < m_players.size(); i++)
	{
		CheckSplit(m_players[i]);
		PlayHands(m_players[i]);
	}

	PlayDealer();
	PrintDealer(false);
	PrintAllPlayers();
	PrintWinners();

	std::cout << "\n\n";
}

void Board::PlayDealer()
{

	bool dBust = true;
	int dSum = 0;
	int pSum = 0;
	int maxHand = 0;

	for(int i = 0; i < m_players.size(); i++)
	{
		for(int j = 0; j < m_players[i]->m_handList.size(); j++)
		{
			pSum = m_players[i]->m_handList[j]->SumHand();

			if(maxHand < pSum && pSum < 22)
			{
				maxHand = pSum;
				dBust = false;
			}
		}
	}

	while(!dBust)
	{
		dSum = m_players[0]->m_handList[0]->SumHand();

		if(dSum < 17 || dSum < pSum)
		{
			DealCard(0, 0);
		}else{
			dBust = true;
		}
	}
}

void Board::PrintWinners()
{
	int playerSum = 0;
	bool dWin = true;
	bool bPush = false;
	int dSum = m_players[0]->m_handList[0]->SumHand();

	//Display winners
	std::cout << "Round Winner(s):";

	//Determine if there is a push
	for(int i = 1; i < m_players.size(); i++)
	{
		for(int j = 0; j < m_players[i]->m_handList.size(); j++)
		{
			playerSum = m_players[i]->m_handList[j]->SumHand();

			if(dSum == playerSum)
				bPush = true;
			else if(playerSum > dSum)
				bPush = false;
		}
	}

	//If no push, else push
	if(!bPush || dSum > 21)
	{
		for(int i = 1; i < m_players.size(); i++)
		{
			for(int j = 0; j < m_players[i]->m_handList.size(); j++)
			{
				playerSum = m_players[i]->m_handList[j]->SumHand();
				if(dSum > 21)
				{
					if(playerSum < 22)
					{
						std::cout << " Player" << m_players[i]->m_playerID;
						dWin = false;
						break;
					}
				}else if(dSum < playerSum && playerSum < 22){
						
					std::cout << " Player" << m_players[i]->m_playerID;
					dWin = false;
					continue;
				}
			}
		}

		if(dWin && dSum < 22)
			std::cout << " Dealer";
	}else{

		std::cout << " Dealer";

		for(int i = 1; i < m_players.size(); i++)
		{
			for(int j = 0; j < m_players[i]->m_handList.size(); j++)
			{
				playerSum = m_players[i]->m_handList[j]->SumHand();
				
				if(dSum == playerSum)
					std::cout << " Player" << m_players[i]->m_playerID;
			}
		}
	}
}

void Board::PauseGame()
{
	std::cout << "The game is pausing.....\n\n\n\n";
}

/***********************************************************************************
* Purpose: Ends a game
* Out: Sets m_play to false, terminating the game loop
***********************************************************************************/
void Board::EndGame()
{
	std::cout << "Ending game......\n\n\n\n";
	m_play = false;
}

/***********************************************************************************
 * Purpose: Checks for valid user input
 * Out: Will return true if the user has enter h,H,s,or S and false otherwise
***********************************************************************************/
bool isValid(char option)
{
	if(tolower(option) == 'h' || tolower(option) == 's')
		return true;
	else
		return false;
}

/***********************************************************************************
 * Purpose: Gathers valid user input and sets option acordingly. Cards will be dealt
 *		with "h" and "s" will output the players score
 * In: Player pointer to current player
 * Out: Will write out the players options and gather the input and will either 
 *		deal a card and write it out again or will print their hand
***********************************************************************************/
void Board::PlayHands(Player* player)
{
	std::string option;
	bool validOption;

	for(int i = 0; i < player->m_handList.size(); i++)
	{
		std::cout << std::endl;
		validOption = false;

		while(!validOption)
		{
			if(player->PrintHand(i))
				break;

			std::cout << "Player " << player->m_playerID << " would you like to (h)it, (s)tand for Hand " << i + 1 << "?>";
			std::getline(std::cin, option);

			if(!isValid(option[0]))
			{
				std::cout << "Invalid choice, pleese choose again.\n";
			}
			else{
				if(option[0] == 's' || option[0] == 'S')
				{
					validOption = true;
				}else{
					DealCard(player->m_playerID, i);
				}
			}
		}
	}
}

void Board::CheckDeck()
{
	if(m_gameDeck->m_deck.size() < (m_nDecks/2)*52)
	{
		std::cout << "Creating new deck....\n";
		delete m_gameDeck;
		m_gameDeck = 0;
		m_gameDeck = MakeGameDeck();
	}
}
