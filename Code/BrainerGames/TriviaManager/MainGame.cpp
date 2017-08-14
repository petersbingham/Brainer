//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "DllRetCodes.h"
#include "FileUtils.h"
#include <direct.h>
#include <string>
#include <algorithm>

using namespace std;

TMainGame::TMainGame()
{
  mi_Diff = EASY;
  setGameType();
  mi_TimeOut = 15;
  populateQuestionReaderWriterVec();
#ifdef TEST
  mi_TimeOut = 999;
#endif   
}

void TMainGame::GetGameName(unsigned int _ui_GameIndex, char* _pc_GameName)
{
  strcpy(_pc_GameName,m_QuestionReaderWriterVec[_ui_GameIndex].GetGameName().c_str());
}

void TMainGame::GetGameType(unsigned int /*_ui_GameIndex*/, int* _pi_GameType)
{
  *_pi_GameType = mi_GameType;
}

unsigned int TMainGame::GetNumberOfQuestions(unsigned int _ui_GameIndex)
{
	if(mi_GameType==RADIO)
		return m_QuestionReaderWriterVec[_ui_GameIndex].GetTotalNumberOfRadioQuestions();
	else                    
		return m_QuestionReaderWriterVec[_ui_GameIndex].GetTotalNumberOfTextQuestions();
}

int TMainGame::GetQA(unsigned int _ui_GameIndex, char* _pc_QA)
{
  int i_Ret = TDllRetCodes::DLLRET_OK;

  string Question;
  string Answer;
  vector<string> Answers;

  if(mi_GameType == RADIO) {
    if(m_QuestionReaderWriterVec[_ui_GameIndex].GetNextQuestionRadio(Question,Answer,Answers,mui_LastQueDiff)) {
      Answers.push_back(Answer);
      random_shuffle(Answers.begin(), Answers.end());
      unsigned int ui_AnswerPos = find(Answers.begin(), Answers.end(), Answer) - Answers.begin() + 1;
      sprintf(_pc_QA,"%s%s%s%s%s%s%s%s%s%s%s%s%d",
        Question.c_str(),QD,
        Answers[0].c_str(),QD,Answers[1].c_str(),QD,Answers[2].c_str(),QD,Answers[3].c_str(),QD,Answers[4].c_str(),QD,
        ui_AnswerPos);
    }
    else {
      i_Ret = TDllRetCodes::DLLRET_AUXFILEERROR;
    }
  }
  else {
    if(m_QuestionReaderWriterVec[_ui_GameIndex].GetNextQuestion(Question,Answer,mui_LastQueDiff)) {
      sprintf(_pc_QA,"%s%s%s", Question.c_str(),QD, Answer.c_str());
    }
    else {
      i_Ret = TDllRetCodes::DLLRET_AUXFILEERROR;
    }
  }

  return i_Ret;
}

void TMainGame::SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff)
{
  mi_Diff = _i_Diff;
  for(vector<TQuestionReaderWriter>::iterator it=m_QuestionReaderWriterVec.begin();
  it!=m_QuestionReaderWriterVec.end(); ++it) {
    it->SetDifficulty(mi_Diff);
  }
  //setGameType();
}
void TMainGame::GetTimeLimit(unsigned int _ui_GameIndex, int* _pi_Secs)
{
  string Header;
  int i_baseTime = 5;
  if(m_QuestionReaderWriterVec[_ui_GameIndex].GetHeader(Header)) {
	  i_baseTime = atoi(Header.c_str());
  }
  if (getLastQueDiff() == mi_Diff) {
      *_pi_Secs = i_baseTime*3;
  }
  else if (mi_Diff == MEDIUM || getLastQueDiff() == MEDIUM) {
	  *_pi_Secs = i_baseTime*2;
  }
  else {
	  *_pi_Secs = i_baseTime;
  }
}

void TMainGame::Reset(unsigned int _ui_GameIndex)
{
  m_QuestionReaderWriterVec[_ui_GameIndex].ResetAll();
}


unsigned int TMainGame::getLastQueDiff()
{
  return mui_LastQueDiff;
}

void TMainGame::populateQuestionReaderWriterVec()
{
  TFileNames* p_FileNames = new TFileNames();
  char pc_cwd[MAXPATH];
  _getcwd(pc_cwd,MAXPATH);
  char pc_questionPath[MAXPATH];
  sprintf(pc_questionPath,"%s%s",pc_cwd,"\\Questions");
  TFileUtils::GetFilesInDir(pc_questionPath,&mi_NoQuestionFiles,p_FileNames,"","que");
  int i_NoInvalidQuestionFiles = 0;
  for(int i=0; i<mi_NoQuestionFiles; ++i) {
    int i_DllSize;
    int iret = p_FileNames->GetFileNameLength(&i_DllSize,i+1);
    if(iret != RET_OK) {
      mi_NoQuestionFiles = i;
    }
    else {
      char *cp_FileName = new char[i_DllSize+1];
      iret = p_FileNames->GetFileName(cp_FileName,i+1);
      if(iret != RET_OK) {
        mi_NoQuestionFiles = i;
      }
      else {
        TQuestionReaderWriter QuestionReaderWriter(cp_FileName);
        if(QuestionReaderWriter.WasLastFileReadOK() && QuestionReaderWriter.AreQuestions()) {
          m_QuestionReaderWriterVec.push_back(TQuestionReaderWriter(cp_FileName));
        }
        else {
          ++i_NoInvalidQuestionFiles;
        }
      }
      delete[] cp_FileName;
    }
  }
  mi_NoQuestionFiles -= i_NoInvalidQuestionFiles;
  delete p_FileNames;
}

void TMainGame::setGameType()
{
  if(mi_Diff == HARD) {
	mi_GameType = TEXT;
  }
  else {
	mi_GameType = RADIO;
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
