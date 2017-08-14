//---------------------------------------------------------------------------
#pragma hdrstop

#include "CommonHeader.h"
#include "Questions.h"
#include "Numeric.h"
#include <string>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <windows.h>

struct RandInt
{
int operator() (int m)
{
	int i_rand;
	TNumeric::RandomInt(RAND_MAX,&i_rand);
	return i_rand%m;
}
} rand_int;

using namespace std;

//******************************************************************************************************
// TQuestionSection
//******************************************************************************************************

TQuestionSection::TQuestionSection() :
  mui_currentQuestionIndex(0)
{
};

bool IsRealQuestion(const TQuestion& _Question)
{
  return !_Question.mb_isDummy;
}

unsigned int TQuestionSection::createUniqueAnswerSet(set<string>& _ElligibleWrongAnswersSet)
{
  for(unsigned int i=0; i<m_Questions.size(); ++i) {
    if(i != mui_currentQuestionIndex) {
      if(m_Questions[i].m_Answer != m_Questions[mui_currentQuestionIndex].m_Answer) {
        _ElligibleWrongAnswersSet.insert(m_Questions[i].m_Answer);
      }
    }
  }
  return _ElligibleWrongAnswersSet.size();
}

unsigned int TQuestionSection::numberUniqueAnswers()
{
  set<string> ElligibleWrongAnswersSet;
  for(unsigned int i=0; i<m_Questions.size(); ++i) {
    ElligibleWrongAnswersSet.insert(m_Questions[i].m_Answer);
  }
  return ElligibleWrongAnswersSet.size();
}

bool TQuestionSection::getRandomWrongAnswers(vector<string>& _WrongAnswers)
{
  bool b_ret = false;
  set<string> ElligibleWrongAnswersSet;
  if(createUniqueAnswerSet(ElligibleWrongAnswersSet) >= uiNoRadioOptions-1) {
    vector<string> ElligibleWrongAnswersVector(ElligibleWrongAnswersSet.begin(), ElligibleWrongAnswersSet.end());
	random_shuffle(ElligibleWrongAnswersVector.begin(),ElligibleWrongAnswersVector.end(),rand_int);
    for(unsigned int i=0; i<uiNoRadioOptions-1; ++i) {
      _WrongAnswers.push_back(ElligibleWrongAnswersVector[i]);
    }
    b_ret = true;
  }
  return b_ret;
}

unsigned int TQuestionSection::GetNumberOfQuestions()
{
  return count_if(m_Questions.begin(), m_Questions.end(), IsRealQuestion);
}

unsigned int TQuestionSection::GetNumberQuestionsLeft()
{
  return count_if(m_Questions.begin()+mui_currentQuestionIndex, m_Questions.end(), IsRealQuestion);
}

bool TQuestionSection::AreQuestionsLeft()
{
  bool b_AreQuestions = false;
  if(GetNumberQuestionsLeft() > 0) {
    b_AreQuestions = true;
  }
  return b_AreQuestions;
}

bool TQuestionSection::AreQuestions()
{
  bool b_AreQuestions = false;
  if(count_if(m_Questions.begin(), m_Questions.end(), IsRealQuestion) > 0) {
    b_AreQuestions = true;
  }
  return b_AreQuestions;
}

bool TQuestionSection::AreEnoughAnswersForRadio()
{
  bool b_AreQuestions = false;
  if(numberUniqueAnswers() >= uiNoRadioOptions) {
    b_AreQuestions = true;
  }
  return b_AreQuestions;
}

bool TQuestionSection::GetNextQuestion( std::string& _Question,
                                      std::string& _Answer,
                                      unsigned int& _ui_Diff)
{
  bool b_ret = AreQuestionsLeft();
  if(b_ret) {
    while(m_Questions[mui_currentQuestionIndex].mb_isDummy == true) {
      ++mui_currentQuestionIndex;  
    }
    _Question = m_Questions[mui_currentQuestionIndex].m_Question;
    _Answer = m_Questions[mui_currentQuestionIndex].m_Answer;   
    _ui_Diff = m_Questions[mui_currentQuestionIndex].mui_Diff;
    ++mui_currentQuestionIndex; 
  }
  return b_ret;
}

