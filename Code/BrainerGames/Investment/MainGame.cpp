//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "Numeric.h"
#include "DllRetCodes.h"

#define DECREASE 0
#define INCREASE 1

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"Investment");
	mi_Diff = EASY;
	mi_GameType = TEXTNUM;
	mi_TimeOut = 24;
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
		getqueparametersEASY(&i_original,&i_final,&i_percentchange);
		sprintf(_pc_QA,"I invested £%d and now have £%d. What is my percentage change?%s%d",i_original,i_final,QD,i_percentchange);
	}
	else if(mi_Diff == MEDIUM) {
		getqueparametersMEDIUM(&i_original,&i_final,&i_percentchange);
		sprintf(_pc_QA,"I invested £%d and now have £%d. What is my percentage change? Give answer to nearest percent, ignoring sign.%s%d",i_original,i_final,QD,i_percentchange);
	}
	else if(mi_Diff == HARD) {
		getqueparametersHARD(&i_original,&i_final,&i_percentchange);
		sprintf(_pc_QA,"I invested £%d and now have £%d. What is my percentage change? Give answer to nearest percent, ignoring sign.%s%d",i_original,i_final,QD,i_percentchange);
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

void TMainGame::getqueparametersEASY(int* _pi_original, int* _pi_final, int* _pi_percentchange)
{
	TNumeric::RandomInt(10, _pi_original);
	(*_pi_original)++;
	if(*_pi_original == 5) {
		*_pi_original = 11;
	}
	if(*_pi_original == 10) {
		*_pi_original = 12;
	}
	(*_pi_original)*=20;

	int i_dir;
	TNumeric::RandomInt(2, &i_dir);

	const int i_increment = 5;
	int i_mult;
	if(i_dir==INCREASE)
		i_mult = 40;
	else
		i_mult = 19;

	TNumeric::RandomInt(i_mult, _pi_percentchange);
	(*_pi_percentchange)++;
	(*_pi_percentchange)*=i_increment;

	if(i_dir==INCREASE)
		*_pi_final = *_pi_original + ((*_pi_original) * (*_pi_percentchange))/100;
	else
		*_pi_final = *_pi_original - ((*_pi_original) * (*_pi_percentchange))/100;
}

void TMainGame::getqueparametersMEDIUM(int* _pi_original, int* _pi_final, int* _pi_percentchange)
{
	TNumeric::RandomInt(30, _pi_original);
	(*_pi_original) += 5;

  *_pi_percentchange = 0;
  while(*_pi_percentchange<1 || *_pi_final==*_pi_original || *_pi_final==0) {
    int i_change;
    const int i_maxchange = 100;
    TNumeric::RandomInt(i_maxchange, &i_change);

    int i_dir;
    TNumeric::RandomInt(2, &i_dir);

    if(i_dir==INCREASE) {
      *_pi_final = (int)(((float)(*_pi_original)) * ((float)(i_change)/((float)(100))) + (float)(*_pi_original));
    }
    else {
      *_pi_final = (int)((float)(i_change)/((float)(i_maxchange)) * (float)(*_pi_original));
    }

    float f_percentchange = ( (float)(*_pi_final)-(float)(*_pi_original) ) / (float)(*_pi_original) * 100;

    if(f_percentchange<0)
      f_percentchange *= -1;

    TNumeric::RoundToNearestInt(f_percentchange, _pi_percentchange);
  }
}

void TMainGame::getqueparametersHARD(int* _pi_original, int* _pi_final, int* _pi_percentchange)
{
	TNumeric::RandomInt(3000, _pi_original);
	(*_pi_original) += 5;

	int i_change;
	const int i_maxchange = 300;
	TNumeric::RandomInt(i_maxchange, &i_change);

	int i_dir;
	TNumeric::RandomInt(2, &i_dir);

	if(i_dir==INCREASE) {
		*_pi_final = (int)(((float)(*_pi_original)) * ((float)(i_change)/((float)(100))) + (float)(*_pi_original));
	}
	else {
		*_pi_final = (int)((float)(i_change)/((float)(i_maxchange)) * (float)(*_pi_original));
	}

	float f_percentchange = ( (float)(*_pi_final)-(float)(*_pi_original) ) / (float)(*_pi_original) * 100;

	if(f_percentchange<0)
		f_percentchange *= -1;

	TNumeric::RoundToNearestInt(f_percentchange, _pi_percentchange);
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
