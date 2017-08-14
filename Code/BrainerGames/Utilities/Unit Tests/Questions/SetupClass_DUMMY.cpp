
#include "SetupClass_DUMMY.h"
#include "TestClass_DUMMY.h"
#include "SetupClass_General.h"
#include "TestClass_General.h"
#include "Questions.h"
#include "CommonHeader.h"
#include "gtest/gtest.h"

#define TESTLOOPS 5
using namespace std;

void TSetupClass_DUMMY::totalRoundCycleTests_Text(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_DUMMY::TotalRoundCycleTests_Text(QuestionReaderWriter, _SetupInfo);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfTextQuestions(),TTestClass_General::GetTotalNumberQuestions(_SetupInfo));
}

void TSetupClass_DUMMY::totalRoundCycleTests_Radio(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_DUMMY::TotalRoundCycleTests_Radio(QuestionReaderWriter, _SetupInfo);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfRadioQuestions(),TTestClass_General::GetTotalNumberRadioQuestions(_SetupInfo));
}

void TSetupClass_DUMMY::singleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_NoQuestions, unsigned int _ui_NoDummyQuestions, unsigned int _ui_SetDiff)
{
  char pc_FileDiff[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff, _ui_FileDiff);
  char pc_FileName[MAX_PATH];
  sprintf_s(pc_FileName,MAX_PATH, "DUMMY_1Section%s_%dQuestion_%dDummy", pc_FileDiff, _ui_NoQuestions, _ui_NoDummyQuestions); 

  TSetupInfo SetupInfo;
  SetupInfo.mui_SetDifficulty = _ui_SetDiff;
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions,_ui_NoDummyQuestions,_ui_FileDiff));
  totalRoundCycleTests_Text(pc_FileName, SetupInfo);
  totalRoundCycleTests_Radio(pc_FileName, SetupInfo);
}

void TSetupClass_DUMMY::SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff)
{
  singleSectionTests(_ui_FileDiff, 1, 1, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 2, 1, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 5, 1, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 5, 4, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 6, 1, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 6, 2, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 10, 1, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 10, 5, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 10, 6, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 10, 10, _ui_SetDiff);
  singleSectionTests(_ui_FileDiff, 11, 1, _ui_SetDiff);
}