bool TQuestionSection::GetNextQuestionRadio(string& _Question,
                                            string& _Answer,
                                            vector<string>& _WrongAnswers,
                                            unsigned int& _ui_Diff)
{
  bool b_ret = AreQuestionsLeft();
  if(b_ret) {
    while(m_Questions[mui_currentQuestionIndex].mb_isDummy == true) {
      ++mui_currentQuestionIndex;  
    }
    _Question = m_Questions[mui_currentQuestionIndex].m_Question;
    _Answer = m_Questions[mui_currentQuestionIndex].m_Answer;
    _ui_Diff = m_Questions[mui_currentQuestionIndex].mui_Diff;
    b_ret = getRandomWrongAnswers(_WrongAnswers);
    ++mui_currentQuestionIndex; 
  }
  return b_ret;
}

void TQuestionSection::AddQuestion( const std::string& _Question,
                                    const std::string& _Answer,
                                    unsigned int ui_Diff)
{
  m_Questions.push_back(TQuestion(_Question, _Answer, ui_Diff));
  if(_Question == string("Dummy")) {
    m_Questions[m_Questions.size()-1].mb_isDummy = true;
  }
}


void TQuestionSection::ResetAndShuffle()
{
  random_shuffle(m_Questions.begin(),m_Questions.end(),rand_int);
  mui_currentQuestionIndex = 0;
}

//******************************************************************************************************
// TQuestions
//******************************************************************************************************

bool TQuestions::getRandomSection(bool _b_Radio, unsigned int& _ui_Section)
{
  bool b_Viable = false;
  vector<unsigned int> ViableSections;
  for(unsigned int i=0; i<m_QuestionSections.size(); ++i) {
    if(m_QuestionSections[i].AreQuestionsLeft() && (!_b_Radio || m_QuestionSections[i].AreEnoughAnswersForRadio())) {
      ViableSections.insert(ViableSections.end(), m_QuestionSections[i].GetNumberQuestionsLeft(), i);
    }
    b_Viable = true;
  }

  int i_RandomIndex;
  TNumeric::RandomInt(ViableSections.size(), &i_RandomIndex);
  _ui_Section = ViableSections[i_RandomIndex];

  return b_Viable;
}

bool TQuestions::AreQuestionsLeft(bool _b_Radio)
{
  bool b_ret = false;
  for(unsigned int i=0; i<m_QuestionSections.size() && !b_ret; ++i) {
    if(m_QuestionSections[i].AreQuestionsLeft() && (!_b_Radio || m_QuestionSections[i].AreEnoughAnswersForRadio())) {
      b_ret = true;
    }
  }
  return b_ret;
}

bool TQuestions::AreQuestions(bool _b_Radio)
{
  bool b_ret = false;
  for(unsigned int i=0; i<m_QuestionSections.size() && !b_ret; ++i) {
    if(!_b_Radio) {
      b_ret = m_QuestionSections[i].AreQuestions();
    }
    else {
      b_ret = m_QuestionSections[i].AreEnoughAnswersForRadio();
    }
  }
  return b_ret;
}

unsigned int TQuestions::GetNumberOfQuestions(bool _b_Radio)
{
  unsigned int ui_NumberQuestionsLeft = 0;
  for(unsigned int i=0; i<m_QuestionSections.size(); ++i) {
    if(!_b_Radio || m_QuestionSections[i].AreEnoughAnswersForRadio()) {
      ui_NumberQuestionsLeft += m_QuestionSections[i].GetNumberOfQuestions();
    }
  }
  return ui_NumberQuestionsLeft;
}

unsigned int TQuestions::GetNumberQuestionsLeft(bool _b_Radio)
{
  unsigned int ui_NumberQuestionsLeft = 0;
  for(unsigned int i=0; i<m_QuestionSections.size(); ++i) {
    if(m_QuestionSections[i].AreQuestionsLeft() && (!_b_Radio || m_QuestionSections[i].AreEnoughAnswersForRadio())) {
      ui_NumberQuestionsLeft += m_QuestionSections[i].GetNumberQuestionsLeft();
    }
  }
  return ui_NumberQuestionsLeft;
}

bool TQuestions::AreEnoughAnswersForRadio()
{
  bool b_ret = false;
  for(unsigned int i=0; i<m_QuestionSections.size() && !b_ret; ++i) {
    b_ret = m_QuestionSections[i].AreEnoughAnswersForRadio();
  }
  return b_ret;
}

