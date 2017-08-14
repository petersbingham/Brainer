//---------------------------------------------------------------------------
#pragma hdrstop

#include "DateHelper.h"
using namespace DateHelper;
using namespace std;


void TDateFunctions::correctDatesForComparison(sDateYear& _startDate, sDateYear& _endDate)
{
  if(IsSecondDateEarlierThanFirst(_startDate, _endDate)) {
    sDateYear copyDate;
    copyDate = _startDate;
    _startDate = _endDate;
    _endDate = copyDate;
  }
}

void TDateFunctions::correctDate(sDateYear& _Date)
{
  correctYear(_Date.mui_year);
  correctMonth(_Date.mui_month);
  correctDay(_Date.mui_day, _Date.mui_year, _Date.mui_month);
}

void TDateFunctions::correctYear(unsigned int& _ui_Year)
{
  /*if(_ui_Year < 1) {
    _ui_Year = 1;
  }*/
}

void TDateFunctions::correctMonth(unsigned int& _ui_Month)
{
  if(_ui_Month < 1) {
    _ui_Month = 1;
  }
  if(_ui_Month > 12) {
    _ui_Month = 12;
  }
}

void TDateFunctions::correctDay(unsigned int& _ui_Day, unsigned int _ui_ForMonth, unsigned int _ui_ForYear)
{
  if(_ui_Day < 1) {
    _ui_Day = 1;
  }
  else {
    if(_ui_Day > TDateFunctions::GetNumberOfDaysInMonth(_ui_ForMonth, _ui_ForYear)) {
      _ui_Day = TDateFunctions::GetNumberOfDaysInMonth(_ui_ForMonth, _ui_ForYear);
    }
  }
}

void TDateFunctions::correctWeekDay(unsigned int& _ui_Day)
{
  if(_ui_Day < 1) {
    _ui_Day = 1;
  }
  else if(_ui_Day > 7) {
    _ui_Day = 7;
  }
}

int TDateFunctions::calculateDayNumber(const sDateYear& _Date)
{
	int m = (_Date.mui_month + 9) % 12;
	int y = _Date.mui_year - m/10;
	return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( _Date.mui_day - 1 );
}

unsigned int TDateFunctions::getNumberOfWholeDaysBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  return calculateDayNumber(_2ndDate) - calculateDayNumber(_1stDate);
}

unsigned int TDateFunctions::getNumberOfDaysInclusiveBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  return calculateDayNumber(_2ndDate) - calculateDayNumber(_1stDate) + 1;
}

bool TDateFunctions::IsSecondDateEarlierThanFirst(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  correctDate(_1stDate);
  correctDate(_2ndDate);
  bool b_secondDateEarlierThanFirst = false;
  if(_2ndDate.mui_year < _1stDate.mui_year) {
    b_secondDateEarlierThanFirst = true;
  }
  else if(_2ndDate.mui_year == _1stDate.mui_year) {
    if(_2ndDate.mui_month < _1stDate.mui_month) {
      b_secondDateEarlierThanFirst = true;
    }
    else if(_2ndDate.mui_month == _1stDate.mui_month) {
      if(_2ndDate.mui_day < _1stDate.mui_day) {
        b_secondDateEarlierThanFirst = true;
      }
    }
  }
  return b_secondDateEarlierThanFirst;
}

bool TDateFunctions::IsWorkingWeekDay(unsigned int _ui_day)
{
  bool b_weekDay = true;
  if(_ui_day==SATURDAY || _ui_day==SUNDAY) {
    b_weekDay = false;
  }
  return b_weekDay;
}

void TDateFunctions::IncrementWeekDay(unsigned int& _ui_weekDay)
{
  if(_ui_weekDay>SATURDAY) {
    _ui_weekDay = MONDAY;
  }
  else {
    ++_ui_weekDay;
  }
}

void TDateFunctions::SetWeekDay(sDateYear& _date)
{
  correctDate(_date);
  int month = _date.mui_month;
  int day = _date.mui_day;
  int year = _date.mui_year;

  int ix, tx, vx;
  switch (month) {
    case FEBRUARY   :
    case JUNE       : vx = 0; break;
    case AUGUST     : vx = 4; break;
    case OCTOBER    : vx = 8; break;
    case SEPTEMBER  :
    case DECEMBER   : vx = 12; break;
    case MARCH      :
    case NOVEMBER   : vx = 16; break;
    case JANUARY    :
    case MAY        : vx = 20; break;
    case APRIL      :
    case JULY       : vx = 24; break;
  }
  if (year > 1900)  // 1900 was not a leap year
    year -= 1900;
  ix = ((year - 21) % 28) + vx + (month > 2);  // take care of February 
  tx = (ix + (ix / 4)) % 7 + day;              // take care of leap year
  switch(tx % 7)
  {
    case 0:
           _date.me_weekday = MONDAY;
           break;
    case 1:
           _date.me_weekday = TUESDAY;
           break;
    case 2:
           _date.me_weekday = WEDNESDAY;
           break;
    case 3:
           _date.me_weekday = THURSDAY;
           break;
    case 4:
           _date.me_weekday = FRIDAY;
           break;
    case 5:
           _date.me_weekday = SATURDAY;
           break;
    case 6:
           _date.me_weekday = SUNDAY;
           break;
  }
}

