//---------------------------------------------------------------------------

#ifndef RandomDateH
#define RandomDateH

#include "DateHelper.h"  
#include <vector>

namespace DateHelper
{

class TRandomDate
{
  private:
    static void correctYears(unsigned int& _ui_MinYear, unsigned int& _ui_MaxYear);
    static void correctMonths(unsigned int& _ui_MinMonth, unsigned int& _ui_MaxMonth);
    static void correctDays(unsigned int& _ui_MinDay, unsigned int& _ui_MaxDay, unsigned int _ui_ForMonth, unsigned int _ui_ForYear);

  public:
    static void GetDate(DateHelper::sDateYear& _DateYear,
                        unsigned int _ui_MinYear, unsigned int _ui_MaxYear,
                        unsigned int _ui_MinMonth=DateHelper::JANUARY, unsigned int _ui_MaxMonth=DateHelper::DECEMBER,
                        unsigned int _ui_MinDay=1, unsigned int _ui_MaxDay=31);

    static void GetDateYear(unsigned int& _ui_Year, unsigned int _ui_MinYear, unsigned int _ui_MaxYear);
    static void GetDateMonth(unsigned int& _ui_Month, unsigned int _ui_MinMonth=DateHelper::JANUARY, unsigned int _ui_MaxMonth=DateHelper::DECEMBER);
    static void GetDateDay(unsigned int& _ui_Day, unsigned int _ui_ForMonth, unsigned int _ui_ForYear, unsigned int _ui_MinDay=1, unsigned int _ui_MaxDay=31);

    static bool CreateRandomDays(unsigned int& _ui_ExcludingDay, std::vector<unsigned int>& _ui_days, unsigned int _ui_numDays);
};

};

#endif
