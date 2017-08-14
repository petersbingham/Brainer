//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"  
#include "Numeric.h"   
#include "FileUtils.h"

#define MINNUMLETS_EASY 3
#define MINNUMLETS_MED 4
#define MINNUMLETS_HARD 5

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"ReduceWord");
  mi_Diff = EASY;
  mi_GameType = TEXTNUM;
  mi_TimeOut = 7;
#ifdef TEST
  mi_TimeOut = 999;
#endif
  mpc_AllLines = 0;
}

TMainGame::~TMainGame()
{                  
  deleteLines();
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
  if(mi_Diff == EASY) {
	mui_minNumLets = MINNUMLETS_EASY;
  }
  else if(mi_Diff == MEDIUM) {
	mui_minNumLets = MINNUMLETS_MED;
  }
  else if(mi_Diff == HARD) {
	mui_minNumLets = MINNUMLETS_HARD;
  }
  refreshLines();
}

void TMainGame::GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs)
{
  *_pi_Secs = mi_TimeOut;
}

void TMainGame::Reset(unsigned int /*_ui_GameIndex*/)
{
}

void TMainGame::getValues(char* _pc_que, char* _pc_ans)
{
  const char* pc_str1 = "Input the first ";
  const char* pc_str2 = " from the following word: ";
             
  int i_phrase;
  TNumeric::RandomInt(mi_n, &i_phrase);

  char* pc_quePhrase = new char[MAX_PATH];
  strcpy(pc_quePhrase, *(mpc_AllLines+i_phrase));
                   
  char* pc_instruct = new char[MAX_PATH];

  createStrings(pc_quePhrase, pc_instruct, _pc_ans);

  sprintf(_pc_que, "%s%s%s%s", pc_str1, pc_instruct, pc_str2, pc_quePhrase);
  delete[] pc_quePhrase;
  delete[] pc_instruct;
}

void TMainGame::createStrings(char* _pc_quePhrase, char* _pc_instruct, char* _pc_ans)
{
  unsigned int ui_type;
  unsigned int ui_num;
  TNumeric::RandomInt(2, &ui_type);
  if (ui_type==0) {
	unsigned int ui_numConsonants = numberConsonants(_pc_quePhrase);
	unsigned int ui_max = ui_numConsonants>=mui_minNumLets+1 ? mui_minNumLets+1 : ui_numConsonants;
	TNumeric::RandomIntOverIncRange(mui_minNumLets, ui_max, &ui_num);
	sprintf(_pc_instruct, "%d %s", ui_num, "consonants");
  }
  else {
	unsigned int ui_numVowels = numberVowels(_pc_quePhrase);
	unsigned int ui_max = ui_numVowels>=mui_minNumLets+1 ? mui_minNumLets+1 : ui_numVowels;
	TNumeric::RandomIntOverIncRange(mui_minNumLets, ui_max, &ui_num);
	sprintf(_pc_instruct, "%d %s", ui_num, "vowels");
  }
  unsigned int ui_cnt = 0;
  for (unsigned int i=0; ui_cnt<ui_num; i++) {
	if (ui_type==0 && isConsonant(_pc_quePhrase[i])) {
	  _pc_ans[ui_cnt] = _pc_quePhrase[i];
	  ui_cnt++;
	}
	else if (ui_type==1 && isVowel(_pc_quePhrase[i])) {
	  _pc_ans[ui_cnt] = _pc_quePhrase[i];
	  ui_cnt++;
	}
  }
  _pc_ans[ui_cnt] = 0;
}

void TMainGame::reduceLines(char** _pc_AllLines, int i_n)
{
	for (int i = 0; i < i_n; i++) {
		char* pc_end = strstr(_pc_AllLines[i], "\n");
		if (pc_end != 0) {
			*pc_end = 0;
		}
	}

	mi_n = 0;
	for (int i = 0; i < i_n; i++) {
		if (isLineGood(_pc_AllLines[i])) {
			mi_n++;
		}
	}

	mpc_AllLines = new char*[mi_n];
	int i_cnt = 0;
	for (int i = 0; i < i_n; i++) {
		if (isLineGood(_pc_AllLines[i])) {
			unsigned int ui_len = strlen(_pc_AllLines[i]);
			mpc_AllLines[i_cnt] = new char[ui_len+1];
			strcpy(mpc_AllLines[i_cnt], _pc_AllLines[i]);
			i_cnt++;
		}
	}
}

