//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "Numeric.h"  
#include "DllRetCodes.h"

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"Restaurant");
	mi_Diff = EASY;
	mi_GameType = TEXTNUM;
	mi_TimeOut = 18;
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
	if(mi_Diff == EASY) {
		int i_people;
		int i_price, i_pp;
		getqueparametersEASY(&i_people, &i_price, &i_pp);
#ifdef TEST
		sprintf(_pc_QA,"Restaurant bill of %d for %d people. What is the average bill (in pounds)?%d%s%d",i_price,i_people,i_pp,QD,i_pp);
#else
		sprintf(_pc_QA,"Restaurant bill of %d for %d people. What is the average bill (in pounds)?%s%d",i_price,i_people,QD,i_pp);
#endif
	}
	else {
		int i_people;
		float f_price, f_pp;
		getqueparameters(&i_people, &f_price, &f_pp);
		if(mi_Diff == MEDIUM) {
			int i_pp;
			TNumeric::RoundToNearestInt(f_pp, &i_pp);
#ifdef TEST
			sprintf(_pc_QA,"Restaurant bill of %.2f for %d people. What is the average bill (to the nearest pound)? Give your answer in pounds only.%d%s%d",f_price,i_people,i_pp,QD,i_pp);
#else
			sprintf(_pc_QA,"Restaurant bill of %.2f for %d people. What is the average bill (to the nearest pound)? Give your answer in pounds only.%s%d",f_price,i_people,QD,i_pp);
#endif
		}
		else if(mi_Diff == HARD) {
#ifdef TEST
			sprintf(_pc_QA,"Restaurant bill of %.2f for %d people. What is the average bill (to the nearest pence)? Give your answer in pounds and pence.%.2f%s%.2f",f_price,i_people,f_pp,QD,f_pp);
#else
			sprintf(_pc_QA,"Restaurant bill of %.2f for %d people. What is the average bill (to the nearest pence)? Give your answer in pounds and pence.%s%.2f",f_price,i_people,QD,f_pp);
#endif
		}
	} 
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

void TMainGame::getqueparametersEASY(int* _pi_people, int* _pi_price, int* _pi_pp)
{
	*_pi_pp = 10;
	while(*_pi_pp % 10 == 0) {
		TNumeric::RandomInt(30, _pi_pp);
		(*_pi_pp) += 7;
	}

	*_pi_people = 10;
	while(*_pi_people % 10 == 0) {
		TNumeric::RandomInt(15, _pi_people);
		(*_pi_people) += 5;
		*_pi_price =  (*_pi_people) * (*_pi_pp);
	}
}

void TMainGame::getqueparameters(int* _pi_people, float* _pf_price, float* _pf_pp)
{
	int i_pp;
	TNumeric::RandomInt(3000, &i_pp);
	i_pp += 700;
	*_pf_pp = ((float)i_pp)/100;

	*_pi_people = 10;
	while(*_pi_people % 10 == 0) {
    TNumeric::RandomInt(15, _pi_people);
    (*_pi_people) += 5;
    *_pf_price =  (*_pi_people) * (*_pf_pp);
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
