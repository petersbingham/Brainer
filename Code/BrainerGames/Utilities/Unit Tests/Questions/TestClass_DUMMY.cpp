
#include "TestClass_DUMMY.h"
#include "TestClass_General.h"
#include "CommonHeader.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
using namespace std;

bool TTestClass_DUMMY::checkNoDummy(const std::string& _Answer, const std::string& _Question)
{
  bool b_ret = true;
  if(_Answer.find("Dummy") != string::npos) {
    b_ret = false; 
  }
  else if(_Question.find("Dummy") != string::npos) {
    b_ret = false; 
  }
  return b_ret;
}

void TTestClass_DUMMY::sequentialQuestionTests(unsigned int _ui_TestType,
                                                        const string& _Answer,
                                                        const string& _Question, 
                                                        vector<string>& _Answers,
                                                        vector<string>& _Questions,
                                                        const TSetupInfo& _SetupInfo,
                                                        unsigned int _ui_QuestionNumber)
{
  ASSERT_EQ(TTestClass_General::CheckNewQuestionAndPush(_ui_TestType, _Answers, _Questions, _Answer, _Question, _SetupInfo, _ui_QuestionNumber), true);
  ASSERT_EQ(TTestClass_General::CheckAnsQueCorrespondence(_Answer, _Question), true);
  ASSERT_EQ(checkNoDummy(_Answer, _Question), true);
  ASSERT_EQ(TTestClass_General::CheckCorrectDiffInString(_Answer, _SetupInfo), true);
  ASSERT_EQ(TTestClass_General::CheckCorrectDiffInString(_Question, _SetupInfo), true);
}

void TTestClass_DUMMY::sequentialQuestionTests(unsigned int _ui_TestType,
                                                        const string& _Answer,
                                                        const string& _Question, 
                                                        vector<string>& _Answers,
                                                        vector<string>& _Questions,
                                                        vector<string>& _WrongAnswers,
                                                        const TSetupInfo& _SetupInfo,
                                                        unsigned int _ui_QuestionNumber)
{
  sequentialQuestionTests(_ui_TestType, _Answer, _Question, _Answers, _Questions, _SetupInfo, _ui_QuestionNumber);
  ASSERT_EQ(TTestClass_General::CheckWrongAnswersAndClear(_Answer, _WrongAnswers), true);
}

void TTestClass_DUMMY::TotalRoundCycleTests_Text(TQuestionReaderWriter& _QuestionReaderWriter, const TSetupInfo& _SetupInfo)
{
  string Question;
  string Answer; 
  set<string> Answers;
  set<string> Questions;
  unsigned int ui_Diff;

  unsigned int ui_CntTotalQue = 0;
  if(TTestClass_General::GetTotalNumberQuestions(_SetupInfo) > 0) {
    while(ui_CntTotalQue<uiNoRounds) {
      unsigned int ui_CntPartQue = 0;
      while(ui_CntPartQue<TTestClass_General::GetTotalNumberQuestions(_SetupInfo) && ui_CntTotalQue<uiNoRounds) {
        vector<string> Answers2;
        vector<string> Questions2;
        bool b_ret = _QuestionReaderWriter.GetNextQuestion(Question, Answer, ui_Diff);
        ASSERT_EQ(b_ret, true);
        sequentialQuestionTests(TTestClass_General::SINGLETYPE, Answer, Question, Answers2, Questions2, _SetupInfo, ui_CntTotalQue);
        TTestClass_General::Increment(ui_CntTotalQue, ui_CntPartQue, Answers, Questions, Answer, Question);
      }
      TTestClass_General::UniqueQueAnsTest(TTestClass_General::SINGLETYPE, Answers, Questions, _SetupInfo, false, ui_CntTotalQue);
    }
  }
  else {
    ASSERT_EQ(TTestClass_General::CheckNoQuestions(_QuestionReaderWriter),true);
  }
}

void TTestClass_DUMMY::TotalRoundCycleTests_Radio(TQuestionReaderWriter& _QuestionReaderWriter, const TSetupInfo& _SetupInfo)
{
  string Question;
  string Answer; 
  vector<string> WrongAnswers;
  set<string> Answers;
  set<string> Questions;
  unsigned int ui_Diff;

  unsigned int ui_CntTotalQue = 0;
  if(TTestClass_General::GetTotalNumberRadioQuestions(_SetupInfo) > 0) {
    while(ui_CntTotalQue<uiNoRounds) {
      unsigned int ui_CntPartQue = 0;
      while(ui_CntPartQue<TTestClass_General::GetTotalNumberRadioQuestions(_SetupInfo) && ui_CntTotalQue<uiNoRounds) {
        vector<string> Answers2;
        vector<string> Questions2;
        bool b_ret = _QuestionReaderWriter.GetNextQuestionRadio(Question, Answer, WrongAnswers, ui_Diff);
        ASSERT_EQ(b_ret, true); 
        sequentialQuestionTests(TTestClass_General::SINGLETYPE, Answer, Question, Answers2, Questions2, WrongAnswers, _SetupInfo, ui_CntTotalQue);
        TTestClass_General::Increment(ui_CntTotalQue, ui_CntPartQue, Answers, Questions, Answer, Question);
      }
      TTestClass_General::UniqueQueAnsTest(TTestClass_General::SINGLETYPE, Answers, Questions, _SetupInfo, true, ui_CntTotalQue);
    }
  }
  else {
    ASSERT_EQ(TTestClass_General::CheckNoQuestions(_QuestionReaderWriter, true),true);
  }
}