bool TQuestions::GetNextQuestion( std::string& _Question,
                                  std::string& _Answer,
                                  unsigned int& _ui_Diff)
{
  bool b_ret = false;
  unsigned int ui_Section;
  if(getRandomSection(false, ui_Section)) {
    b_ret = m_QuestionSections[ui_Section].GetNextQuestion(_Question, _Answer, _ui_Diff);
  }
  return b_ret;
}

bool TQuestions::GetNextQuestionRadio(  std::string& _Question,
                                        std::string& _Answer,
                                        std::vector<std::string>& _WrongAnswers,
                                        unsigned int& _ui_Diff)
{
  bool b_ret = false;
  unsigned int ui_Section;
  if(getRandomSection(true, ui_Section)) {
    b_ret = m_QuestionSections[ui_Section].GetNextQuestionRadio(_Question, _Answer, _WrongAnswers, _ui_Diff);
  }
  return b_ret;
}

void TQuestions::AddSection()
{
  m_QuestionSections.push_back(TQuestionSection());
}

bool TQuestions::AddQuestionToLastSection(  const std::string& _Question,
                                            const std::string& _Answer,
                                            unsigned int ui_Diff)
{
  bool b_ret = false;
  if(m_QuestionSections.size()>0) {
    m_QuestionSections[m_QuestionSections.size()-1].AddQuestion(_Question, _Answer, ui_Diff);
    b_ret = true;
  }
  return b_ret;
}

void TQuestions::ResetAndShuffle()
{
  for(unsigned int i=0; i<m_QuestionSections.size(); ++i) {
    m_QuestionSections[i].ResetAndShuffle();
  }
}

//******************************************************************************************************
// TQuestionReaderWriter
//******************************************************************************************************

unsigned int TQuestionReaderWriter::checkDiff(const string& _GroupID)
{
  unsigned int i_ret;
  if(_GroupID.find("Hard")!=string::npos) {
    i_ret = HARD;
  }
  else if(_GroupID.find("Medium")!=string::npos) {
    i_ret = MEDIUM;
  }
  else {
    i_ret = EASY;
  }
  return i_ret;
}

bool TQuestionReaderWriter::checkForHeader(const string& _firstLine)
{
	unsigned int headerPos = _firstLine.find(m_HeaderID.c_str()); 
	if(headerPos != string::npos) {
		m_Header = _firstLine.substr(headerPos+m_HeaderID.length());
		return true;
	}
	return false;
}

bool TQuestionReaderWriter::populateQuestions()
{
  bool b_ret = false;
  char pc_FileName[MAX_PATH];
  mb_LastFileLoadOK = false;
  if(m_GameName.find(".") == string::npos) {
    sprintf(pc_FileName,".\\Questions\\%s.que",m_GameName.c_str());
  }
  else {
    sprintf(pc_FileName,".\\Questions\\%s",m_GameName.c_str());
  }
  ifstream file(pc_FileName);
  if(!file.fail()) {
    mb_LastFileLoadOK = true;
    istream_iterator<string>FileIt(file);
    if (checkForHeader(*FileIt)) {
		advance(FileIt,1);
	}
	while(FileIt != istream_iterator<string>()) {
      if((*FileIt).find(m_SectionDelimiter.c_str()) != string::npos) {
        b_ret = true;
        unsigned int ui_Diff = checkDiff(*FileIt);
        m_Questions[ui_Diff].AddSection();
        advance(FileIt,1);
        while(FileIt!=istream_iterator<string>() && (*FileIt).find(m_SectionDelimiter.c_str())==string::npos) {
          string Question;
          getFileString(FileIt, Question);
          if(FileIt!=istream_iterator<string>() || (*FileIt).find(m_SectionDelimiter.c_str())==string::npos) {
            string Answer;
            getFileString(FileIt, Answer);
            if(Question.size()>0 || Answer.size()>0) {
              m_Questions[ui_Diff].AddQuestionToLastSection(Question, Answer, ui_Diff);
            }
          }
        }
        m_Questions[ui_Diff].ResetAndShuffle();
      }
      else {
        advance(FileIt,1);
      }
    }
  }
  return b_ret;
}

