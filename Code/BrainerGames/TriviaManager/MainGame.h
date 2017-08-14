//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h"
#include "Questions.h"

#define smallbuffer 28
#define STRSIZE 128

//#define TEST

class TMainGame : public TInterface
{
  public:
    TMainGame();
	unsigned int GetNumberOfGames(){return mi_NoQuestionFiles;}
	unsigned int GetNumberOfQuestions(unsigned int _ui_GameIndex);
    void GetGameName(unsigned int _ui_GameIndex, char* _pc_GameName);
    void GetGameType(unsigned int _ui_GameIndex, int* _piGameType);
    int GetQA(unsigned int _ui_GameIndex, char* _pcQA);
    void SetDiff(unsigned int _ui_GameIndex, int _pi_Secs);
    void GetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs);
    void Reset(unsigned int _ui_GameIndex);

  private:
    int mi_NoQuestionFiles;
    unsigned int getLastQueDiff();
    void populateQuestionReaderWriterVec();
    void setGameType();
    std::vector<TQuestionReaderWriter> m_QuestionReaderWriterVec;
    unsigned int mui_LastQueDiff;
};

//---------------------------------------------------------------------------
#endif
