#ifndef _DECK_H_INCLUDED
#define _DECK_H_INCLUDED

#include "Card.h"
#include "Ace.h"
#include <vector>

class Deck
{
public:
	std::vector<Card*> m_deck;
	void InitializeSet();
	void Shuffle();
	Card* DealCard();
	Deck(int);
	~Deck();
	int m_nSets;

};


#endif
