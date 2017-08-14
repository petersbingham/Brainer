//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h"

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
		char mpc_GameName[SMALL_PATH];
		template <class T, class U> void TMainGame::getqueparameters(double* _d_Conv, T* _T_length, T* _T_width, U* _U_price, double* _d_cost);

};

//---------------------------------------------------------------------------
#endif
