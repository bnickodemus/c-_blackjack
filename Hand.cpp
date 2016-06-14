#include <iostream>
#include "Card.h"
#include "Hand.h" 

/***********************************************************************************
 * Purpose: This is the default constructor, used in Player.cpp
 * In: Takes an integer id
 * Out: Assign the value of the id passed to the hands member handID
 ***********************************************************************************/
Hand::Hand(int id)
{
    if(id < 0)
	{
		std::cout << "Hand id is a negative number: " << id << std::endl;
	}
    m_handID = id;
}

/***********************************************************************************
 * Purpose: This is the default destructor 
 * Out: Clears every element in the hand and sets size equal to 0 
***********************************************************************************/
Hand::~Hand(void)
{
	DumpHand();
}

/***********************************************************************************
 * Purpose: Adds up all of the card values in a hand
 * Out: Return the sum of all of the cards in a hand 
 ***********************************************************************************/
int Hand::SumHand() 
{
	int sum = 0;

	for(int i = 0; i < m_hand.size(); i++) 
	{
		sum += m_hand[i]->GetValue();		
	}

	while(sum > 21 && DecAce())
	{
		sum = 0;

		for(int i = 0; i < m_hand.size(); i++) 
		{
			sum += m_hand[i]->GetValue();		
		}
	}

	return sum;
}

/***********************************************************************************
 * Purpose: Prints all cards in a hand
 * Out: Prints all cards in m_hand and their hand ID's 
 ***********************************************************************************/
bool Hand::PrintHand() 
{
	int sum = SumHand();

	std::cout << "Hand " << m_handID + 1 << ": "; 
	for(int i = 0; i < m_hand.size(); i++) 
	{
		m_hand[i]->PrintCard();
	}

	if(sum > 21)
	{
		std::cout << "- Total: " << sum << " - Bust!\n\n";
		return true;
	}else if(sum == 21){
		std::cout << "- Blackjack!\n";
		return true;
	}
	else{
		std::cout << "- Total: " << sum << "\n";
		return false;
	}
}

/***********************************************************************************
 * Purpose: Clears a hand
 * Out: Clears all elements in the hand and sets it's size to zero
 ***********************************************************************************/
void Hand::DumpHand() 
{
	m_hand.clear();
}

/***********************************************************************************
 * Purpose: Determines if a hand can be split
 * Out: Returns true or false
***********************************************************************************/
bool Hand::CanSplit()
{
	Ace* a1 = dynamic_cast<Ace*>(m_hand[0]);
	Ace* a2 = dynamic_cast<Ace*>(m_hand[1]);

	//If one card is an ace and the other is not, return false
	if((a1 != 0 && a2 == 0) || (a2 != 0 && a1 == 0))
		return false;

	//If both are Ace, restore original value of 11 to first Ace and return true
	if(a1 != 0 && a2 != 0)
	{
		a1->m_value = 11;
		return true;
	}

	//If both are not Ace, but have the same value, return true
	if(m_hand[0]->m_value == m_hand[1]->m_value)
	{
		return true;
	}

	//Otherwise return false
	return false;
}

/***********************************************************************************
 * Purpose: Finds the first Ace that has not be decremented and sets it's value to 
 *		one
 * Out: Will return true if an Ace has been decremented
***********************************************************************************/
bool Hand::DecAce()
{
	for(int i = 0; i < m_hand.size(); i++)
	{
		if(dynamic_cast<Ace*>(m_hand[i]))
		{
			if(!m_hand[i]->IsLow())
			{
				m_hand[i]->DecValue();
				return true;
			}
		}
	}

	return false;
}
