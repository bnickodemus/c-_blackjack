#ifndef Hand_H
#define Hand_H

#include "Card.h"
#include "Ace.h"
#include <vector>

class Hand
{
public:
	Hand(int);
    ~Hand();
    std::vector<Card*> m_hand;

    int SumHand();
    bool PrintHand();
    void DumpHand();
    int m_handID;
	bool DecAce();
	bool CanSplit();
};

#endif
