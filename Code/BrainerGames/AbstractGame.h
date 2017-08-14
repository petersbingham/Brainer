//---------------------------------------------------------------------------

#ifndef AbstractGameH
#define AbstractGameH

#include<stdlib.h>
#include<stdio.h>

#define SMALL_PATH 28
#define EXLARGE_PATH 1024
#define STRSIZE 128

class TInterface
{
	public:
		virtual ~TInterface(){};
		virtual unsigned int GetNumberOfGames() = 0;
		virtual unsigned int GetNumberOfQuestions(unsigned int _ui_GameIndex) = 0;
		virtual void GetGameName(unsigned int _ui_GameIndex, char* _pc_GameName) = 0;
		virtual void GetGameType(unsigned int _ui_GameIndex, int* _pi_GameType) = 0;
		virtual int GetQA(unsigned int _ui_GameIndex, char* _pc_QA) = 0;
		virtual void SetDiff(unsigned int _ui_GameIndex, int _i_Diff) = 0;
		virtual void GetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs) = 0;
		virtual void Reset(unsigned int _ui_GameIndex) = 0;
	protected:
		int mi_Diff;
		int mi_GameType;
		int mi_TimeOut;
};

class TGenGame : public TInterface
{
	public:          
		virtual ~TGenGame(){};
		virtual unsigned int GetNumberOfGames() = 0;
		unsigned int GetNumberOfQuestions(unsigned int _ui_GameIndex){return 1;};
		virtual void GetGameName(unsigned int _ui_GameIndex, char* _pc_GameName) = 0;
		virtual void GetGameType(unsigned int _ui_GameIndex, int* _pi_GameType) = 0;
		virtual int GetQA(unsigned int _ui_GameIndex, char* _pc_QA) = 0;
		virtual void SetDiff(unsigned int _ui_GameIndex, int _i_Diff) = 0;
		virtual void GetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs) = 0;
		virtual void Reset(unsigned int _ui_GameIndex) = 0;
};

//---------------------------------------------------------------------------
#endif
