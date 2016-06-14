#include <iostream>
#include <vector>
#include <math.h>
#include "Pot.h"

Pot::Pot(int initialPot)
{
    m_curPot = initialPot;
}

Pot::~Pot()
{
    
}

void Pot::PlaceBet(int betAmount)
{
    m_curPot -= betAmount;
    m_curBet += betAmount;
}

void Pot::DoubleDown()
{
    PlaceBet(m_curBet);
}

void Pot::BuyInsurance(int insurAmount)
{
    m_curInsurance += insurAmount;
    m_curPot -= insurAmount;
}

void Pot::AddWinnings(bool blackjack)
{
    if(blackjack)
    {
        m_curPot+= m_curBet * 1.5;
        m_curBet = 0;
    }
}

void Pot::ResetBets()
{
    m_curBet = m_curInsurance = 0;
}

void Pot::PrintPot()
{
    std::cout << "pot:" << m_curPot << std::endl;
}

void Pot::PrintBet()
{
    std::cout << "bet:" << m_curBet << std::endl;
}
