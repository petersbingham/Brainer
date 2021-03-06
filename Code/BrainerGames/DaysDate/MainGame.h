//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h" 
#include "DateHelper.h" 

#define smallbuffer 28
#define STRSIZE 128

//#define TEST

class TMainGame : public TGenGame
{
  public:
    TMainGame();
    unsigned int GetNumberOfGames(){return 1;}
    void GetGameName(unsigned int _ui_GameIndex, char* _pc_GameName);
    void GetGameType(unsigned int _ui_GameIndex, int* _piGameType);
    int GetQA(unsigned int _ui_GameIndex, char* _pcQA);
    void SetDiff(unsigned int _ui_GameIndex, int _pi_Secs);
    void GetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs);    
    void Reset(unsigned int _ui_GameIndex);

  private:
    void getDates(DateHelper::sDateYear& _currentDate, DateHelper::sDateYear& _futureDate, unsigned int& _ui_noDays);
    char mpc_GameName[smallbuffer];
};

//---------------------------------------------------------------------------
#endif
