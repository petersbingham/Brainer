//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"  
#include "Numeric.h"    
#include "RandomDate.h"
#include <vector>
using namespace std;

using namespace DateHelper;

TMainGame::TMainGame()
{
  strcpy(mpc_GameName,"DaysDate");
  mi_Diff = EASY;
  mi_GameType = RADIO;
  mi_TimeOut = 15;
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
  sDateYear currentDate, futureDate;
  unsigned int ui_noDays;

  getDates(currentDate, futureDate, ui_noDays);
  vector<unsigned int> wrongDays;
  TRandomDate::CreateRandomDays(futureDate.me_weekday, wrongDays, 4);
  unsigned int ui_correctIndex;
  TNumeric::RandomInt(5, &ui_correctIndex);
  vector<unsigned int> allDays;
  for (unsigned int i=0; i < 5; i++) {
    if(i==ui_correctIndex){
      allDays.push_back(futureDate.me_weekday);
    }
    else {
      allDays.push_back(wrongDays.back());
      wrongDays.pop_back();
    }
  }
  sprintf(_pc_QA, "Today is %s %d/%d/%d. What day is %d/%d/%d?%s%s%s%s%s%s%s%s%s%s%s%d",
          TDateFunctions::GetStringForWeekDay(currentDate.me_weekday).c_str(),
          currentDate.mui_day, currentDate.mui_month, currentDate.mui_year,
          futureDate.mui_day, futureDate.mui_month, futureDate.mui_year,QD,
          TDateFunctions::GetStringForWeekDay(allDays[0]).c_str(),QD,
          TDateFunctions::GetStringForWeekDay(allDays[1]).c_str(),QD,
          TDateFunctions::GetStringForWeekDay(allDays[2]).c_str(),QD,
          TDateFunctions::GetStringForWeekDay(allDays[3]).c_str(),QD,
          TDateFunctions::GetStringForWeekDay(allDays[4]).c_str(),QD,
          ui_correctIndex+1);

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

void TMainGame::getDates(DateHelper::sDateYear& _currentDate, DateHelper::sDateYear& _futureDate, unsigned int& _ui_noDays)
{
	if(mi_Diff == EASY) {
    TRandomDate::GetDate(_currentDate, 1990, 2015, JANUARY, DECEMBER, 1, 10);

    _futureDate.mui_year = _currentDate.mui_year;
    _futureDate.mui_month = _currentDate.mui_month;
    TRandomDate::GetDateDay(_futureDate.mui_day, _futureDate.mui_month, _futureDate.mui_year, 20, 31);
    TDateFunctions::SetWeekDay(_futureDate);

    _ui_noDays = TDateFunctions::GetNumberOfWholeDaysBetweenDates(_currentDate, _futureDate);
	}
	else if(mi_Diff == MEDIUM) {   
    TRandomDate::GetDate(_currentDate, 1990, 2015, JANUARY, NOVEMBER, 1, 25);

    _futureDate.mui_year = _currentDate.mui_year;
    _futureDate.mui_month = _currentDate.mui_month+1;
    TRandomDate::GetDateDay(_futureDate.mui_day, _futureDate.mui_month, _futureDate.mui_year, 5, 20); 
    TDateFunctions::SetWeekDay(_futureDate);

    _ui_noDays = TDateFunctions::GetNumberOfWholeDaysBetweenDates(_currentDate, _futureDate);
  }
	else if(mi_Diff == HARD) {
    TRandomDate::GetDate(_currentDate, 1990, 2015, JANUARY, SEPTEMBER, 1, 25);

    _futureDate.mui_year = _currentDate.mui_year;
    int i_noMonths;
    TNumeric::RandomInt(2, &i_noMonths);
    i_noMonths += 2;
    _futureDate.mui_month = _currentDate.mui_month + i_noMonths;
    TRandomDate::GetDateDay(_futureDate.mui_day, _futureDate.mui_month, _futureDate.mui_year, 5, 20);  
    TDateFunctions::SetWeekDay(_futureDate);

    _ui_noDays = TDateFunctions::GetNumberOfWholeDaysBetweenDates(_currentDate, _futureDate);
	}
}


//---------------------------------------------------------------------------
#pragma package(smart_init)