unsigned int TDateFunctions::GetNumberOfDaysInMonth(unsigned int _ui_month, bool _b_isLeapYear)
{
  correctMonth(_ui_month);

  unsigned int ui_noDays;

  switch(_ui_month) {
    case  JANUARY:
    case  MARCH:
    case  MAY:
    case  JULY:
    case  AUGUST:
    case  OCTOBER:
    case  DECEMBER:
            ui_noDays = 31;
            break;

    case  SEPTEMBER:
    case  APRIL:
    case  JUNE:
    case  NOVEMBER:
            ui_noDays = 30;
            break;

    case  FEBRUARY:
            int iDays;
            if(_b_isLeapYear) {
              ui_noDays = 29;
            }
            else {
              ui_noDays = 28;
            }
            break;
  }
  return ui_noDays;
}

unsigned int TDateFunctions::GetNumberOfDaysInMonth(unsigned int _ui_month, unsigned int _ui_year)
{
  return GetNumberOfDaysInMonth(_ui_month, IsLeapYear(_ui_year));
}

bool TDateFunctions::IsLeapYear(unsigned int _ui_year)
{
  correctYear(_ui_year);

	bool b_LeapYear;
	if( _ui_year%4==0 && (_ui_year%100!=0 || _ui_year%400==0) ) {
		b_LeapYear = true;
	}
	else {
		b_LeapYear = false;
	}
	return b_LeapYear;
}

string TDateFunctions::GetStringForWeekDay(unsigned int _ui_weekDay)
{
  correctWeekDay(_ui_weekDay);

  string dayString;
  switch(_ui_weekDay) {
    case  MONDAY:
            dayString = mp_MONDAY;
            break;
    case  TUESDAY:
            dayString = mp_TUESDAY;
            break;
    case  WEDNESDAY:
            dayString = mp_WEDNESDAY;
            break;
    case  THURSDAY:
            dayString = mp_THURSDAY;
            break;
    case  FRIDAY:
            dayString = mp_FRIDAY;
            break;
    case  SATURDAY:
            dayString = mp_SATURDAY;
            break;
    case  SUNDAY:
            dayString = mp_SUNDAY;
            break;

  }
  return dayString;
}

unsigned int TDateFunctions::GetNumberOfWholeDaysBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  correctDatesForComparison(_1stDate, _2ndDate);

  return getNumberOfWholeDaysBetweenDates(_1stDate, _2ndDate);
}

unsigned int TDateFunctions::GetNumberOfDaysInclusiveBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  correctDatesForComparison(_1stDate, _2ndDate);

  return getNumberOfDaysInclusiveBetweenDates(_1stDate, _2ndDate);
}

unsigned int TDateFunctions::GetNumberOfWholeWeeksBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{    
  correctDatesForComparison(_1stDate, _2ndDate);

  return GetNumberOfWholeDaysBetweenDates(_1stDate, _2ndDate) / 7;
}

unsigned int TDateFunctions::GetNumberOfWholeMonthsBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  correctDatesForComparison(_1stDate, _2ndDate);

  unsigned int ui_months;
	ui_months = 12*(_2ndDate.mui_year - _1stDate.mui_year - 1)
									+ 12-_1stDate.mui_month + _2ndDate.mui_month-1;
	if(_1stDate.mui_day <= _2ndDate.mui_day) {
		ui_months++;
	}
  return ui_months;
}

unsigned int TDateFunctions::GetNumberOfWholeYearsBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  correctDatesForComparison(_1stDate, _2ndDate);

  unsigned int ui_years;
	ui_years = _2ndDate.mui_year - _1stDate.mui_year - 1;

	if(_2ndDate.mui_month > _1stDate.mui_month) {
		ui_years++;
	}
	else if(_2ndDate.mui_month == _1stDate.mui_month) {
		if(_2ndDate.mui_day >= _1stDate.mui_day) {
			ui_years++;
    }
  }
  return ui_years;
}

unsigned int TDateFunctions::GetNumberOfWholeWorkingDaysBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate)
{
  unsigned int ui_days = 0;
  correctDatesForComparison(_1stDate, _2ndDate);
  SetWeekDay(_1stDate);

  unsigned int ui_weekDay = _1stDate.me_weekday;
  for(unsigned int i=0; i<getNumberOfDaysInclusiveBetweenDates(_1stDate, _2ndDate); ++i) {
    if(IsWorkingWeekDay(ui_weekDay)) {
      ++ui_days;
    }
    IncrementWeekDay(ui_weekDay);
  }
  return ui_days;
}
