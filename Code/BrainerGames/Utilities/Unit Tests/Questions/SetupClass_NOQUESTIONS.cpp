
#include "SetupClass_NOQUESTIONS.h"
#include "SetupClass_General.h"
#include "Questions.h"
#include "CommonHeader.h"

void TSetupClass_NOQUESTIONS::EmptyFile()
{
  TSetupClass_General::CheckNoQuestions("NOQUESTIONS_EMPTY");
}

void TSetupClass_NOQUESTIONS::SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff)
{
  char pc_FileDiff[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff, _ui_FileDiff);
  char pc_FileName[MAX_PATH];  
  sprintf_s(pc_FileName,MAX_PATH, "NOQUESTIONS_1Section%s", pc_FileDiff);

  TSetupClass_General::CheckNoQuestions(pc_FileName, _ui_SetDiff);
}

void TSetupClass_NOQUESTIONS::DoubleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_SetDiff)
{
  char pc_FileDiff1[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff1, _ui_FileDiff1);
  char pc_FileDiff2[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff2, _ui_FileDiff2);

  char pc_FileName[MAX_PATH];  
  sprintf_s(pc_FileName,MAX_PATH, "NOQUESTIONS_2Section%s%s", pc_FileDiff1, pc_FileDiff2);

  TSetupClass_General::CheckNoQuestions(pc_FileName, _ui_SetDiff);
}