inline bool TQuestionReaderWriter::notEndOrDelimiter(istream_iterator<string>& _FileIt)
{
  return _FileIt!=istream_iterator<string>() &&
        (*_FileIt).find(m_QuestionDelimiter.c_str())==string::npos &&
        (*_FileIt).find(m_SectionDelimiter.c_str())==string::npos;
}

void TQuestionReaderWriter::getFileString(  istream_iterator<string>& _FileIt,
                                            string& _String)
{
  while(notEndOrDelimiter(_FileIt)) {
	if((*_FileIt).find(m_CommentDelimiter.c_str())!=string::npos) {
      _String.clear();       
	  advance(_FileIt,1);
	}
	else {
	  _String.append(*_FileIt);
	  advance(_FileIt,1);
	  if(notEndOrDelimiter(_FileIt)) {
		_String.append(" ");
	  }
	}
  }
  if((*_FileIt).find(m_QuestionDelimiter.c_str())!=string::npos) {
    advance(_FileIt,1);
  }
}

bool TQuestionReaderWriter::isViableForSelectedDifficulty(bool _b_Radio)
{
  bool b_Viable = false;
  switch(mui_Diff) {
    case HARD:
          if(m_Questions[HARD].AreQuestions(_b_Radio)) {
            b_Viable = true;
            break;
          }
    case MEDIUM:
          if(m_Questions[MEDIUM].AreQuestions(_b_Radio)) {
            b_Viable = true;
            break;
          }
    case EASY:
          if(m_Questions[EASY].AreQuestions(_b_Radio)) {
            b_Viable = true;
            break;
          }
  }
  return b_Viable;
}

void TQuestionReaderWriter::resetIfRequired(bool _b_Radio)
{
  switch(mui_Diff) {
    case HARD:
          if(!m_Questions[HARD].AreQuestionsLeft(_b_Radio) &&
          !m_Questions[MEDIUM].AreQuestionsLeft(_b_Radio) &&
          !m_Questions[EASY].AreQuestionsLeft(_b_Radio)) {
            if(m_Questions[HARD].AreQuestions(_b_Radio)) {
              m_Questions[HARD].ResetAndShuffle();
            }
            if(m_Questions[MEDIUM].AreQuestions(_b_Radio)) {
              m_Questions[MEDIUM].ResetAndShuffle();
            }
            if(m_Questions[EASY].AreQuestions(_b_Radio)) {
              m_Questions[EASY].ResetAndShuffle();
            }
          }
          break;
    case MEDIUM:
          if(!m_Questions[MEDIUM].AreQuestionsLeft(_b_Radio) &&
          !m_Questions[EASY].AreQuestionsLeft(_b_Radio)) {
            if(m_Questions[MEDIUM].AreQuestions(_b_Radio)) {
              m_Questions[MEDIUM].ResetAndShuffle();
            }
            if(m_Questions[EASY].AreQuestions(_b_Radio)) {
              m_Questions[EASY].ResetAndShuffle();
            }
          }
          break;
    case EASY:
          if(!m_Questions[EASY].AreQuestionsLeft(_b_Radio)) {
            if(m_Questions[EASY].AreQuestions(_b_Radio)) {
              m_Questions[EASY].ResetAndShuffle();
            }
          }
          break;
  }
}

inline void TQuestionReaderWriter::addGroupIfApplicable(vector<unsigned int>& _ViableGroups, unsigned int _ui_Diff, bool _b_Radio)
{
  if(m_Questions[_ui_Diff].AreQuestionsLeft(_b_Radio)) {
    _ViableGroups.insert(_ViableGroups.end(),m_Questions[_ui_Diff].GetNumberQuestionsLeft(_b_Radio),_ui_Diff);
  }
}

