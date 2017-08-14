//---------------------------------------------------------------------------

#ifndef DateHelperH
#define DateHelperH

#include <string>

namespace DateHelper
{

static const char* mp_MONDAY = "Monday";
static const char* mp_TUESDAY = "Tuesday";
static const char* mp_WEDNESDAY = "Wednesday";
static const char* mp_THURSDAY = "Thursday";
static const char* mp_FRIDAY = "Friday";
static const char* mp_SATURDAY = "Saturday";
static const char* mp_SUNDAY = "Sunday";

enum date {
  JANUARY = 1,
  FEBRUARY = 2,
  MARCH = 3,
  APRIL = 4,
  MAY = 5,
  JUNE = 6,
  JULY = 7,
  AUGUST = 8,
  SEPTEMBER = 9,
  OCTOBER = 10,
  NOVEMBER = 11,
  DECEMBER = 12
};
enum weekDay {
  MONDAY = 1,
  TUESDAY = 2,
  WEDNESDAY = 3,
  THURSDAY = 4,
  FRIDAY = 5,
  SATURDAY = 6,
  SUNDAY = 7
};

struct sDateYear {
  sDateYear() : mui_year(0), mui_month(0), mui_day(0), me_weekday(0) {}
  unsigned int mui_year;
  unsigned int mui_month;
  unsigned int mui_day;
  unsigned int me_weekday;
};

class TDateFunctions
{
  private:
    static void correctDatesForComparison(sDateYear& _startDate, sDateYear& _endDate);
    static void correctDate(sDateYear& _Date);
    static void correctYear(unsigned int& _ui_Year);
    static void correctMonth(unsigned int& _ui_Month);
    static void correctDay(unsigned int& _ui_Day, unsigned int _ui_ForMonth, unsigned int _ui_ForYear);
    static void correctWeekDay(unsigned int& _ui_Day);
    static int calculateDayNumber(const sDateYear& _Date);
    static unsigned int getNumberOfWholeDaysBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);
    static unsigned int getNumberOfDaysInclusiveBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);

  public:
    friend class TRandomDate;
    
    static bool IsSecondDateEarlierThanFirst(sDateYear& _1stDate, sDateYear& _2ndDate);
    static void SetWeekDay(sDateYear& _date);
    static bool IsWorkingWeekDay(unsigned int _ui_day);
    static void IncrementWeekDay(unsigned int& _ui_weekDay);
    static std::string GetStringForWeekDay(unsigned int _ui_weekDay);

    static unsigned int GetNumberOfDaysInMonth(unsigned int _ui_month, bool _b_isLeapYear);
    static unsigned int GetNumberOfDaysInMonth(unsigned int _ui_month, unsigned int _ui_year);

    static bool IsLeapYear(unsigned int _ui_year);

    static unsigned int GetNumberOfWholeDaysBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);
    static unsigned int GetNumberOfDaysInclusiveBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);

    static unsigned int GetNumberOfWholeWeeksBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate); 
    static unsigned int GetNumberOfWholeMonthsBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);
    static unsigned int GetNumberOfWholeYearsBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);

    static unsigned int GetNumberOfWholeWorkingDaysBetweenDates(sDateYear& _1stDate, sDateYear& _2ndDate);

};

};



#endif
