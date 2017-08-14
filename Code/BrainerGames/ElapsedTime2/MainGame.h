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
    static const unsigned int mui_DUMMYYEAR = 1991;

		TMainGame();    
    unsigned int GetNumberOfGames(){return 1;}
		void GetGameName(unsigned int /*_ui_GameIndex*/, char* _pc_GameName);
		void GetGameType(unsigned int /*_ui_GameIndex*/, int* _piGameType);
		int GetQA(unsigned int /*_ui_GameIndex*/, char* _pcQA);
		void SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff);
		void GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs);    
    void Reset(unsigned int _ui_GameIndex);

  private:
    char mpc_GameName[smallbuffer];

    void getDates(DateHelper::sDateYear& _leaveDate, DateHelper::sDateYear& _returnDate, unsigned int& _ui_noDays);
    void getDatesDelay(DateHelper::sDateYear& _currentDate, unsigned int& _ui_Delay, DateHelper::sDateYear& _leaveDate, DateHelper::sDateYear& _returnDate, unsigned int& _ui_noDays);
};

//---------------------------------------------------------------------------
#endif
