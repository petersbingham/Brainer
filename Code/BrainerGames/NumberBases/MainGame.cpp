//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"  
#include "Numeric.h"

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"NumberBases");
  mi_Diff = EASY;
  mi_GameType = TEXTNUM;
  mi_TimeOut = 21;
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
  char pc_decValue[56], pc_hexValue[56], pc_binValue[56];

  int i_type;
  TNumeric::RandomInt(3, &i_type);
  int i_dir;
  TNumeric::RandomInt(3, &i_dir);

  int value1, value2, valueAnswer;
  getValues(pc_decValue, pc_hexValue, pc_binValue, i_type, i_dir);

  if(i_type==DEC_HEX) {
    if(i_dir == 0) {
      createString(_pc_QA, "decimal to hexadecimal", pc_decValue, pc_hexValue);
    }
    else {
      createString(_pc_QA, "hexadecimal to decimal", pc_hexValue, pc_decValue);
    }
  }
  if(i_type==HEX_BIN) {
    if(i_dir == 0) {
      createString(_pc_QA, "hexadecimal to binary", pc_hexValue, pc_binValue);
    }
    else {
      createString(_pc_QA, "binary to hexadecimal", pc_binValue, pc_hexValue);
    }
  }
  if(i_type==DEC_BIN) {
    if(i_dir == 0) {
      createString(_pc_QA, "decimal to binary", pc_decValue, pc_binValue);
    }
    else {
      createString(_pc_QA, "binary to decimal", pc_binValue, pc_decValue);
    }
  }

  return TDllRetCodes::DLLRET_OK;
}

void TMainGame::createString(char* _pc_QA, char* _pc_description, char* _pc_from, char* _pc_to)
{
#ifndef TEST
	sprintf(_pc_QA, "Convert %s from %s? %s%s", _pc_from, _pc_description, QD, _pc_to);
#else
  sprintf(_pc_QA, "Convert %s from %s?%s%s%s", _pc_from, _pc_description, _pc_to, QD, _pc_to);
#endif
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

int TMainGame::getFirst(int _i_type, int _i_dir)
{
  int i_first;
  if(mi_Diff==EASY) {
    if(_i_type==DEC_HEX)      _i_dir==0 ? i_first=EASY_DEC_HEX_MIN : i_first=EASY_HEX_DEC_MIN;
    else if(_i_type==DEC_BIN) _i_dir==0 ? i_first=EASY_DEC_BIN_MIN : i_first=EASY_BIN_DEC_MIN;
    else if(_i_type==HEX_BIN) _i_dir==0 ? i_first=EASY_HEX_BIN_MIN : i_first=EASY_BIN_HEX_MIN;
  }
  else if(mi_Diff==MEDIUM) {
    if(_i_type==DEC_HEX)      _i_dir==0 ? i_first=MED_DEC_HEX_MIN : i_first=MED_HEX_DEC_MIN;
    else if(_i_type==DEC_BIN) _i_dir==0 ? i_first=MED_DEC_BIN_MIN : i_first=MED_BIN_DEC_MIN;
    else if(_i_type==HEX_BIN) _i_dir==0 ? i_first=MED_HEX_BIN_MIN : i_first=MED_BIN_HEX_MIN;
  }
  else if(mi_Diff==HARD) {
    if(_i_type==DEC_HEX)      _i_dir==0 ? i_first=HARD_DEC_HEX_MIN : i_first=HARD_HEX_DEC_MIN;
    else if(_i_type==DEC_BIN) _i_dir==0 ? i_first=HARD_DEC_BIN_MIN : i_first=HARD_BIN_DEC_MIN;
    else if(_i_type==HEX_BIN) _i_dir==0 ? i_first=HARD_HEX_BIN_MIN : i_first=HARD_BIN_HEX_MIN;
  }
  return i_first;
}

int TMainGame::getLast(int _i_type, int _i_dir)
{
  int i_last;
  if(mi_Diff==EASY) {
    if(_i_type==DEC_HEX)      _i_dir==0 ? i_last=EASY_DEC_HEX_MAX : i_last=EASY_HEX_DEC_MAX;
    else if(_i_type==DEC_BIN) _i_dir==0 ? i_last=EASY_DEC_BIN_MAX : i_last=EASY_BIN_DEC_MAX;
    else if(_i_type==HEX_BIN) _i_dir==0 ? i_last=EASY_HEX_BIN_MAX : i_last=EASY_BIN_HEX_MAX;
  }
  else if(mi_Diff==MEDIUM) {
    if(_i_type==DEC_HEX)      _i_dir==0 ? i_last=MED_DEC_HEX_MAX : i_last=MED_HEX_DEC_MAX;
    else if(_i_type==DEC_BIN) _i_dir==0 ? i_last=MED_DEC_BIN_MAX : i_last=MED_BIN_DEC_MAX;
    else if(_i_type==HEX_BIN) _i_dir==0 ? i_last=MED_HEX_BIN_MAX : i_last=MED_BIN_HEX_MAX;
  }
  else if(mi_Diff==HARD) {
    if(_i_type==DEC_HEX)      _i_dir==0 ? i_last=HARD_DEC_HEX_MAX : i_last=HARD_HEX_DEC_MAX;
    else if(_i_type==DEC_BIN) _i_dir==0 ? i_last=HARD_DEC_BIN_MAX : i_last=HARD_BIN_DEC_MAX;
    else if(_i_type==HEX_BIN) _i_dir==0 ? i_last=HARD_HEX_BIN_MAX : i_last=HARD_BIN_HEX_MAX;
  }
  return i_last;
}

std::string TMainGame::dec2bin(unsigned int n)
{
  const int size=sizeof(n)*8;
  std::string res;        
  bool s=0;
  for (int a=0;a<size;a++){
    bool bit=n>>(size-1);
    if (bit)
      s=1;
    if (s)
      res.push_back(bit+'0');
    n<<=1;
  }
  if (!res.size())
    res.push_back('0');
  return res;
}

void TMainGame::getValues(char* mpc_DecValue, char* mpc_HexValue, char* mpc_BinValue, int _i_type, int _i_dir)
{
  int i_value;
  TNumeric::RandomIntOverIncRange(getFirst(_i_type, _i_dir), getLast(_i_type, _i_dir), &i_value);
  sprintf(mpc_DecValue,"%d",i_value);
  sprintf(mpc_HexValue,"%x",i_value); 
  sprintf(mpc_BinValue,"%s",dec2bin(((unsigned int)i_value)).c_str());
}




//---------------------------------------------------------------------------
#pragma package(smart_init)