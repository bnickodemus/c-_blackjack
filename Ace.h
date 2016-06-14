#ifndef _ACE_H_INCLUDED
#define _ACE_H_INCLUDED

#include "Card.h"

class Ace : public Card
{

public:
	Ace(int, Suit);

	bool m_bLowVal;

	void PrintCard();
	int GetValue();
	void DecValue();
	void IncValue();
	bool IsLow();
};
#endif
