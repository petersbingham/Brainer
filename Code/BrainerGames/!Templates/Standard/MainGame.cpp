//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"  
#include "Numeric.h"    

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"Template");
  mi_Diff = EASY;
  mi_GameType = TEXTNUM;
  mi_TimeOut = 35;
#ifdef TEST
  mi_TimeOut = 999;
#endif
}

void TMainGame::GetGameName(unsigned int /*_ui_GameIndex*/, char* _pc_GameName)
{
  strcpy(_pc_GameName,mpc_GameName);
}

void TMainGame::GetGameType(unsigned int /*_ui_GameIndex*/, int* _pi_GameType)
{
  *_pi_GameType = mi_GameType;
}

int TMainGame::GetQA(unsigned int /*_ui_GameIndex*/, char* _pc_QA)
{
  int i_type;
  TNumeric::RandomInt(2, &i_type);

  int value1, value2, valueAnswer;
  if(i_type==0) {
    getValues(value1, value2, valueAnswer);
#ifndef TEST
		sprintf(_pc_QA, "%d plus %d equals what? %s%d", value1, value2, QD, valueAnswer);
#else
		sprintf(_pc_QA, "%d plus %d equals what? %d%s%d", value1, value2, valueAnswer, QD, valueAnswer);
#endif
  }
}

void TMainGame::SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff)
{
  mi_Diff = _i_Diff;
}

void TMainGame::GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs)
{
  *_pi_Secs = mi_TimeOut;
}

void TMainGame::Reset(unsigned int /*_ui_GameIndex*/)
{
}

void TMainGame::getValues(int& value1, int& value2, int& valueAnswer)
{
  valueAnswer = 2+3;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)