//---------------------------------------------------------------------------

#ifndef SetupClass_DUPLICATEH
#define SetupClass_DUPLICATEH

#include "TestClass_General.h"


class TSetupClass_DUPLICATE
{
private:
  static void totalRoundCycleTests_Text(const char* _pc_FileName, const TSetupInfo& _SetupInfo);
  static void totalRoundCycleTests_Radio(const char* _pc_FileName, const TSetupInfo& _SetupInfo);

  static void createDuplicatesString(const std::vector<unsigned int>& _Duplicates, char* _pc_String);
  static void singleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_NoQuestions, unsigned int _ui_SetDiff, const std::vector<unsigned int>& _Duplicates);

public:
  static void SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff);
};


#endif