bool TMainGame::isLineGood(char* _pc_Line)
{
	if (numberConsonants(_pc_Line)+numberVowels(_pc_Line) != strlen(_pc_Line)) {
		return false;
	}
	if (numberConsonants(_pc_Line)<mui_minNumLets || numberVowels(_pc_Line)<mui_minNumLets) {
		return false;
	}
	return true;
}

unsigned int TMainGame::numberConsonants(char* _pc_Line)
{
  int num = 0;
  for (unsigned int i = 0; i < strlen(_pc_Line); i++) {
	if (isConsonant(_pc_Line[i])) {
	  num++;
	}
  }
  return num;
}

unsigned int TMainGame::numberVowels(char* _pc_Line)
{
  int num = 0;
  for (unsigned int i = 0; i < strlen(_pc_Line); i++) {
	if (isVowel(_pc_Line[i])) {
	  num++;
	}
  }
  return num;
}

void TMainGame::refreshLines()
{
  deleteLines();
  int i_n;
  char** pc_AllLines;
  TFileUtils::GetAllLinesInFile("100000Words.txt", &pc_AllLines, &i_n);
  reduceLines(pc_AllLines, i_n);
  for (int i = 0; i < i_n; i++) {
	  delete[] *(pc_AllLines+i);
  }
  delete[] pc_AllLines;
}

void TMainGame::deleteLines()
{
  if (mpc_AllLines != 0) {
	for (int i = 0; i < mi_n; i++) {
		delete[] *(mpc_AllLines+i);
	}
	delete[] mpc_AllLines;
	mpc_AllLines = 0;
  }
}

bool TMainGame::isConsonant(char Letter)
{
  if (Letter == 'b' || Letter == 'B') {
	return true;
  }     
  else if (Letter == 'c' || Letter == 'C') {
	return true;
  }
  else if (Letter == 'd' || Letter == 'D') {
	return true;
  }
  else if (Letter == 'f' || Letter == 'F') {
	return true;
  }
  else if (Letter == 'g' || Letter == 'G') {
	return true;
  }
  else if (Letter == 'h' || Letter == 'H') {
	return true;
  }
  else if (Letter == 'j' || Letter == 'J') {
	return true;
  }
  else if (Letter == 'k' || Letter == 'K') {
	return true;
  }
  else if (Letter == 'l' || Letter == 'L') {
	return true;
  }
  else if (Letter == 'm' || Letter == 'M') {
	return true;
  }
  else if (Letter == 'n' || Letter == 'N') {
	return true;
  }
  else if (Letter == 'p' || Letter == 'P') {
	return true;
  }
  else if (Letter == 'q' || Letter == 'Q') {
	return true;
  }
  else if (Letter == 'r' || Letter == 'R') {
	return true;
  }
  else if (Letter == 's' || Letter == 'S') {
	return true;
  }
  else if (Letter == 't' || Letter == 'T') {
	return true;
  }
  else if (Letter == 'v' || Letter == 'V') {
	return true;
  }
  else if (Letter == 'w' || Letter == 'W') {
	return true;
  }
  else if (Letter == 'x' || Letter == 'X') {
	return true;
  }
  else if (Letter == 'y' || Letter == 'Y') {
	return true;
  }
  else if (Letter == 'z' || Letter == 'Z') {
	return true;
  }
  return false;
}

bool TMainGame::isVowel(char Letter)
{
  if (Letter == 'a' || Letter == 'A') {
	return true;
  }
  else if (Letter == 'e' || Letter == 'E') {
	return true;
  }
  else if (Letter == 'i' || Letter == 'I') {
	return true;
  }
  else if (Letter == 'o' || Letter == 'O') {
	return true;
  }
  else if (Letter == 'u' || Letter == 'U') {
	return true;
  }
  return false;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)