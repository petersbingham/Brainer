//---------------------------------------------------------------------------

#ifndef SetupClass_DUMMYH
#define SetupClass_DUMMYH

#include "TestClass_General.h"


class TSetupClass_DUMMY
{
private:
  static void totalRoundCycleTests_Text(const char* _pc_FileName, const TSetupInfo& _SetupInfo);
  static void totalRoundCycleTests_Radio(const char* _pc_FileName, const TSetupInfo& _SetupInfo);

  static void singleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_NoQuestions, unsigned int _ui_NoDummyQuestions, unsigned int _ui_SetDiff);

public:
  static void SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff);
};


#endif