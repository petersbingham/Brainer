#include "FileUtils.h"

class TIniFile
{
private:
  char* mpc_path;
  char* mpc_section;
  bool isOK(const char* _pc_keyName);
  bool setString(const char* _pc_keyName, const char* _pc_keyValue);
  bool getString(const char* _pc_keyName, char* _pc_keyValue, unsigned int _ui_buffSize);

public:
  TIniFile(const char* _pc_path, const char* _pc_sectionName = NULL);
  ~TIniFile();

  void SetSection(const char* _pc_sectionName);
  bool SetInt(const char* _pc_keyName, int _i_value);
  int GetInt(const char* _pc_keyName, int _i_default);
};