bool TQuestionReaderWriter::getRandomGroup(unsigned int& _ui_Group, bool _b_Radio)
{
  bool b_Viable = isViableForSelectedDifficulty(_b_Radio);
  if(b_Viable) {
    vector<unsigned int> ViableGroups;
    resetIfRequired(_b_Radio);
    switch(mui_Diff) {
      case HARD:
            addGroupIfApplicable(ViableGroups, HARD, _b_Radio);
      case MEDIUM:
            addGroupIfApplicable(ViableGroups, MEDIUM, _b_Radio);
      case EASY:
            addGroupIfApplicable(ViableGroups, EASY, _b_Radio);
    }
    if(ViableGroups.size()>0) {
      int i_RandomIndex;
      TNumeric::RandomInt(ViableGroups.size(), &i_RandomIndex);
      _ui_Group = ViableGroups[i_RandomIndex];
    }
    else {
      b_Viable = false;
    }
  }
  return b_Viable;
}

TQuestionReaderWriter::TQuestionReaderWriter(const string& _GameName) :
  m_GameName(_GameName),
  m_QuestionDelimiter(QUEFILEDLIM),
  m_SectionDelimiter("NewSection"),
  m_CommentDelimiter("$$"),
  m_HeaderID("$$Header"),
  mui_Diff(EASY),
  mb_LastFileLoadOK(false)
{
  populateQuestions();
}

void TQuestionReaderWriter::SetDifficulty(unsigned int _ui_Difficulty)
{
  if(_ui_Difficulty == HARD) {
    mui_Diff = HARD;
  }
  else if(_ui_Difficulty == MEDIUM) {
    mui_Diff = MEDIUM;
  }
  else {
    mui_Diff = EASY;
  }
}

bool TQuestionReaderWriter::GetHeader( std::string& _Header)
{
	_Header = m_Header;
	if (m_Header.length() == 0) {
		return false;
	}
	else {
		return true;
	}
}

bool TQuestionReaderWriter::GetNextQuestion( std::string& _Question,
                                             std::string& _Answer,
                                             unsigned int& _ui_Diff)
{
  bool b_ret = false;
  unsigned int ui_Group;
  if(getRandomGroup(ui_Group, false)) {
    b_ret = m_Questions[ui_Group].GetNextQuestion(_Question, _Answer, _ui_Diff);
  }
  return b_ret;
}

bool TQuestionReaderWriter::GetNextQuestionRadio(  std::string& _Question,
                                                   std::string& _Answer,
                                                   std::vector<std::string>& _WrongAnswers,
                                                   unsigned int& _ui_Diff)
{
  bool b_ret = false;
  unsigned int ui_Group;
  if(getRandomGroup(ui_Group, true)) {
    b_ret = m_Questions[ui_Group].GetNextQuestionRadio(_Question, _Answer, _WrongAnswers, _ui_Diff);
  }
  return b_ret;
}

string TQuestionReaderWriter::GetGameName()
{
  string ret;
  if(m_GameName.find(".") == string::npos) {
    ret = m_GameName;
  }
  else {
    ret = m_GameName.substr(0,m_GameName.find("."));
  }
  return ret;
}

bool TQuestionReaderWriter::AreQuestions()
{
  bool b_ret = false;
  if(m_Questions[HARD].AreQuestions(false)) {
    b_ret = true;
  }
  else if(m_Questions[MEDIUM].AreQuestions(false)) {
    b_ret = true;
  }
  else if(m_Questions[EASY].AreQuestions(false)) {
    b_ret = true;
  }
  return b_ret;
}

unsigned int TQuestionReaderWriter::GetTotalNumberOfTextQuestions()
{
	return getTotalNumberOfQuestions(false);
}

unsigned int TQuestionReaderWriter::GetTotalNumberOfRadioQuestions()
{
	return getTotalNumberOfQuestions(true);
}

unsigned int TQuestionReaderWriter::getTotalNumberOfQuestions(bool _b_Radio)
{
	unsigned int ui_numberQuestions = 0;
    switch(mui_Diff) {
      case HARD:
            ui_numberQuestions += m_Questions[HARD].GetNumberOfQuestions(_b_Radio);
      case MEDIUM:
            ui_numberQuestions += m_Questions[MEDIUM].GetNumberOfQuestions(_b_Radio);
      case EASY:
            ui_numberQuestions += m_Questions[EASY].GetNumberOfQuestions(_b_Radio);
    }
	return ui_numberQuestions;
}

void TQuestionReaderWriter::ResetAll()
{
  m_Questions[HARD].ResetAndShuffle();
  m_Questions[MEDIUM].ResetAndShuffle();
  m_Questions[EASY].ResetAndShuffle();
}
