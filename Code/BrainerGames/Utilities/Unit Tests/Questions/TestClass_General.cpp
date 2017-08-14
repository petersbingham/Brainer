
#include "TestClass_General.h"
#include "CommonHeader.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
using namespace std;

unsigned int TTestClass_General::vectorSum(const vector<unsigned int>& _Duplicates)
{
  unsigned int ui_Sum = 0;
  for(unsigned int i=0; i<_Duplicates.size(); ++i) {
    ui_Sum += _Duplicates[i];
  }
  return ui_Sum;
}

unsigned int TTestClass_General::getNumberUniqueAnswers(unsigned int _ui_NumberSectionQuestions, const vector<unsigned int>& _Duplicates)
{
  return _ui_NumberSectionQuestions - vectorSum(_Duplicates) + _Duplicates.size();  
}

int TTestClass_General::getStringPos(const string& _SearchString, const string& _FindString) 
{
  int i_Pos = _SearchString.find(_FindString);
  if(i_Pos != string::npos) {
    i_Pos += _FindString.length();  
  }
  else {
    i_Pos = -1;
  }
  return i_Pos;
}

int TTestClass_General::getNumberFromString(const string& _String, int _i_StartPosition)
{
  int i_ret = -1;
  if(_i_StartPosition > -1) {
    string Number;
    for(int i=_i_StartPosition; i<_String.length() && _i_StartPosition+2; ++i) {
      if(isdigit(_String[i])) {
        Number += _String[i];
      }
      else {
        break;
      }
    }
    if(Number.length()>0) {
      i_ret = atoi(Number.c_str());
    }
  }
  return i_ret;
}

int TTestClass_General::getQueAnsNumber(const string& _String, bool _b_Answer)
{ 
  int i_Pos;
  if(_b_Answer) {
    i_Pos = getStringPos(_String, "Answer");  
  }
  else {
    i_Pos = getStringPos(_String, "Question");  
  }
  return getNumberFromString(_String, i_Pos);
}

int TTestClass_General::getSectionNumber(const string& _String)
{ 
  int i_Pos = getStringPos(_String, "EASY");  
  if(i_Pos < 0) {
    i_Pos = getStringPos(_String, "MEDIUM");  
    if(i_Pos < 0) {
      i_Pos = getStringPos(_String, "HARD");  
    }
  }
  return getNumberFromString(_String, i_Pos);
}

bool TTestClass_General::checkValidStringDiff(const TSetupInfo& _SetupInfo, unsigned int _ui_Diff)
{
  bool b_ret = true;
  if(HighestFileDifficulty(_SetupInfo) < _ui_Diff) {
    b_ret = false;
  }
  else if(_SetupInfo.mui_SetDifficulty < _ui_Diff) {
    b_ret = false;
  }  
  return b_ret;
}

bool TTestClass_General::areAllValidSectionsGreaterOrLessThanRadio(const TSetupInfo& _SetupInfo)
{
  bool b_GreaterThan = true;
  bool b_LessThan = true;
  for(vector<TFileSectionInfo>::const_iterator it=_SetupInfo.m_Section.begin(); it!=_SetupInfo.m_Section.end() && (b_GreaterThan||b_LessThan); ++it) {
    if(it->mui_Difficulty <= _SetupInfo.mui_SetDifficulty) {
      if(it->mui_NumberQuestions - it->mui_NumberDummyQuestions < uiNoRadioOptions) {
        b_GreaterThan = false;
      }
      else if(it->mui_NumberQuestions - it->mui_NumberDummyQuestions >= uiNoRadioOptions) {
        b_LessThan = false;
      }
    }
  }
  return b_GreaterThan || b_LessThan;
}

unsigned int TTestClass_General::getNumberAnswers(const std::set<std::string>& _Questions)
{
  set<pair<unsigned int, unsigned int> > QuestionNumbers;
  for(set<std::string>::const_iterator it = _Questions.begin(); it!=_Questions.end(); ++it) {
    QuestionNumbers.insert(pair<unsigned int, unsigned int>(getSectionNumber(*it), getQueAnsNumber(*it, false)));
  }
  return QuestionNumbers.size();
}

