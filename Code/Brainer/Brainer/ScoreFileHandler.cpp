#include "stdafx.h"
#include "ScoreFileHandler.h"
#include <fstream>
#include <deque>

#define SCOREFILE "scr.dat"

TScoreFileHandler::TScoreFileHandler()
{
	mpi_ScoreArray = new int[NOHIGHSCORES];
}

TScoreFileHandler::~TScoreFileHandler()
{
	delete[] mpi_ScoreArray; 
}

int TScoreFileHandler::Setgame(string &GameName)
{
	int iret = RET_OK;

	bool b_game = false;

	std::fstream file(SCOREFILE, ios::in | ios::binary);

	char ch;
	int igameret = RET_OK;
	string SearchGameName("");
	while(file.get(ch) && igameret==RET_OK) {
		if(ch == '?') {
			SearchGameName = "";
			igameret = getgamename(&file, SearchGameName);
			if(SearchGameName.compare(GameName)==0) {
				break;
			}
		}
	}
	if(SearchGameName.compare(GameName)==0) {
		b_game = true;
	}
	if(b_game) {
		iret = populatescorearray(&file);	
	}
	else {
		zeroscorearray();
	}

	return iret;
}

int TScoreFileHandler::GetScore(int _i_ScoreIndex)
{
	return mpi_ScoreArray[_i_ScoreIndex];
}

int TScoreFileHandler::TakeScore(string &GameName, int _i_Score)
{
	int iret = RET_OK;

	std::fstream file(SCOREFILE, ios::in | ios::out | ios::binary);

	if(!file) {
		createnewscoretable(GameName, _i_Score);	
	}
	else {
		char ch;
		int igameret = RET_OK;
		string SearchGameName("");
		while(file.get(ch) && igameret==RET_OK) {
			if(ch == '?') {
				SearchGameName = "";
				igameret = getgamename(&file, SearchGameName);
				if(SearchGameName.compare(GameName)==0) {
					break;
				}
			}
		}
		if(SearchGameName.compare(GameName)==0) {
			checkinsertnewhighscore(&file, _i_Score);
		}
		else {
			createnewscoretable(GameName, _i_Score);
		}
	}

	return iret;
}

int TScoreFileHandler::getgamename(fstream *_p_file, string &GameName)
{
	int iret = RET_OK;
	
	char ch;
	int i_chars = 0;
	while(_p_file->get(ch) && ch != ';' && i_chars < iMaxGameNameLen) {
		GameName += ch;
		i_chars++;
	}
	if(!_p_file || i_chars >= iMaxGameNameLen) {
		iret = RET_OTHER;
	}

	return iret;
}

int TScoreFileHandler::checkinsertnewhighscore(fstream *_p_file, int _i_Score)
{
	int iret = RET_OK;

	for(int i=0; i<NOHIGHSCORES; i++) {
		int i_Score;
		int i_pos = _p_file->tellg();
		_p_file->read((char*)&i_Score,sizeof(int));

		if(_i_Score>i_Score) {

			deque<int> Scores;	
			Scores.push_back(_i_Score);
			_p_file->seekg(i_pos);

			for(int j=0; j<NOHIGHSCORES-i; j++) {
				_p_file->read((char*)&i_Score,sizeof(int));
				Scores.push_back(i_Score);
			}

			_p_file->seekp(i_pos);

			for(int j=0; j<NOHIGHSCORES-i; j++) {
				i_Score = (int)Scores.front();
				Scores.pop_front();
				_p_file->write((char*)&i_Score,sizeof(int));
			}
			_p_file->close();

			break;
		}
	}

	if(_p_file) {
		_p_file->close();
	}

	return iret;
}

int TScoreFileHandler::createnewscoretable(string &GameName, int _i_Score)
{
	int iret = RET_OK;

	std::ofstream file2(SCOREFILE, ios::app | ios::out | ios::binary); 
	file2 << '?' << GameName.c_str() << ";";
	file2.write((char*)&_i_Score,sizeof(int));
	const int i_zero = 0;
	for(int i=0;i<9;i++) {
		file2.write((char*)&i_zero,sizeof(int));	
	}
	file2.close();
	return iret;
}

int TScoreFileHandler::populatescorearray(fstream *_p_file)
{
	int iret = RET_OK;

	for(int i=0; i<NOHIGHSCORES; i++) {
		if(_p_file)
			_p_file->read((char*)&(mpi_ScoreArray[i]),sizeof(int));
		else
			iret = RET_FILECORRUPT;
	}	

	return iret;
}

void TScoreFileHandler::zeroscorearray()
{
	for(int i=0; i<NOHIGHSCORES; i++) {
		mpi_ScoreArray[i] = 0;
	}
}