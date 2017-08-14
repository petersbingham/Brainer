//---------------------------------------------------------------------------
#pragma hdrstop

#include "RandomDate.h"
#include "Numeric.h"
#include <algorithm>

using namespace std;
using namespace DateHelper;

void TRandomDate::correctYears(unsigned int& _ui_MinYear, unsigned int& _ui_MaxYear)
{
  TDateFunctions::correctYear(_ui_MinYear);
  TDateFunctions::correctYear(_ui_MaxYear);
  if(_ui_MinYear > _ui_MaxYear) {
    TNumeric::Swap(_ui_MinYear, _ui_MaxYear);
  }
}

void TRandomDate::correctMonths(unsigned int& _ui_MinMonth, unsigned int& _ui_MaxMonth)
{
  TDateFunctions::correctMonth(_ui_MinMonth);
  TDateFunctions::correctMonth(_ui_MaxMonth);
  if(_ui_MinMonth > _ui_MaxMonth) {
    TNumeric::Swap(_ui_MinMonth, _ui_MaxMonth);
  }
}

void TRandomDate::correctDays(unsigned int& _ui_MinDay, unsigned int& _ui_MaxDay, unsigned int _ui_ForMonth, unsigned int _ui_ForYear)
{
  TDateFunctions::correctDay(_ui_MinDay, _ui_ForMonth, _ui_ForYear);
  TDateFunctions::correctDay(_ui_MaxDay, _ui_ForMonth, _ui_ForYear);
  if(_ui_MinDay > _ui_MaxDay) {
    TNumeric::Swap(_ui_MinDay, _ui_MaxDay);
  }
}

void TRandomDate::GetDate(DateHelper::sDateYear& _DateYear,
                          unsigned int _ui_MinYear, unsigned int _ui_MaxYear,
                          unsigned int _ui_MinMonth, unsigned int _ui_MaxMonth,
                          unsigned int _ui_MinDay, unsigned int _ui_MaxDay)
{
  GetDateYear(_DateYear.mui_year, _ui_MinYear, _ui_MaxYear);
  GetDateMonth(_DateYear.mui_month, _ui_MinMonth, _ui_MaxMonth);
  GetDateDay(_DateYear.mui_day, _DateYear.mui_month, _DateYear.mui_year, _ui_MinDay, _ui_MaxMonth);
  TDateFunctions::SetWeekDay(_DateYear);
}

void TRandomDate::GetDateYear(unsigned int& _ui_Year, unsigned int _ui_MinYear, unsigned int _ui_MaxYear)
{
  correctYears(_ui_MinYear, _ui_MaxYear);
  TNumeric::RandomIntOverIncRange(_ui_MinYear, _ui_MaxYear, &_ui_Year);
}

void TRandomDate::GetDateMonth(unsigned int& _ui_Month, unsigned int _ui_MinMonth, unsigned int _ui_MaxMonth)
{
  correctMonths(_ui_MinMonth, _ui_MaxMonth);
	TNumeric::RandomIntOverIncRange(_ui_MinMonth, _ui_MaxMonth, &_ui_Month);
}

void TRandomDate::GetDateDay(unsigned int& _ui_Day, unsigned int _ui_ForMonth, unsigned int _ui_ForYear, unsigned int _ui_MinDay, unsigned int _ui_MaxDay)
{
  correctDays(_ui_MinDay, _ui_MaxDay, _ui_ForMonth, _ui_ForYear);
  TNumeric::RandomIntOverIncRange(_ui_MinDay, _ui_MaxDay, &_ui_Day);
}

bool TRandomDate::CreateRandomDays(unsigned int& _ui_ExclusionDay, vector<unsigned int>& _ui_days, unsigned int _ui_numDays)
{
  bool b_ret = false;
  if(_ui_numDays<7) {
    vector<unsigned int> _ui_validDays;
    for(unsigned int i=MONDAY; i<=SUNDAY; ++i) {
     if(i!=_ui_ExclusionDay) {
       _ui_validDays.push_back(i);
     }
    }
    random_shuffle(_ui_validDays.begin(), _ui_validDays.end());
    for(unsigned int i=0; i<_ui_numDays; ++i) {
     _ui_days.push_back(_ui_validDays[i]);
    }
    b_ret = true;
  }
  return b_ret;
}


