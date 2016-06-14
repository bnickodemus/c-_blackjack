#ifndef _PLAYER_H_INCLUDED
#define _PLAYER_H_INCLUDED


#include "Card.h"
#include "Hand.h"
#include "Pot.h"
#include <vector>

class Player
{
public:
	Player(int);
	std::vector<Hand*> m_handList;
	int m_playerID;
	
	//Pot* m_pot = new Pot(500);
	
	void Split(int index);
	void AddStartingHand(Hand* hand);
	bool PrintHand(int);
	void PrintHands();
	void DumpHands();
	bool CanSplit(int);
};

#endif
