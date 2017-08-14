//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"
#include "Numeric.h"
#include "FileUtils.h"

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"FigureThePhrase");
  mi_Diff = EASY;
  mi_GameType = TEXT;
  mi_TimeOut = 35;
#ifdef TEST
  mi_TimeOut = 999;
#endif
  TFileUtils::GetAllLinesInFile("Phrases.txt", &mpc_AllLines, &mi_n);
} 

TMainGame::~TMainGame()
{
	for (int i = 0; i < mi_n; i++) {
		delete[] *(mpc_AllLines+i);
	}
  delete[] mpc_AllLines;
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
  char* pc_que = new char[MAX_PATH];
  char* pc_ans = new char[MAX_PATH];
  getValues(pc_que, pc_ans);
#ifndef TEST
  sprintf(_pc_QA, "%s%s%s", pc_que, QD, pc_ans);
#else
  sprintf(_pc_QA, "%s%s%s", pc_que, QD, pc_ans);
#endif                              
  delete[] pc_que;
  delete[] pc_ans;
  return TDllRetCodes::DLLRET_OK;
}

void TMainGame::SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff)
{
	mi_Diff = _i_Diff;
}

void TMainGame::GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs)
{
  if(mi_Diff==EASY || mi_Diff==MEDIUM) {
    *_pi_Secs = mi_TimeOut;
  }
  else {
    *_pi_Secs = mi_TimeOut + 10;
  }
}   

void TMainGame::Reset(unsigned int /*_ui_GameIndex*/)
{
}

void TMainGame::getValues(char* _pc_que, char* _pc_ans)
{
  int i_phrase;
  const char* pc_str = "Input the missing letters from the following phrase:\n";
  TNumeric::RandomInt(mi_n, &i_phrase);

  char* pc_quePhrase = new char[MAX_PATH];
  strcpy(pc_quePhrase, *(mpc_AllLines+i_phrase));

  createStrings(pc_quePhrase, _pc_ans);

  sprintf(_pc_que, "%s%s", pc_str, pc_quePhrase); 
  delete[] pc_quePhrase;
}

void TMainGame::createStrings(char* _pc_que, char* _pc_ans)
{
	unsigned int ui_numAlphas = 0;
	for (unsigned int i=0; i<strlen(_pc_que); i++) {
		if (isAlpha(*(_pc_que+i))) ui_numAlphas++;
	}    
	unsigned int ui_alphaIndex = 0;
	unsigned int* charIndices = new unsigned int[ui_numAlphas];
	for (unsigned int i=0; i<strlen(_pc_que); i++) {
		if (isAlpha(*(_pc_que+i))) {
			charIndices[ui_alphaIndex] = i;
			ui_alphaIndex++;
        }
	}

	unsigned int ui_chars = getNumChars(ui_numAlphas);

	TNumeric::ArrayShuffle(charIndices, ui_numAlphas);
	TNumeric::OrderArray(charIndices, ui_chars);
	for (unsigned int i=0; i<ui_chars; i++) {
		_pc_ans[i] = _pc_que[charIndices[i]];
		_pc_que[charIndices[i]] = '*';
	}
	_pc_ans[ui_chars] = 0;
	delete[] charIndices;
}

bool TMainGame::isAlpha(char c)
{
  if ((c>='a' && c<='z') || (c>='A' && c<='Z')) {
	return true;
  }
  return false;
}             

unsigned int TMainGame::getNumChars(unsigned int _ui_numAlphas)
{        
  if(mi_Diff==EASY) {
	return _ui_numAlphas/3;
  }
  else if(mi_Diff==MEDIUM) {
	return _ui_numAlphas/2;
  }
  else {     
	return _ui_numAlphas/2+2;
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
