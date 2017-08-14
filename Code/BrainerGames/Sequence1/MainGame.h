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
		void getSequence(int* _pi_SeqType);
		void getanswerarrays(int* _pi_Seq, int* _pi_WrongAns, int _i_SeqType);
		void generateSequence(int* _pi_Seq, int _i_SeqType);
		void createdisplaystring(const int* _pi_Seq, const int* _pi_WrongAns, int* _pi_stringarray, int _i_Diff);
};

//---------------------------------------------------------------------------
#endif
