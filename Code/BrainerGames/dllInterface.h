//---------------------------------------------------------------------------

#ifndef dllInterfaceH
#define dllInterfaceH

#define DLL_DEF __declspec(dllexport)  __stdcall

extern "C" unsigned int DLL_DEF fnGetNumberOfGames(); 
extern "C" unsigned int DLL_DEF fnGetNumberOfQuestions(unsigned int _ui_GameIndex);
extern "C" int DLL_DEF fnGetGameName(unsigned int _ui_GameIndex, char* _pc_GameName);
extern "C" int DLL_DEF fnGetGameType(unsigned int _ui_GameIndex, int* _pi_GameType);
extern "C" int DLL_DEF fnGetQA(unsigned int _ui_GameIndex, char* _pc_QA);
extern "C" int DLL_DEF fnSetDiff(unsigned int _ui_GameIndex, int _i_Diff);
extern "C" int DLL_DEF fnGetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs); 
extern "C" int DLL_DEF fnReset(unsigned int _ui_GameIndex);


//---------------------------------------------------------------------------
#endif
