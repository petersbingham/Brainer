//---------------------------------------------------------------------------

#ifndef SetupClass_NOQUESTIONSH
#define SetupClass_NOQUESTIONSH

#include "TestClass_General.h"


class TSetupClass_NOQUESTIONS
{
public:
  static void EmptyFile();
  static void SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff);
  static void DoubleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_SetDiff);
};


#endif