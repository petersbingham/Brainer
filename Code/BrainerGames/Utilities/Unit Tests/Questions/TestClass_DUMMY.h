//---------------------------------------------------------------------------

#ifndef TestClass_DUMMYH
#define TestClass_DUMMYH

#include "Questions.h"
#include "TestClass_General.h"

class TTestClass_DUMMY
{
private:
  static bool checkNoDummy(  const std::string& _Answer,
                             const std::string& _Question);  

  static void sequentialQuestionTests(unsigned int _ui_TestType,
                                      const std::string& _Answer,
                                      const std::string& _Question, 
                                      std::vector<std::string>& _Answers,
                                      std::vector<std::string>& _Questions,
                                      const TSetupInfo& _SetupInfo,
                                      unsigned int _ui_QuestionNumber);
  static void sequentialQuestionTests(unsigned int _ui_TestType,
                                      const std::string& _Answer,
                                      const std::string& _Question, 
                                      std::vector<std::string>& _Answers,
                                      std::vector<std::string>& _Questions,
                                      std::vector<std::string>& _WrongAnswers,
                                      const TSetupInfo& _SetupInfo,
                                      unsigned int _ui_QuestionNumber);
public:
  static void TotalRoundCycleTests_Text(TQuestionReaderWriter& _QuestionReaderWriter, const TSetupInfo& _SetupInfo);
  static void TotalRoundCycleTests_Radio(TQuestionReaderWriter& _QuestionReaderWriter, const TSetupInfo& _SetupInfo);

};


#endif