//---------------------------------------------------------------------------

#ifndef QuestionsH
#define QuestionsH

#include <vector>
#include <set>
#include <map>
#include <iterator>
#include "Numeric.h"

class TQuestion
{
  private:
    TQuestion(){};
  public:
    TQuestion(const std::string& _Question, const std::string& _Answer, unsigned int _ui_Diff) :
      m_Question(_Question), m_Answer(_Answer), mui_Diff(_ui_Diff), mb_isDummy(false){};
    std::string m_Question;
    std::string m_Answer; 
    unsigned int mui_Diff;
    bool mb_isDummy;
};

class TQuestionSection
{
  private:
    unsigned int mui_currentQuestionIndex;
    std::vector<TQuestion> m_Questions;
    unsigned int createUniqueAnswerSet(std::set<std::string>& _ElligibleWrongAnswersSet);
    unsigned int numberUniqueAnswers();
    bool getRandomWrongAnswers(std::vector<std::string>& _WrongAnswers);
  public:
    TQuestionSection();
    bool AreQuestionsLeft();
    bool AreQuestions();
	unsigned int GetNumberOfQuestions();
    unsigned int GetNumberQuestionsLeft();
    bool AreEnoughAnswersForRadio();
    bool GetNextQuestion( std::string& _Question,
                          std::string& _Answer,
                          unsigned int& _ui_Diff);
    bool GetNextQuestionRadio(  std::string& _Question,
                                std::string& _Answer,
                                std::vector<std::string>& _WrongAnswers,
                                unsigned int& _ui_Diff);
    void AddQuestion( const std::string& _Question,
                      const std::string& _Answer,
                      unsigned int _ui_Diff);
    void ResetAndShuffle();
};

class TQuestions
{
  private:
    std::vector<TQuestionSection> m_QuestionSections;
    bool getRandomSection(bool _b_Radio, unsigned int& _ui_Section);
  public:
    bool AreQuestionsLeft(bool _b_Radio);
    bool AreQuestions(bool _b_Radio);
	unsigned int GetNumberOfQuestions(bool _b_Radio);
    unsigned int GetNumberQuestionsLeft(bool _b_Radio);
    bool AreEnoughAnswersForRadio();
    bool GetNextQuestion( std::string& _Question,
                          std::string& _Answer,
                          unsigned int& _ui_Diff);
    bool GetNextQuestionRadio(  std::string& _Question,
                                std::string& _Answer,
                                std::vector<std::string>& _WrongAnswers,
                                unsigned int& _ui_Diff);
    void AddSection();
    bool AddQuestionToLastSection(  const std::string& _Question,
                                    const std::string& _Answer,
                                    unsigned int _ui_Diff);
    void ResetAndShuffle();
};

class TQuestionReaderWriter
{
  private:
    std::string m_GameName;
    std::string m_QuestionDelimiter;
    std::string m_SectionDelimiter;      
    std::string m_CommentDelimiter;
    std::string m_HeaderID;
    std::string m_Header;
    std::map<unsigned int, TQuestions> m_Questions;
    unsigned int mui_Diff;
    bool mb_LastFileLoadOK;
    unsigned int checkDiff(const std::string& _GroupID);
    bool checkForHeader(const std::string& _firstLine);
    TQuestionReaderWriter(){};
    bool populateQuestions();
    inline bool notEndOrDelimiter(std::istream_iterator<std::string>& _FileIt);
    void getFileString(std::istream_iterator<std::string>& _FileIt, std::string& _String);
    bool isViableForSelectedDifficulty(bool _b_Radio);
    void resetIfRequired(bool _b_Radio);
    inline void addGroupIfApplicable(std::vector<unsigned int>& _ViableGroups, unsigned int __ui_Diff, bool _b_Radio);
    bool getRandomGroup(unsigned int& _ui_Group, bool _b_Radio);
	unsigned int getTotalNumberOfQuestions(bool _b_Radio);
  public:
    TQuestionReaderWriter(const std::string& _GameName);
    bool WasLastFileReadOK() {return mb_LastFileLoadOK;}
    void SetDifficulty(unsigned int __ui_Difficulty);
    bool GetHeader( std::string& _Header);
    bool GetNextQuestion( std::string& _Question,
                          std::string& _Answer,
                          unsigned int& _ui_Diff);
    bool GetNextQuestionRadio(  std::string& _Question,
                                std::string& _Answer,
                                std::vector<std::string>& _WrongAnswers,
                                unsigned int& _ui_Diff);
    bool AreQuestions();
	unsigned int GetTotalNumberOfTextQuestions();
	unsigned int GetTotalNumberOfRadioQuestions();
    std::string GetGameName();
    void ResetAll();
};
//---------------------------------------------------------------------------
#endif