unsigned int TTestClass_General::GetTotalNumberRadioQuestions(const TSetupInfo& _SetupInfo)
{
  unsigned int ui_NumberRadioQuestions = 0;
  for(vector<TFileSectionInfo>::const_iterator it=_SetupInfo.m_Section.begin(); it!=_SetupInfo.m_Section.end(); ++it) {
    if(_SetupInfo.mui_SetDifficulty>=it->mui_Difficulty && getNumberUniqueAnswers(it->mui_NumberQuestions,it->m_DuplicateQuestions)>=uiNoRadioOptions) {
      ui_NumberRadioQuestions += it->mui_NumberQuestions - it->mui_NumberDummyQuestions;
    }
  }
  return ui_NumberRadioQuestions;
}

unsigned int TTestClass_General::GetTotalNumberQuestions(const TSetupInfo& _SetupInfo)
{
  unsigned int ui_TotalNumberQuestions = 0;
  for(vector<TFileSectionInfo>::const_iterator it=_SetupInfo.m_Section.begin(); it!=_SetupInfo.m_Section.end(); ++it) {
    if(_SetupInfo.mui_SetDifficulty>=it->mui_Difficulty) {
      ui_TotalNumberQuestions += it->mui_NumberQuestions - it->mui_NumberDummyQuestions;
    }
  }
  return ui_TotalNumberQuestions;
}

void TTestClass_General::Increment( unsigned int& _ui_CntTotalQue, 
                                    unsigned int& _ui_CntPartQue, 
                                    set<string>& _Answers,
                                    set<string>& _Questions,
                                    const string& _Answer,
                                    const string& _Question)
{
  ++_ui_CntTotalQue;
  ++_ui_CntPartQue;
  _Questions.insert(_Question);
  _Answers.insert(_Answer);
}

bool TTestClass_General::CheckAnsQueCorrespondence( const string& _Answer,
                                const string& _Question)
{
  int i_Ans = getQueAnsNumber(_Answer, true);
  int i_Que = getQueAnsNumber(_Question, false);
  return i_Ans>0 && i_Ans==i_Que;
}

unsigned int TTestClass_General::HighestFileDifficulty(const TSetupInfo& _SetupInfo)
{
  unsigned int ui_Difficulty = EASY;
  for(unsigned int i=0; i<_SetupInfo.m_Section.size(); ++i) {
    if(_SetupInfo.m_Section[i].mui_Difficulty > ui_Difficulty) {
      ui_Difficulty = _SetupInfo.m_Section[i].mui_Difficulty;
    }
  }
  return ui_Difficulty;
}

bool TTestClass_General::CheckCorrectDiffInString(const string& _String, 
                                                         const TSetupInfo& _SetupInfo)
{
  bool b_ret = true;
  int i_Pos = _String.find("HARD");
  if(i_Pos != string::npos) {
    b_ret = checkValidStringDiff(_SetupInfo, HARD);
  }
  else {
    i_Pos = _String.find("MEDIUM");
    if(i_Pos != string::npos) {
      b_ret = checkValidStringDiff(_SetupInfo, MEDIUM);
    }
    else {
      i_Pos = _String.find("EASY");
      if(i_Pos != string::npos) {
        b_ret = checkValidStringDiff(_SetupInfo, EASY);
      }
      else {
        b_ret = false;
      }
    }
  }
  return b_ret;
}

bool TTestClass_General::CheckWrongAnswersAndClear(const string& _Answer, vector<string>& _WrongAnswers)
{
  bool b_ret = true;
  if(_WrongAnswers.size() != uiNoRadioOptions-1) {
    b_ret = false;
  }
  else if(set<string>(_WrongAnswers.begin(), _WrongAnswers.end()).size() != uiNoRadioOptions-1) {
    b_ret = false;
  }
  else {
    for(vector<string>::const_iterator it=_WrongAnswers.begin(); it!=_WrongAnswers.end() && b_ret; ++it) {
      if(it->compare(_Answer)==0) {
        b_ret = false;
      }
    }
  }
  _WrongAnswers.clear();
  return b_ret;
}

