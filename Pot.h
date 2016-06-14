#ifndef _POT_H_INCLUDED
#define _POT_H_INCLUDED

class Pot
{
public:
    Pot(int);
    ~Pot();
    
    int m_curBet;
    int m_curPot;
    int m_curInsurance;
    
    void PlaceBet(int);
    void DoubleDown();
    void BuyInsurance(int);
    void AddWinnings(bool);
    void ResetBets();
    
    void PrintPot();
    void PrintBet();
}; 

#endif

