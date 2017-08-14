#include <fstream>
using namespace std;

#define NOHIGHSCORES 10

class TScoreFileHandler
{
public:
	TScoreFileHandler();
	~TScoreFileHandler();
	int GetNumberOfScores(string &GameName, int *_pi_NoScores);
	int GetScore(int _i_ScoreIndex);

	int TakeScore(string &GameName, int _i_Score);
	int Setgame(string &GameName);

private:
	int getgamename(fstream *_p_file, string &GameName);
	int checkinsertnewhighscore(fstream *_p_file, int _i_Score);
	int createnewscoretable(string &GameName, int _i_Score);
	int populatescorearray(fstream *_p_file);
	void zeroscorearray();
	int* mpi_ScoreArray;
	
};