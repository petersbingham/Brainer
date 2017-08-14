
#include "SetupClass_UNIQUE.h"
#include "TestClass_UNIQUE.h"
#include "SetupClass_General.h"
#include "Questions.h"
#include "CommonHeader.h"
#include "gtest/gtest.h"

#define TESTLOOPS 5
using namespace std;

void TSetupClass_UNIQUE::totalRoundCycleTests_Mix(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_UNIQUE::TotalRoundCycleTests_Mix(QuestionReaderWriter, _SetupInfo);
}

void TSetupClass_UNIQUE::totalRoundCycleTests_Text(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_UNIQUE::TotalRoundCycleTests_Text(QuestionReaderWriter, _SetupInfo);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfTextQuestions(),TTestClass_General::GetTotalNumberQuestions(_SetupInfo));
}

void TSetupClass_UNIQUE::totalRoundCycleTests_Radio(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_UNIQUE::TotalRoundCycleTests_Radio(QuestionReaderWriter, _SetupInfo);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfRadioQuestions(),TTestClass_General::GetTotalNumberRadioQuestions(_SetupInfo));
}

void TSetupClass_UNIQUE::singleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_NoQuestions, unsigned int _ui_SetDiff)
{
  char pc_FileDiff[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff, _ui_FileDiff);
  char pc_FileName[MAX_PATH];
  sprintf_s(pc_FileName,MAX_PATH, "UNIQUE_1Section%s_%dQuestion", pc_FileDiff, _ui_NoQuestions);

  TSetupInfo SetupInfo;
  SetupInfo.mui_SetDifficulty = _ui_SetDiff;
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions,_ui_FileDiff));
  totalRoundCycleTests_Mix(pc_FileName, SetupInfo);
  totalRoundCycleTests_Text(pc_FileName, SetupInfo);
  totalRoundCycleTests_Radio(pc_FileName, SetupInfo);
}

void TSetupClass_UNIQUE::doubleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, 
                                            unsigned int _ui_NoQuestions1, unsigned int _ui_NoQuestions2, unsigned int _ui_SetDiff)
{
  char pc_FileDiff1[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff1, _ui_FileDiff1);
  char pc_FileDiff2[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff2, _ui_FileDiff2);

  char pc_FileName[MAX_PATH];  
  sprintf_s(pc_FileName,MAX_PATH, "UNIQUE_2Section%s%s_%d_%dQuestion", pc_FileDiff1, pc_FileDiff2, _ui_NoQuestions1, _ui_NoQuestions2);

  TSetupInfo SetupInfo;
  SetupInfo.mui_SetDifficulty = _ui_SetDiff;
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions1,_ui_FileDiff1));
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions2,_ui_FileDiff2));
  for(int i=0; i<TESTLOOPS; ++i) { //Questions are randomly pulled from group. The questions are not completely determinate.
    totalRoundCycleTests_Mix(pc_FileName, SetupInfo);
  }
  totalRoundCycleTests_Text(pc_FileName, SetupInfo);
  totalRoundCycleTests_Radio(pc_FileName, SetupInfo);
}

void TSetupClass_UNIQUE::tripleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_FileDiff3, 
                                            unsigned int _ui_NoQuestions1, unsigned int _ui_NoQuestions2, unsigned int _ui_NoQuestions3, unsigned int _ui_SetDiff)
{
  char pc_FileDiff1[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff1, _ui_FileDiff1);
  char pc_FileDiff2[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff2, _ui_FileDiff2);
  char pc_FileDiff3[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff3, _ui_FileDiff3);

  char pc_FileName[MAX_PATH];  
  sprintf_s(pc_FileName,MAX_PATH, "UNIQUE_3Section%s%s%s_%d_%d_%dQuestion", pc_FileDiff1, pc_FileDiff2, pc_FileDiff3, _ui_NoQuestions1, _ui_NoQuestions2, _ui_NoQuestions3);

  TSetupInfo SetupInfo;
  SetupInfo.mui_SetDifficulty = _ui_SetDiff;
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions1,_ui_FileDiff1));
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions2,_ui_FileDiff2));
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions3,_ui_FileDiff3));
  for(int i=0; i<TESTLOOPS; ++i) { //Questions are randomly pulled from group. The questions are not completely determinate.
    totalRoundCycleTests_Mix(pc_FileName, SetupInfo);
  }
  totalRoundCycleTests_Text(pc_FileName, SetupInfo);
  totalRoundCycleTests_Radio(pc_FileName, SetupInfo);
}

void TSetupClass_UNIQUE::SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff)
{
  singleSectionTests(_ui_FileDiff, 1, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 2, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 3, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 4, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 5, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 6, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 9, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 10, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 11, _ui_SetDiff);
}

void TSetupClass_UNIQUE::DoubleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_SetDiff)
{
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 0, 3, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 0, 5, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 1, 5, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 3, 1, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 3, 10, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 4, 3, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 4, 5, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 5, 0, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 5, 1, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 5, 4, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 5, 5, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 5, 10, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 6, 3, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 6, 5, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 10, 3, _ui_SetDiff);
  doubleSectionTests(_ui_FileDiff1, _ui_FileDiff2, 10, 5, _ui_SetDiff);
}

void TSetupClass_UNIQUE::TripleSectionTests(unsigned int _ui_FileDiff1, unsigned int _ui_FileDiff2, unsigned int _ui_FileDiff3, unsigned int _ui_SetDiff)
{
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 4, 5, 10, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 4, 10, 5, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 5, 4, 10, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 5, 10, 4, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 10, 4, 5, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 10, 5, 4, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 1, 2, 5, _ui_SetDiff);
  tripleSectionTests(_ui_FileDiff1, _ui_FileDiff2, _ui_FileDiff3, 1, 2, 1, _ui_SetDiff);
}