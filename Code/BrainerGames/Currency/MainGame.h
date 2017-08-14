//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h" 
#include "Conversion.h"
#include <vector>

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
	static const int i_NOGAMES = 8;
	enum TYPE { STERLINGTOEURO, EUROTOSTERLING,
              STERLINGTODOLLAR, DOLLARTOSTERLING,
              STERLINGTOZLOTY, ZLOTYTOSTERLING,
              STERLINGTOFORINT, FORINTTOSTERLING};
  std::vector<TConversionDiffParameters> AllConversionDiffParameters;

  char mpc_GameName[smallbuffer];

	void getqueString(int _i_GameType);
	TConversion* mp_Conversion;
};

//---------------------------------------------------------------------------
#endif
