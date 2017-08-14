//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH

#include "AbstractGame.h" 
#include "string"

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
    //************EASY***********
    static const unsigned int EASY_DEC_HEX_MIN = 10;
    static const unsigned int EASY_DEC_HEX_MAX = 48;
    static const unsigned int EASY_HEX_DEC_MIN = 10;
    static const unsigned int EASY_HEX_DEC_MAX = 48;

    static const unsigned int EASY_DEC_BIN_MIN = 3;
    static const unsigned int EASY_DEC_BIN_MAX = 16;
    static const unsigned int EASY_BIN_DEC_MIN = 3;
    static const unsigned int EASY_BIN_DEC_MAX = 32;

    static const unsigned int EASY_HEX_BIN_MIN = 3;
    static const unsigned int EASY_HEX_BIN_MAX = 16;
    static const unsigned int EASY_BIN_HEX_MIN = 3;
    static const unsigned int EASY_BIN_HEX_MAX = 16;

    //************MEDIUM***********
    static const unsigned int MED_DEC_HEX_MIN = 49;
    static const unsigned int MED_DEC_HEX_MAX = 256; 
    static const unsigned int MED_HEX_DEC_MIN = 49;
    static const unsigned int MED_HEX_DEC_MAX = 256;

    static const unsigned int MED_DEC_BIN_MIN = 17;
    static const unsigned int MED_DEC_BIN_MAX = 31; 
    static const unsigned int MED_BIN_DEC_MIN = 33;
    static const unsigned int MED_BIN_DEC_MAX = 64;

    static const unsigned int MED_HEX_BIN_MIN = 17;
    static const unsigned int MED_HEX_BIN_MAX = 31; 
    static const unsigned int MED_BIN_HEX_MIN = 17;
    static const unsigned int MED_BIN_HEX_MAX = 31;

    //************HARD***********
    static const unsigned int HARD_DEC_HEX_MIN = 257;
    static const unsigned int HARD_DEC_HEX_MAX = 4095; 
    static const unsigned int HARD_HEX_DEC_MIN = 257;
    static const unsigned int HARD_HEX_DEC_MAX = 4095;

    static const unsigned int HARD_DEC_BIN_MIN = 32;
    static const unsigned int HARD_DEC_BIN_MAX = 63;
    static const unsigned int HARD_BIN_DEC_MIN = 65;
    static const unsigned int HARD_BIN_DEC_MAX = 256;

    static const unsigned int HARD_HEX_BIN_MIN = 32;
    static const unsigned int HARD_HEX_BIN_MAX = 63;
    static const unsigned int HARD_BIN_HEX_MIN = 32;
    static const unsigned int HARD_BIN_HEX_MAX = 63;
    enum TYPE {
      DEC_HEX, DEC_BIN, HEX_BIN
    };
    void createString(char* _pc_QA, char* _pc_description, char* _pc_from, char* _pc_to);
    int getFirst(int _i_type, int _i_dir);
    int getLast(int _i_type, int _i_dir);
    std::string dec2bin(unsigned int n);
    void getValues(char* mpc_DecValue, char* mpc_HexValue, char* mpc_BinValue, int _i_type, int _i_dir);
    char mpc_GameName[smallbuffer];
};

//---------------------------------------------------------------------------
#endif