unsigned int TTestClass_General::GetNumberOfValidSections(const TSetupInfo& _SetupInfo)
{
  unsigned int ui_NumberValidSections = 0;
  for(unsigned int i=0; i<_SetupInfo.m_Section.size(); ++i) {
    if(_SetupInfo.m_Section[i].mui_Difficulty <= _SetupInfo.mui_SetDifficulty) {
      ++ui_NumberValidSections;
    }
  }
  return ui_NumberValidSections;
}

bool TTestClass_General::CheckNoQuestions(TQuestionReaderWriter& _QuestionReaderWriter, bool _b_RadioOnly) 
{
  bool b_ret = false;
  string Question;
  string Answer; 
  unsigned int ui_Diff;
  vector<string> WrongAnswers;
  if(_QuestionReaderWriter.WasLastFileReadOK()) {
    if(!_b_RadioOnly) {
      b_ret = !_QuestionReaderWriter.GetNextQuestion(Question, Answer, ui_Diff);
    }
    else {
      b_ret = true;
    }
    if(b_ret) {
      b_ret = !_QuestionReaderWriter.GetNextQuestionRadio(Question, Answer, WrongAnswers, ui_Diff);
    }
  }
  return b_ret;
}

//for both this function and the following one need to put in other permutations. Radio was causing a premature reset.
//eg if we have 8 questions 6 radio and 2 non. If first six questions are all from the radio section then the next one will force a reset.
//ie although we do a check against the number of radio question in the TotalRoundCycleTests_Mix function it is still possible that the
//pool of radio questions has been depleted via the text string questions.

bool TTestClass_General::GuaranteeUnique(unsigned int _ui_TestType, const TSetupInfo& _SetupInfo, unsigned int _ui_QuestionNumber)
{
  bool b_ret = false;
  if(_ui_TestType == SINGLETYPE) {
    b_ret = true;
  }
  else if(areAllValidSectionsGreaterOrLessThanRadio(_SetupInfo)) {
    b_ret = true;
  }
  else if(_ui_QuestionNumber<GetTotalNumberRadioQuestions(_SetupInfo)) {
    b_ret = true;
  }
  return b_ret;
}

void TTestClass_General::UniqueQueAnsTest(unsigned int _ui_TestType, 
                                          const set<string>& _Answers, 
                                          const set<string>& _Questions, 
                                          const TSetupInfo& _SetupInfo, 
                                          bool _b_RadioOnly, 
                                          unsigned int _ui_QuestionNumber)
{
  int i_NumberQuestions;
  if(_b_RadioOnly) {
    i_NumberQuestions = GetTotalNumberRadioQuestions(_SetupInfo);
  }
  else {
    i_NumberQuestions = GetTotalNumberQuestions(_SetupInfo);
  }

  int i_NumberQuestionsSoFar = i_NumberQuestions>uiNoRounds ? uiNoRounds : i_NumberQuestions;
  if(GuaranteeUnique(_ui_TestType, _SetupInfo, _ui_QuestionNumber)) {
    //Using a set so adding question again will not increase size.
    ASSERT_EQ(_Questions.size(), i_NumberQuestionsSoFar);
  }
  else {
    ASSERT_LE(_Questions.size(), i_NumberQuestionsSoFar); 
  }
  ASSERT_EQ(getNumberAnswers(_Questions), _Answers.size());
}

bool TTestClass_General::CheckNewQuestionAndPush( unsigned int _ui_TestType, 
                                                  vector<string>& _Answers,
                                                  vector<string>& _Questions,
                                                  const string& _Answer,
                                                  const string& _Question, 
                                                  const TSetupInfo& _SetupInfo, 
                                                  unsigned int _ui_QuestionNumber)
{
  bool b_ret = true;
  if(TTestClass_General::GuaranteeUnique(_ui_TestType, _SetupInfo, _ui_QuestionNumber)) {
    if(find(_Answers.begin(), _Answers.end(), _Answer) != _Answers.end()) {
      b_ret = false;
    }
    else {
      if(find(_Questions.begin(), _Questions.end(), _Question) != _Questions.end()) {
        b_ret = false;
      }
    }
  }

  if(b_ret == true) {
    _Answers.push_back(_Answer);
    _Questions.push_back(_Question);
  }

  return b_ret;
}