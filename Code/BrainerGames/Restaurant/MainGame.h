//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h"

class TMainGame : public TGenGame
{
	public:
		TMainGame();    
    unsigned int GetNumberOfGames(){return 1;}
		void GetGameName(unsigned int /*_ui_GameIndex*/, char* _pc_GameName);
		void GetGameType(unsigned int /*_ui_GameIndex*/, int* _piGameType);
		int GetQA(unsigned int /*_ui_GameIndex*/, char* _pcQA);
		void SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff);
		void GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs);    
    void Reset(unsigned int _ui_GameIndex);

	private:
		char mpc_GameName[SMALL_PATH];
		void getqueparametersEASY(int* _pi_people, int* _pi_price, int* _pi_pp);
		void getqueparameters(int* _pi_people, float* _pf_price, float* _pf_pp);
};

//---------------------------------------------------------------------------
#endif
