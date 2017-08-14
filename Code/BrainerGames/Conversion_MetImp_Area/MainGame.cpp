//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include <typeinfo.h>
#include "Numeric.h" 
#include "DllRetCodes.h"

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"Conversion_MetImp_Area");
	mi_Diff = EASY;
	mi_GameType = TEXTNUM;
	mi_TimeOut = 30;
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
	int i_original, i_final, i_percentchange;
	if(mi_Diff == EASY) {
		int i_length, i_width, i_price;
		double d_Conv, d_cost;
		getqueparameters<int, int>(&d_Conv, &i_length, &i_width, &i_price, &d_cost);
		sprintf(_pc_QA,"A room measures %dm by %dm. It costs £%d.00 per square yard of tiling. How much does it cost to tile the room? (1m=%.2fyd)%s%.2f"
		,i_length, i_width, i_price, d_Conv, QD, d_cost);
	}
	if(mi_Diff == MEDIUM) {
		int i_length, i_width, i_price;
		double d_Conv, d_cost;
		getqueparameters<int, int>(&d_Conv, &i_length, &i_width, &i_price, &d_cost);
		sprintf(_pc_QA,"A room measures %dm by %dm. It costs £%d.00 per square yard of tiling. How much does it cost to tile the room? (1m=%.2fyd)%s%.2f"
		,i_length, i_width, i_price, d_Conv, QD, d_cost);
	}
	else if(mi_Diff == HARD) {
		int i_length, i_width, i_price;
		double d_Conv, d_cost;
		getqueparameters<int, int>(&d_Conv, &i_length, &i_width, &i_price, &d_cost);
		sprintf(_pc_QA,"A room measures %dm by %dm. It costs £%d.00 per square yard of tiling. How much does it cost to tile the room (to the nearest pound)? (1m=%.2fyd)%s%.2f"
		,i_length, i_width, i_price, d_Conv, QD, d_cost);
	}           
  return TDllRetCodes::DLLRET_OK;
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

template <class T, class U>
void TMainGame::getqueparameters(double* _d_Conv, T* _T_length, T* _T_width, U* _U_price, double* _d_cost)
{
	int i_length, i_width;

  int i_lengthStart;
  if(mi_Diff == EASY) {
    i_lengthStart = 1500;
  }
  else {
    i_lengthStart = 1100;
  }
	TNumeric::RandomInt(i_lengthStart, &i_length);
  if(mi_Diff == EASY) {
	  i_length+=200;
  }
  else {
    i_length+=1000;
  }
  int i_widthStart;
  if(mi_Diff == EASY) {
    if(i_length > 1000) {
      i_widthStart = 800;
    }
    else {
      i_widthStart = 900;
    }
  }
  else {
    i_widthStart = 1100;
  }
	TNumeric::RandomInt(i_widthStart, &i_width);
  if(mi_Diff == EASY) {
    if(i_length > 1000) {
      i_width+=200;
    }
    else {
      i_width+=1000;
    }
  }
  else {
    i_width+=1000;
  }

	*_T_length = static_cast<T>(static_cast<double>(i_length) / 100);
	*_T_width = static_cast<T>(static_cast<double>(i_width) / 100);
	if(typeid(T) == typeid(float) || typeid(T) == typeid(double)) {
		(*_T_length)+=0.0000000001;
		(*_T_width)+=0.0000000001;
	}

	int i_price;
  *_U_price = 0;
  while (*_U_price<1) {
    TNumeric::RandomInt(5000, &i_price);
    *_U_price = static_cast<U>(i_price+501) / 100;
    *_U_price = (*_U_price/5)*5;
    if(typeid(T) == typeid(float) || typeid(T) == typeid(double)) {
      (*_U_price)+=0.0000000001;
    }
  }

	if(mi_Diff == EASY || mi_Diff == MEDIUM)
		*_d_Conv = 1.0000000001;
	else
		*_d_Conv = 1.0100000001;

	*_d_cost = (*_T_length)*(*_d_Conv)*(*_T_width)*(*_d_Conv) * (*_U_price);
	(*_d_cost)+=0.0000000001;
	TNumeric::RoundPrecision(*_d_cost, _d_cost, 0);
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
