#ifndef _CARD_H_INCLUDED
#define _CARD_H_INCLUDED

class Card
{

public:
	enum Suit{
		Club = 0,
		Diamond = 1,
		Spade = 2,
		Heart = 3,
	};

	Card(int, Suit);
	virtual ~Card(){};
	int m_value;
	Suit m_suit;

	virtual void PrintCard();
	virtual int GetValue();
	virtual void DecValue();
	virtual bool IsLow();
};

#endif
