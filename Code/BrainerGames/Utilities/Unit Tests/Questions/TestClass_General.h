//---------------------------------------------------------------------------

#ifndef TestClass_GeneralH
#define TestClass_GeneralH

#include "Questions.h"
#include <string>
#include <set>
#include <vector>

class TFileSectionInfo
{
  public:
    TFileSectionInfo(unsigned int _ui_NumberQuestions, unsigned int _ui_Difficulty)
      : mui_NumberQuestions(_ui_NumberQuestions), mui_NumberDummyQuestions(0), mui_Difficulty(_ui_Difficulty) {}
    TFileSectionInfo(unsigned int _ui_NumberQuestions, unsigned int _ui_NumberDummyQuestions, unsigned int _ui_Difficulty)
      : mui_NumberQuestions(_ui_NumberQuestions), mui_NumberDummyQuestions(_ui_NumberDummyQuestions), mui_Difficulty(_ui_Difficulty) {}
    TFileSectionInfo(unsigned int _ui_NumberQuestions, std::vector<unsigned int> _DuplicateQuestions, unsigned int _ui_Difficulty)
      : mui_NumberQuestions(_ui_NumberQuestions), mui_NumberDummyQuestions(0), m_DuplicateQuestions(_DuplicateQuestions), mui_Difficulty(_ui_Difficulty) {}
    unsigned int mui_NumberQuestions;
    unsigned int mui_NumberDummyQuestions;
    std::vector<unsigned int> m_DuplicateQuestions;
    unsigned int mui_Difficulty;
};

class TSetupInfo
{
  public:
    unsigned int mui_SetDifficulty;
    std::vector<TFileSectionInfo> m_Section; 
};

class TTestClass_General
{
public:
  enum {SINGLETYPE, MIXEDTYPE}TTestType;

private:
  static unsigned int vectorSum(const std::vector<unsigned int>& _Duplicates);
  static unsigned int getNumberUniqueAnswers(unsigned int _ui_NumberSectionQuestions, const std::vector<unsigned int>& _Duplicates);
  static int getStringPos(const std::string& _SearchString, const std::string& _FindString);
  static int getNumberFromString(const std::string& _String, int _i_StartPosition);
  static int getQueAnsNumber(const std::string& _String, bool _b_Answer);
  static int getSectionNumber(const std::string& _String);
  static bool checkValidStringDiff(const TSetupInfo& _SetupInfo, unsigned int _ui_Diff);
  static bool areAllValidSectionsGreaterOrLessThanRadio(const TSetupInfo& _SetupInfo);
  static unsigned int getNumberAnswers(const std::set<std::string>& _Questions);

public:
  static unsigned int GetTotalNumberRadioQuestions(const TSetupInfo& _SetupInfo);
  static unsigned int GetTotalNumberQuestions(const TSetupInfo& _SetupInfo);
  static void Increment( unsigned int& _ui_CntTotalQue, 
                         unsigned int& _ui_CntPartQue, 
                         std::set<std::string>& _UniqueAnswers,
                         std::set<std::string>& _UniqueQuestions,
                         const std::string& _Answer,
                         const std::string& _Question);

  static bool CheckAnsQueCorrespondence(  const std::string& _Answer,
                                          const std::string& _Question);

  static unsigned int HighestFileDifficulty(const TSetupInfo& _SetupInfo);

  static bool CheckCorrectDiffInString(const std::string& _String, const TSetupInfo& _SetupInfo);

  static bool CheckWrongAnswersAndClear(const std::string& _Answer, std::vector<std::string>& _WrongAnswers);

  static unsigned int GetNumberOfValidSections(const TSetupInfo& _SetupInfo);

  static bool CheckNoQuestions(TQuestionReaderWriter& _QuestionReaderWriter, bool b_RadioOnly=false);

  //static bool CheckNumberQuestions(TQuestionReaderWriter& _QuestionReaderWriter, bool b_Radio, unsigned int mui_SetDifficulty);

  static bool GuaranteeUnique(unsigned int _ui_TestType, const TSetupInfo& _SetupInfo, unsigned int _ui_QuestionNumber);

  static void UniqueQueAnsTest( unsigned int _ui_TestType, 
                                const std::set<std::string>& _Answers, 
                                const std::set<std::string>& _Questions, 
                                const TSetupInfo& _SetupInfo, 
                                bool _b_RadioOnly, 
                                unsigned int _ui_QuestionNumber);

  static bool CheckNewQuestionAndPush(unsigned int _ui_TestType, 
                                      std::vector<std::string>& _Answers,
                                      std::vector<std::string>& _Questions,
                                      const std::string& _Answer,
                                      const std::string& _Question, 
                                      const TSetupInfo& _SetupInfo, 
                                      unsigned int _ui_QuestionNumber);
};


#endif