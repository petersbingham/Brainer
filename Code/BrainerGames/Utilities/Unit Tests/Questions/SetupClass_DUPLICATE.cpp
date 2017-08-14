
#include "SetupClass_DUPLICATE.h"
#include "TestClass_DUPLICATE.h"
#include "SetupClass_General.h"
#include "Questions.h"
#include "CommonHeader.h"
#include "gtest/gtest.h"

#define TESTLOOPS 5
using namespace std;

void TSetupClass_DUPLICATE::totalRoundCycleTests_Text(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_DUPLICATE::TotalRoundCycleTests_Text(QuestionReaderWriter, _SetupInfo);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfTextQuestions(),TTestClass_General::GetTotalNumberQuestions(_SetupInfo));
}

void TSetupClass_DUPLICATE::totalRoundCycleTests_Radio(const char* _pc_FileName, const TSetupInfo& _SetupInfo)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  QuestionReaderWriter.SetDifficulty(_SetupInfo.mui_SetDifficulty);
  TTestClass_DUPLICATE::TotalRoundCycleTests_Radio(QuestionReaderWriter, _SetupInfo);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfRadioQuestions(),TTestClass_General::GetTotalNumberRadioQuestions(_SetupInfo));
}

void TSetupClass_DUPLICATE::createDuplicatesString(const vector<unsigned int>& _Duplicates, 
                                                   char* _pc_String)
{
  _pc_String[0] = 0;
  for(int i=0; i<_Duplicates.size(); ++i) {
    if(i == _Duplicates.size()-1) {
      sprintf(_pc_String,"%s%d", _pc_String, _Duplicates[i]);
    }
    else {
      sprintf(_pc_String,"%s%d-", _pc_String, _Duplicates[i]);
    }
  }
}

void TSetupClass_DUPLICATE::singleSectionTests(unsigned int _ui_FileDiff, 
                                               unsigned int _ui_NoQuestions, 
                                               unsigned int _ui_SetDiff,
                                               const vector<unsigned int>& _Duplicates)
{
  char pc_FileDiff[MAX_PATH];
  TSetupClass_General::WriteDiffToString(pc_FileDiff, _ui_FileDiff);
  char pc_NoDuplicatesString[MAX_PATH];
  pc_NoDuplicatesString[0] = 0;
  createDuplicatesString(_Duplicates, pc_NoDuplicatesString);
  char pc_FileName[MAX_PATH];   
  sprintf_s(pc_FileName,MAX_PATH, "DUPLICATE_1Section%s_%dQuestion_%sDuplicate", pc_FileDiff, _ui_NoQuestions, pc_NoDuplicatesString); 

  TSetupInfo SetupInfo;
  SetupInfo.mui_SetDifficulty = _ui_SetDiff;
  SetupInfo.m_Section.push_back(TFileSectionInfo(_ui_NoQuestions,_Duplicates,_ui_FileDiff));
  totalRoundCycleTests_Text(pc_FileName, SetupInfo);
  totalRoundCycleTests_Radio(pc_FileName, SetupInfo);
}

void TSetupClass_DUPLICATE::SingleSectionTests(unsigned int _ui_FileDiff, unsigned int _ui_SetDiff)
{
  vector<unsigned int> _Duplicates;
  _Duplicates.push_back(3);
  _Duplicates.push_back(2);
  singleSectionTests(_ui_FileDiff, 10, _ui_SetDiff, _Duplicates);
  _Duplicates.push_back(2);
  singleSectionTests(_ui_FileDiff, 10, _ui_SetDiff, _Duplicates);
  _Duplicates[2] = 3;
  singleSectionTests(_ui_FileDiff, 10, _ui_SetDiff, _Duplicates);
  _Duplicates[1] = 3;
  singleSectionTests(_ui_FileDiff, 10, _ui_SetDiff, _Duplicates);
}
