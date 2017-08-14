
#include "SetupClass_General.h"
#include "TestClass_General.h"
#include "Questions.h"
#include "gtest/gtest.h"
#include "CommonHeader.h"

void TSetupClass_General::CheckNoQuestions(const char* _pc_FileName, int _i_Difficulty)
{
  TQuestionReaderWriter QuestionReaderWriter(_pc_FileName);
  if(_i_Difficulty > -1) {
    QuestionReaderWriter.SetDifficulty((unsigned int)_i_Difficulty);
  }
  ASSERT_EQ(TTestClass_General::CheckNoQuestions(QuestionReaderWriter),true);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfRadioQuestions(),0);
  ASSERT_EQ(QuestionReaderWriter.GetTotalNumberOfTextQuestions(),0);
}

void TSetupClass_General::WriteDiffToString(char* _pc_FileDiff, unsigned int _ui_FileDiff) 
{
  if(_ui_FileDiff == EASY) {
    strcpy_s(_pc_FileDiff,MAX_PATH,"EASY");
  }
  else if(_ui_FileDiff == MEDIUM) {
    strcpy_s(_pc_FileDiff,MAX_PATH,"MEDIUM");
  }
  else {
    strcpy_s(_pc_FileDiff,MAX_PATH,"HARD");
  }
}