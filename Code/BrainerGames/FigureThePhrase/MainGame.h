//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h"

class TMainGame : public TGenGame
{
  public:
	TMainGame();
	~TMainGame();
    unsigned int GetNumberOfGames(){return 1;}
	void GetGameName(unsigned int /*_ui_GameIndex*/, char* _pc_GameName);
	void GetGameType(unsigned int /*_ui_GameIndex*/, int* _piGameType);
	int GetQA(unsigned int /*_ui_GameIndex*/, char* _pcQA);
	void SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff);
	void GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs);
    void Reset(unsigned int _ui_GameIndex);

  private:
	char mpc_GameName[SMALL_PATH];
	void getValues(char* _pc_que, char* _pc_ans);
	void createStrings(char* _pc_que, char* _pc_ans);
	bool isAlpha(char c);
	unsigned int getNumChars(unsigned int _ui_numAlphas);
	int mi_n;
	char** mpc_AllLines;
};

//---------------------------------------------------------------------------
#endif
