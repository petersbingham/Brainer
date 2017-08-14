class TGames {
private:
	string* GameNames;
	int mi_NoGames;
public:
	TGames(int _i_NoGames);
	~TGames();
	int GetNumGames();
	int SetGame(int _i_Index, string _Name);
	int GetIndex(int* _pi_Index, string _Name);
	int GetGame(int _i_Index, string& _Name);
};

TGames::TGames(int _i_NoGames)
{
	mi_NoGames = _i_NoGames; 
	GameNames = new string[_i_NoGames];
}

TGames::~TGames()
{
	delete[] GameNames;
}

int TGames::GetNumGames()
{
	return mi_NoGames;
}

int TGames::SetGame(int _i_Index, string _Name)
{
	int i_ret = RET_OK;
	if(_i_Index>=mi_NoGames) {
		i_ret = RET_RANGEERR; 
	}
	else {
		GameNames[_i_Index] = _Name; 	
	}
	return i_ret; 
}

int TGames::GetIndex(int* _pi_Index, string _Name)
{
	int i_ret = RET_OK;

	*_pi_Index = -1;

	for(int i=0;i<mi_NoGames;i++) {
		if(_Name == GameNames[i]) {
			*_pi_Index = i;		
		}
	}

	if(*_pi_Index == -1) {
		i_ret = RET_STRINGDOESNOTEXIST;
	}

	return i_ret; 	
}

int TGames::GetGame(int _i_Index, string& _Name)
{
	int i_ret = RET_OK;

	if(_i_Index>=mi_NoGames || _i_Index<0) {
		i_ret = RET_RANGEERR; 
	}
	else {
		_Name = GameNames[_i_Index]; 	
	}

	return i_ret; 	
}

struct TRound {
	int mi_GameIndex;
	bool mb_Correct;
	int mi_score;
};

class TRounds {
public:
	int mi_NumRounds;
	TRound* mp_rounds;
	TRounds() {
		mp_rounds = NULL;
		mi_NumRounds = -1;
	}
	~TRounds() {
		if (mp_rounds != NULL) {
			delete[] mp_rounds;
		}
	}
	int GetNumberOfRounds()
	{
		return mi_NumRounds;
	}
	TRound& GetRound(const unsigned int _ui_Index)
	{
		return mp_rounds[_ui_Index];
	}
	void InitialiseRounds(unsigned int _ui_NumGames) {
		mi_NumRounds = static_cast<int>(_ui_NumGames);
		if (mp_rounds != NULL) {
			delete[] mp_rounds;
		}
		mp_rounds = new TRound[mi_NumRounds];
	}
};