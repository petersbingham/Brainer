//---------------------------------------------------------------------------

#ifndef SetupClass_GeneralH
#define SetupClass_GeneralH

class TSetupClass_General
{
public:
  static void WriteDiffToString(char* _pc_FileDiff, unsigned int _ui_FileDiff);
  static void CheckNoQuestions(const char* _pc_FileName, int _i_Difficulty = -1);
};


#endif