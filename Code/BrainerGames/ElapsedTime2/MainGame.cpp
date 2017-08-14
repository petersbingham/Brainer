//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"
#include "Numeric.h"    
#include "RandomDate.h"

using namespace DateHelper;

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"ElapsedTime2");
  mi_Diff = EASY;
  mi_GameType = TEXTNUM;
  mi_TimeOut = 45;
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
  sDateYear currentDate, leaveDate, returnDate;
  unsigned int ui_Delay, ui_nodays;

  int i_type;
  TNumeric::RandomInt(2, &i_type);

	char tempstringInfo[128];
	strcpy(tempstringInfo,"\n\n(Assume no statutory holidays over this period. Ranges are inclusive.)");
  if(i_type==0) {
    getDates(leaveDate, returnDate, ui_nodays);
#ifndef TEST
		sprintf(_pc_QA, "Going on holiday from %s %d/%d/%d to %d/%d/%d. How many days do I need to book off work?%s%s%d",
            TDateFunctions::GetStringForWeekDay(leaveDate.me_weekday).c_str(),
            leaveDate.mui_day, leaveDate.mui_month, leaveDate.mui_year,
            returnDate.mui_day, returnDate.mui_month, returnDate.mui_year,
            tempstringInfo,QD,ui_nodays);
#else
		sprintf(_pc_QA, "Going on holiday from %s %d/%d/%d to %d/%d/%d. How many days do I need to book off work?%s%d%s%d",
            TDateFunctions::GetStringForWeekDay(leaveDate.me_weekday).c_str(),
            leaveDate.mui_day, leaveDate.mui_month, leaveDate.mui_year,
            returnDate.mui_day, returnDate.mui_month, returnDate.mui_year,
            tempstringInfo,ui_nodays,QD,ui_nodays);
#endif
  }
  else {
    getDatesDelay(currentDate, ui_Delay, leaveDate, returnDate, ui_nodays);
#ifndef TEST
		sprintf(_pc_QA, "Today is %s %d/%d/%d. Going on holiday in %d days time, until the %d/%d/%d. How many days do I need to book off work?%s%s%d",
            TDateFunctions::GetStringForWeekDay(currentDate.me_weekday).c_str(),
            currentDate.mui_day, currentDate.mui_month, currentDate.mui_year,
            ui_Delay,
            returnDate.mui_day, returnDate.mui_month, returnDate.mui_year,
            tempstringInfo,QD,ui_nodays);
#else
		sprintf(_pc_QA, "Today is %s %d/%d/%d. Going on holiday in %d days time, until the %d/%d/%d. How many days do I need to book off work?%s%d%s%d",
            TDateFunctions::GetStringForWeekDay(currentDate.me_weekday).c_str(),
            currentDate.mui_day, currentDate.mui_month, currentDate.mui_year,
            ui_Delay,
            returnDate.mui_day, returnDate.mui_month, returnDate.mui_year,
            tempstringInfo,ui_nodays,QD,ui_nodays);
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

void TMainGame::getDates(DateHelper::sDateYear& _leaveDate, DateHelper::sDateYear& _returnDate, unsigned int& _ui_noDays)
{
	if(mi_Diff == EASY) {
    TRandomDate::GetDate(_leaveDate, 1990, 2015, JANUARY, DECEMBER, 1, 10);

    _returnDate.mui_year = _leaveDate.mui_year;
    _returnDate.mui_month = _leaveDate.mui_month;
    TRandomDate::GetDateDay(_returnDate.mui_day, _returnDate.mui_month, _returnDate.mui_year, 20, 31);

    _ui_noDays = TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(_leaveDate, _returnDate);
	}
	else if(mi_Diff == MEDIUM) {   
    TRandomDate::GetDate(_leaveDate, 1990, 2015, JANUARY, NOVEMBER, 1, 25);

    _returnDate.mui_year = _leaveDate.mui_year;
    _returnDate.mui_month = _leaveDate.mui_month+1;
    TRandomDate::GetDateDay(_returnDate.mui_day, _returnDate.mui_month, _returnDate.mui_year, 5, 20);

    _ui_noDays = TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(_leaveDate, _returnDate);
  }
	else if(mi_Diff == HARD) {
    TRandomDate::GetDate(_leaveDate, 1990, 2015, JANUARY, SEPTEMBER, 1, 25);

    _returnDate.mui_year = _leaveDate.mui_year;
    int i_noMonths;
    TNumeric::RandomInt(2, &i_noMonths);
    i_noMonths += 2;
    _returnDate.mui_month = _leaveDate.mui_month + i_noMonths;
    TRandomDate::GetDateDay(_returnDate.mui_day, _returnDate.mui_month, _returnDate.mui_year, 5, 20);

    _ui_noDays = TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(_leaveDate, _returnDate);
	}
}

void TMainGame::getDatesDelay(DateHelper::sDateYear& _currentDate, unsigned int& _ui_Delay, DateHelper::sDateYear& _leaveDate, DateHelper::sDateYear& _returnDate, unsigned int& _ui_noDays)
{
	if(mi_Diff == EASY) {
    TRandomDate::GetDate(_currentDate, 1990, 2015, JANUARY, DECEMBER, 1, 10);
    _leaveDate.mui_year = _currentDate.mui_year;
    _leaveDate.mui_month = _currentDate.mui_month;
    TRandomDate::GetDateDay(_leaveDate.mui_day, _leaveDate.mui_month, _leaveDate.mui_year, 12, 16);
    _returnDate.mui_year = _currentDate.mui_year;
    _returnDate.mui_month = _currentDate.mui_month;
    TRandomDate::GetDateDay(_returnDate.mui_day, _returnDate.mui_month, _returnDate.mui_year, 18, 23);

    _ui_Delay = TDateFunctions::GetNumberOfWholeDaysBetweenDates(_currentDate, _leaveDate);
    _ui_noDays = TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(_leaveDate, _returnDate);
	}
	else if(mi_Diff == MEDIUM) {
    TRandomDate::GetDate(_currentDate, 1990, 2015, JANUARY, NOVEMBER, 1, 31);
    _leaveDate.mui_year = _currentDate.mui_year;
    _leaveDate.mui_month = _currentDate.mui_month+1;
    TRandomDate::GetDateDay(_leaveDate.mui_day, _leaveDate.mui_month, _leaveDate.mui_year, 1, 15);
    _returnDate.mui_year = _leaveDate.mui_year;
    _returnDate.mui_month = _leaveDate.mui_month;
    TRandomDate::GetDateDay(_returnDate.mui_day, _returnDate.mui_month, _returnDate.mui_year, 17, 31);

    _ui_Delay = TDateFunctions::GetNumberOfWholeDaysBetweenDates(_currentDate, _leaveDate);
    _ui_noDays = TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(_leaveDate, _returnDate);
  }
	else if(mi_Diff == HARD) {
    TRandomDate::GetDate(_currentDate, 1990, 2015, JANUARY, SEPTEMBER, 1, 31);
    _leaveDate.mui_year = _currentDate.mui_year;
    _leaveDate.mui_month = _currentDate.mui_month+1;
    TRandomDate::GetDateDay(_leaveDate.mui_day, _leaveDate.mui_month, _leaveDate.mui_year, 1, 31);
    int i_noMonths;
    TNumeric::RandomInt(2, &i_noMonths);
    i_noMonths += 1;
    _returnDate.mui_year = _leaveDate.mui_year;
    _returnDate.mui_month = _leaveDate.mui_month+i_noMonths;
    TRandomDate::GetDateDay(_returnDate.mui_day, _returnDate.mui_month, _returnDate.mui_year, 1, 31);

    _ui_Delay = TDateFunctions::GetNumberOfWholeDaysBetweenDates(_currentDate, _leaveDate);
    _ui_noDays = TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(_leaveDate, _returnDate);
	}
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
