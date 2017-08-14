//---------------------------------------------------------------------------

#ifndef SetupClass_UNIQUEH
#define SetupClass_UNIQUEH

#include "TestClass_General.h"


class TSetupClass_UNIQUE
{
private:
  static void totalRoundCycleTests_Mix(const char* _pc_FileName, const TSetupInfo& _SetupInfo);
  static void totalRoundCycleTests_Text(const char* _pc_FileName, const TSetupInfo& _SetupInfo);
  static void totalRoundCycleTests_Radio(const char* _pc_FileName, const TSetupInfo& _SetupInfo);

  static void singleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_NoQuestions, unsigned int _ui_SetDiff);
  static void doubleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, 
                                 unsigned int _ui_NoQuestions1, unsigned int _ui_NoQuestions2, unsigned int _ui_SetDiff);
  static void tripleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_FileDiff3, 
                                 unsigned int _ui_NoQuestions1, unsigned int _ui_NoQuestions2, unsigned int _ui_NoQuestions3, unsigned int _ui_SetDiff);

public:
  static void SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff);
  static void DoubleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_SetDiff);
  static void TripleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_FileDiff3, unsigned int _ui_SetDiff);
};


#endif