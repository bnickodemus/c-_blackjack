#include <iostream>
#include <stdio.h>
#include <string>
#include "Card.h"

/***********************************************************************************
 * Purpose: Constructor for card, used in Hand.cpp
 * In: A value and a suit for the card is passed
 * Out: Assigns the member value and the member suit to the value and suit passed
 ***********************************************************************************/
Card::Card(int val, Suit s)
{
	if(val > 13)
	{
		std::cout << "Value of card too high - " << val << std::endl;
		return;
	}

	if((int)s > 3)
	{
		std::cout << "Invalid suit trying to be created\n";
	}

	m_value = val;
	m_suit = s;
}

/***********************************************************************************
 * Purpose: Gets the value for a card 
 * Out: Returns the value 10 if if the cards member value is less than 9 
 ***********************************************************************************/
int Card::GetValue()
{
	if(m_value > 9)
		return 10;
	else
		return m_value;
}

/***********************************************************************************
 * Purpose: PrintCard() will print the character suit and the value of the card
 * Out: The value and suit of the card will be printed. X being the default value
 ***********************************************************************************/
void Card::PrintCard()
{
	char s;
	std::string v;

	switch(m_suit)
	{
		case Club:
			s = 'C';
			break;
		case Diamond:
			s = 'D';
			break;
		case Spade:
			s = 'S';
			break;
		case Heart:
			s = 'H';
			break;
		default:
			s = 'X';
			break;
	}

	switch(m_value)
	{
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			v = std::to_string(m_value);
			break;
		case 11:
			v = 'J';
			break;
		case 12:
			v = 'Q';
			break;
		case 13:
			v = 'K';
			break;
		default:
			v = 'X';
			break;
	}

	std::cout << v << s << " ";
}

void Card::DecValue()
{

}

bool Card::IsLow()
{
	return true;
}
