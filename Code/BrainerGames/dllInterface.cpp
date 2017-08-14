//---------------------------------------------------------------------------

#include <windows.h>
#include "MainGame.h"
#include "dllInterface.h"
#include "DllRetCodes.h"

TMainGame MainGame;

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}

unsigned int DLL_DEF fnGetNumberOfGames()
{
	return MainGame.GetNumberOfGames();
}     

unsigned int DLL_DEF fnGetNumberOfQuestions(unsigned int _ui_GameIndex)
{          
	return MainGame.GetNumberOfQuestions(_ui_GameIndex);
}

int DLL_DEF fnGetGameName(unsigned int _ui_GameIndex, char* _pc_GameName)
{
  int i_Ret;
  if(_ui_GameIndex<MainGame.GetNumberOfGames()) {
    MainGame.GetGameName(_ui_GameIndex, _pc_GameName);
    i_Ret = TDllRetCodes::DLLRET_OK;
  }
  else {
    i_Ret = TDllRetCodes::DLLRET_GAMEINDEXOUTSIDERANGE;
  }
  return i_Ret;
}

int DLL_DEF fnGetGameType(unsigned int _ui_GameIndex, int* _pi_GameType)
{
  int i_Ret;
  if(_ui_GameIndex<MainGame.GetNumberOfGames()) {
	MainGame.GetGameType(_ui_GameIndex, _pi_GameType);
	i_Ret = TDllRetCodes::DLLRET_OK;
  }
  else {
    i_Ret = TDllRetCodes::DLLRET_GAMEINDEXOUTSIDERANGE;
  }
  return i_Ret;
}

int DLL_DEF fnGetQA(unsigned int _ui_GameIndex, char* _pc_QA)
{  
  int i_Ret;
  if(_ui_GameIndex<MainGame.GetNumberOfGames()) {
    i_Ret = MainGame.GetQA(_ui_GameIndex, _pc_QA);
  }
  else {
    i_Ret = TDllRetCodes::DLLRET_GAMEINDEXOUTSIDERANGE;
  }
  return i_Ret;
}

int DLL_DEF fnSetDiff(unsigned int _ui_GameIndex, int _i_Diff)
{  
  int i_Ret;
  if(_ui_GameIndex<MainGame.GetNumberOfGames()) {
    MainGame.SetDiff(_ui_GameIndex, _i_Diff);
    i_Ret = TDllRetCodes::DLLRET_OK;
  }
  else {
    i_Ret = TDllRetCodes::DLLRET_GAMEINDEXOUTSIDERANGE;
  }
  return i_Ret;
}

int DLL_DEF fnGetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs)
{ 
  int i_Ret;
  if(_ui_GameIndex<MainGame.GetNumberOfGames()) {
    MainGame.GetTimeLimit(_ui_GameIndex, _pi_Secs);
    i_Ret = TDllRetCodes::DLLRET_OK;
  }
  else {
    i_Ret = TDllRetCodes::DLLRET_GAMEINDEXOUTSIDERANGE;
  }
  return i_Ret;
}

int DLL_DEF fnReset(unsigned int _ui_GameIndex)
{ 
  int i_Ret;
  if(_ui_GameIndex<MainGame.GetNumberOfGames()) {
    MainGame.Reset(_ui_GameIndex);
    i_Ret = TDllRetCodes::DLLRET_OK;
  }
  else {
    i_Ret = TDllRetCodes::DLLRET_GAMEINDEXOUTSIDERANGE;
  }
  return i_Ret;
}
