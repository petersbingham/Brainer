#define PATHLEN 256
#include <string>

#define STRSIZE 128

using namespace std;

class TGamedllWrapper;

class TGameContainer
{
public:
	TGameContainer();
	void Setup();
	~TGameContainer();
	int GetNumberOfGames();
	int GetNumberOfQuestions(int i_GameIndex);
	int GetGameName(string &GameName, int i_GameIndex);
	int GetGameType(int* _pi_GameType, int i_GameIndex);
	int GetQA(char* _pc_QA, int i_GameIndex);
	int SetDiff(int _i_Diff, int i_GameIndex);
	int GetTimeLimit(int* _pi_TimeLimit, int i_GameIndex);
  int Reset(int i_GameIndex);

private:
	void mapGameIndexToDllIndex(int i_GameIndex, unsigned int& ui_DllIndex, unsigned int& ui_DllGameIndex);
	unsigned int mapGameIndexToDllIndex(int i_GameIndex);
	unsigned int mapGameIndexToDllGameIndex(int i_GameIndex);
	char mpc_cwd[PATHLEN];
	int mi_NoDlls;
	TGamedllWrapper **mpp_GameWrappers;
};