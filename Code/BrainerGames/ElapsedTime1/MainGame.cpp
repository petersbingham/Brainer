//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "Numeric.h"
#include "DllRetCodes.h" 

//#define TEST
//#define TEST2

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"ElapsedTime1");
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
	int i_original, i_final, i_percentchange;
	sDateRange DateRange;
	sTime TimeDiff;
	getqueparameters(DateRange, TimeDiff);
	char tempstring[128];

	sprintf(tempstring,"From %d/%d/%d to %d/%d/%d",
		DateRange.From.mui_day,DateRange.From.mui_month,DateRange.From.mui_year,
		DateRange.To.mui_day,DateRange.To.mui_month,DateRange.To.mui_year);

	char tempstring2[128];
	strcpy(tempstring2,"\n\n(From date is just after midnight. To date is just before midnight)");

	if(mi_Diff == EASY) {
#ifndef TEST
		sprintf(_pc_QA,"%s how many full years elapsed?%s%s%d",tempstring,tempstring2,QD,TimeDiff.mi_Years);
#else
		sprintf(_pc_QA,"%s how many full years elapsed?%s%d%s%d",tempstring,tempstring2,TimeDiff.mi_Years,QD,TimeDiff.mi_Years);
#endif
	}
	else if(mi_Diff == MEDIUM) {
#ifndef TEST
		sprintf(_pc_QA,"%s how many full months elapsed?%s%s%d",tempstring,tempstring2,QD,TimeDiff.mi_Months);
#else
		sprintf(_pc_QA,"%s how many full months elapsed?%s%d%s%d",tempstring,tempstring2,TimeDiff.mi_Months,QD,TimeDiff.mi_Months);
#endif
		}
	else if(mi_Diff == HARD) {
#ifndef TEST
		sprintf(_pc_QA,"%s how many full weeks elapsed?%s%s%d",tempstring,tempstring2,QD,TimeDiff.mi_Weeks);
#else
		sprintf(_pc_QA,"%s how many full weeks elapsed?%s%d%s%d",tempstring,tempstring2,TimeDiff.mi_Weeks,QD,TimeDiff.mi_Weeks);
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

void TMainGame::getqueparameters(sDateRange& _DateRange, sTime& _TimeDiff)
{
  TRandomDate Date;

  Date.GetDate(_DateRange.From,0,2500);

  if(mi_Diff == EASY) {
    Date.GetDate(_DateRange.To,_DateRange.From.mui_year+1,3000);
  }
  else {
    Date.GetDate(_DateRange.To,_DateRange.From.mui_year+11,_DateRange.From.mui_year+100);
  }

#ifdef TEST2
	_DateRange.To.mui_month = _DateRange.From.mui_month;
	_DateRange.To.mui_day = _DateRange.From.mui_day;
#endif

	_TimeDiff.mi_Weeks = TDateFunctions::GetNumberOfWholeWeeksBetweenDates(_DateRange.From, _DateRange.To);

	_TimeDiff.mi_Months = TDateFunctions::GetNumberOfWholeMonthsBetweenDates(_DateRange.From, _DateRange.To);

	_TimeDiff.mi_Years = TDateFunctions::GetNumberOfWholeYearsBetweenDates(_DateRange.From, _DateRange.To);
}



//---------------------------------------------------------------------------
#pragma package(smart_init)
