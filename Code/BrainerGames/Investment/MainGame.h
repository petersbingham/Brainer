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
		void getqueparametersEASY(int* _pi_original, int* _pi_final, int* _pi_percentchange);
		void getqueparametersMEDIUM(int* _pi_original, int* _pi_final, int* _pi_percentchange);
		void getqueparametersHARD(int* _pi_original, int* _pi_final, int* _pi_percentchange);
		void getqueparameters(	int* _pi_original,
														int* _pi_final,
														int* _pi_percentchange,
														const int _i_maxoriginal,
														const int _i_maxchange,
														const int _i_increment
														);

};

//---------------------------------------------------------------------------
#endif
