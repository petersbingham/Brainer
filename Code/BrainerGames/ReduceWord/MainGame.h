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
	~TMainGame();
    unsigned int GetNumberOfGames(){return 1;}
    void GetGameName(unsigned int _ui_GameIndex, char* _pc_GameName);
    void GetGameType(unsigned int _ui_GameIndex, int* _piGameType);
    int GetQA(unsigned int _ui_GameIndex, char* _pcQA);
    void SetDiff(unsigned int _ui_GameIndex, int _pi_Secs);
    void GetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs);    
    void Reset(unsigned int _ui_GameIndex);

  private:
	void getValues(char* _pc_que, char* _pc_ans);
	void createStrings(char* _pc_quePhrase, char* _pc_instruct, char* _pc_ans);    
	void reduceLines(char** _pc_AllLines, int i_n);
	bool isLineGood(char* _pc_Line);
	unsigned int numberConsonants(char* _pc_Line);
	unsigned int numberVowels(char* _pc_Line);
	bool isConsonant(char Letter);
	bool isVowel(char Letter);
	void refreshLines();
	void deleteLines();
	char mpc_GameName[smallbuffer];
	int mi_n;
	char** mpc_AllLines;
	unsigned int mui_minNumLets;
};

//---------------------------------------------------------------------------
#endif
