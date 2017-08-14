//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h"

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
    void getValues(int& value1, int& value2, int& valueAnswer);
    char mpc_GameName[smallbuffer];
};

//---------------------------------------------------------------------------
#endif
