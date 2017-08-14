//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "Numeric.h"  
#include "DllRetCodes.h"

//#define TEST

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"MonthlyPayments");
	mi_Diff = EASY;
	mi_GameType = TEXTNUM;
	mi_TimeOut = 23;
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
	int _i_itemCost, _i_modifier;
	double _d_payments;
	if(mi_Diff == EASY) {
		getqueparameters(&_i_itemCost, &_i_modifier, &_d_payments);
		int i_payments;
		TNumeric::RoundToNearestInt(_d_payments, &i_payments);
		if(_i_modifier>0)
#ifdef TEST
			sprintf(_pc_QA,"An item costs £%d with %d%% added interest over a period of 10 monthly payments. What is each payment made? (to the nearest pound)%d%s%d",_i_itemCost, _i_modifier, i_payments, QD, i_payments);
#else
			sprintf(_pc_QA,"An item costs £%d with %d%% added interest over a period of 10 monthly payments. What is each payment made? (to the nearest pound)%s%d",_i_itemCost, _i_modifier, QD, i_payments);
#endif
		else
#ifdef TEST
			sprintf(_pc_QA,"An item costs £%d with a %d%% deduction. If 10 montly payments are made, what is the value of each? (to the nearest pound)%d%s%d",_i_itemCost, _i_modifier, i_payments, QD, i_payments);
#else
			sprintf(_pc_QA,"An item costs £%d with a %d%% deduction. If 10 montly payments are made, what is the value of each? (to the nearest pound)%s%d",_i_itemCost, _i_modifier, QD, i_payments);
#endif
	}
	else if(mi_Diff == MEDIUM) {
		getqueparameters(&_i_itemCost, &_i_modifier, &_d_payments);
		int i_payments;
		TNumeric::RoundToNearestInt(_d_payments, &i_payments);
		if(_i_modifier>0)
#ifdef TEST
			sprintf(_pc_QA,"An item costs £%d with %d%% added interest over a period of 12 monthly payments. What is each payment made? (to the nearest pound)%d%s%d",_i_itemCost, _i_modifier, i_payments, QD, i_payments);
#else
			sprintf(_pc_QA,"An item costs £%d with %d%% added interest over a period of 12 monthly payments. What is each payment made? (to the nearest pound)%s%d",_i_itemCost, _i_modifier, QD, i_payments);
#endif
		else
#ifdef TEST
			sprintf(_pc_QA,"An item costs £%d with a %d%% deduction. If 12 montly payments are made, what is the value of each? (to the nearest pound)%d%s%d",_i_itemCost, _i_modifier, i_payments, QD, i_payments);
#else
			sprintf(_pc_QA,"An item costs £%d with a %d%% deduction. If 12 montly payments are made, what is the value of each? (to the nearest pound)%s%d",_i_itemCost, _i_modifier, QD, i_payments);
#endif
		}
	else if(mi_Diff == HARD) {
		getqueparameters(&_i_itemCost, &_i_modifier, &_d_payments);
		double d_RoundedPayments;
		TNumeric::RoundPrecision(_d_payments, &d_RoundedPayments, 2);
		if(_i_modifier>0)
#ifdef TEST
			sprintf(_pc_QA,"An item costs £%d with %d%% added interest over a period of 12 monthly payments. What is each payment made? (to the nearest pence)%.2f%s%.2f",_i_itemCost, _i_modifier, d_RoundedPayments, QD, d_RoundedPayments);
#else
			sprintf(_pc_QA,"An item costs £%d with %d%% added interest over a period of 12 monthly payments. What is each payment made? (to the nearest pence)%s%.2f",_i_itemCost, _i_modifier, QD, d_RoundedPayments);
#endif
		else
#ifdef TEST
			sprintf(_pc_QA,"An item costs £%d with a %d%% deduction. If 12 montly payments are made, what is the value of each? (to the nearest pence)%.2f%s%.2f",_i_itemCost, _i_modifier, d_RoundedPayments, QD, d_RoundedPayments);
#else
			sprintf(_pc_QA,"An item costs £%d with a %d%% deduction. If 12 montly payments are made, what is the value of each? (to the nearest pence)%s%.2f",_i_itemCost, _i_modifier, QD, d_RoundedPayments);
#endif
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

void TMainGame::getqueparameters(int* _pi_itemCost, int* _pi_modifier, double* _pd_payments)
{
	int i_Temp;
	TNumeric::RandomInt(2000, &i_Temp);
	i_Temp += 30;
  if(i_Temp < 100) {
    *_pi_itemCost = (i_Temp/10)*10;
  }
  else {
    *_pi_itemCost = (i_Temp/100)*100;
  }

	*_pi_modifier = 0;
	while(*_pi_modifier==0) {
		TNumeric::RandomInt(140, &i_Temp);
		i_Temp -= 70;
		*_pi_modifier = (i_Temp/5)*5;
	}

  double _d_Period;
  if(mi_Diff == EASY) {
    _d_Period = 10.0;
  }
  else {
    _d_Period = 12.0;
  }

	*_pd_payments = (*_pi_itemCost * (double)(100+*_pi_modifier)/100.0) / _d_Period;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
