#include <iostream>
#include "Hand.h"
#include "Player.h"
#include "Card.h"


/***********************************************************************************
 * Purpose: Player constructor, uses Hand.cpp, used in Board.cpp. No default constructor
 * In: The id that will referance the player
 * Out: Assigns id passed to the member playerID
***********************************************************************************/
Player::Player(int id)
{
	m_playerID = id;
}

/***********************************************************************************
 * Purpose: This function will split a players hand into two hands located in Player.h
 * In: The index of which hand in m_handList that needs to split
 * Out: m_handList[index] will have one card and the last element of m_handList will
 *		have one card.
***********************************************************************************/
void Player::Split(int index)
{
	Hand* h = new Hand(m_handList.size());
	h->m_hand.push_back(m_handList[index]->m_hand.back());

	//If splitting a double Ace then Inc first Ace back up to value of 11
	if(dynamic_cast<Ace*>(m_handList[index]->m_hand[0]))
	{
		dynamic_cast<Ace*>(m_handList[index]->m_hand[0])->IncValue();;
	}
	
	m_handList.push_back(h);
	m_handList[index]->m_hand.pop_back();
}	

/***********************************************************************************
 * Purpose: This function will add the starting hands to the handList of player
 * In: The Hand* that will be added to the handList of player
 * Out: The handList of the player will now contains a pointer to a hand 
 ***********************************************************************************/
void Player::AddStartingHand(Hand* hand)
{
	m_handList.push_back(hand);
}

/***********************************************************************************
 * Purpose: This function will print all of the hands in the handList.
 * Out: The Players and Hands are printed and the sum of the cards is printed if the 
 *		sum is less than 21 and prints Bust if their sum is greater than 21
 ***********************************************************************************/
bool Player::PrintHand(int iHand)
{
	std::cout << "Player " << m_playerID << ": ";
	return m_handList[iHand]->PrintHand();
}

void Player::PrintHands()
{
	for(int i = 0; i < m_handList.size(); i++)
	{
		std::cout << "Player " << m_playerID << ": ";
		m_handList[i]->PrintHand();
	}
}

/***********************************************************************************
 * Purpose: This function will determines if a hand can be split
 * In: The index of the handList
 * Out: Will return true or false if the handList can be split
 ***********************************************************************************/
bool Player::CanSplit(int iHand)
{
	return m_handList[iHand]->CanSplit();
}

/***********************************************************************************
 * Purpose: Will dump a Players hands
 * Out: Clears all of a Players handList and sets the handList size to 0
 ***********************************************************************************/
void Player::DumpHands()
{
	m_handList.clear();
}
