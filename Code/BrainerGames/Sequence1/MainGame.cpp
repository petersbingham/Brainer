//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonHeader.h"
#include "MainGame.h"
#include "string.h"
#include "Numeric.h"   
#include "DllRetCodes.h"
#include <math.h>

#define NOWRONGANS 8
//At least 4:
#define SEQLEN 5
#define NOQSEQTYPES 2
#define LINEAR 0
#define POLY 1

TMainGame::TMainGame()
{
	strcpy(mpc_GameName,"Sequence1");
	mi_Diff = EASY;
	mi_GameType = RADIO;
	mi_TimeOut = 32;
}

void TMainGame::GetGameName(unsigned int /*_ui_GameIndex*/, char* _pc_GameName)
{
	strcpy(_pc_GameName,mpc_GameName);
}

void TMainGame::GetGameType(unsigned int /*_ui_GameIndex*/, int* _pi_GameType)
{
	*_pi_GameType = mi_GameType;
}

int TMainGame::GetQA(unsigned int /*_ui_GameIndex*/, char* _pc_QA)
{
	int i_SeqType;
	int pi_Seq[SEQLEN];
	int pi_WrongAns[SEQLEN*NOWRONGANS];
	getSequence(&i_SeqType);
	getanswerarrays(pi_Seq, pi_WrongAns, i_SeqType);
	int pi_stringarray[SEQLEN+9];
	if(mi_Diff == EASY) {
		createdisplaystring(pi_Seq, pi_WrongAns, pi_stringarray, EASY);
		sprintf(_pc_QA,"Set the missing elements in the following sequence:\n %d, %d, %d, ?, ?.%s%d,%d%s%d,%d%s%d,%d%s%d,%d%s%d,%d%s%d"
			,pi_stringarray[0],pi_stringarray[1],pi_stringarray[2],QD,pi_stringarray[3],pi_stringarray[4],QD,pi_stringarray[5]
			,pi_stringarray[6],QD,pi_stringarray[7],pi_stringarray[8],QD,pi_stringarray[9],pi_stringarray[10],QD,pi_stringarray[11]
			,pi_stringarray[12],QD,pi_stringarray[13]);
	}
	else if(mi_Diff == MEDIUM) {
		createdisplaystring(pi_Seq, pi_WrongAns, pi_stringarray, MEDIUM);
		sprintf(_pc_QA,"Set the missing elements in the following sequence:\n %d, %d, ?, ?, %d.%s%d,%d%s%d,%d%s%d,%d%s%d,%d%s%d,%d%s%d"
			,pi_stringarray[0],pi_stringarray[1],pi_stringarray[2],QD,pi_stringarray[3],pi_stringarray[4],QD,pi_stringarray[5]
			,pi_stringarray[6],QD,pi_stringarray[7],pi_stringarray[8],QD,pi_stringarray[9],pi_stringarray[10],QD,pi_stringarray[11]
			,pi_stringarray[12],QD,pi_stringarray[13]);
	}
	else if(mi_Diff == HARD) {
		createdisplaystring(pi_Seq, pi_WrongAns, pi_stringarray, HARD);
		sprintf(_pc_QA,"Set the missing elements in the following sequence:\n %d, ?, ?, %d, %d.%s%d,%d%s%d,%d%s%d,%d%s%d,%d%s%d,%d%s%d"
			,pi_stringarray[0],pi_stringarray[1],pi_stringarray[2],QD,pi_stringarray[3],pi_stringarray[4],QD,pi_stringarray[5]
			,pi_stringarray[6],QD,pi_stringarray[7],pi_stringarray[8],QD,pi_stringarray[9],pi_stringarray[10],QD,pi_stringarray[11]
			,pi_stringarray[12],QD,pi_stringarray[13]);
	}
  return TDllRetCodes::DLLRET_OK;
}

void TMainGame::SetDiff(unsigned int /*_ui_GameIndex*/, int _i_Diff)
{
	mi_Diff = _i_Diff;
}

void TMainGame::GetTimeLimit(unsigned int /*_ui_GameIndex*/, int* _pi_Secs)
{
	*_pi_Secs = mi_TimeOut;
}        

void TMainGame::Reset(unsigned int /*_ui_GameIndex*/)
{
}

void TMainGame::getSequence(int* _pi_SeqType)
{
	TNumeric::RandomInt(NOQSEQTYPES, _pi_SeqType);
}

void TMainGame::getanswerarrays(int* _pi_Seq, int* _pi_WrongAns, int _i_SeqType)
{
	generateSequence(_pi_Seq, _i_SeqType);

	for(int i=0;i<NOWRONGANS;i++) {
		int j;
		if(i>=NOWRONGANS/2) {
			j=i+i;
		}
		else {
			j=i;
		}
		for(int k=0;k<SEQLEN;k++) {
			_pi_WrongAns[i*SEQLEN+k] = _pi_Seq[k]+j-NOWRONGANS/2;
		}
	}
}

void TMainGame::generateSequence(int* _pi_Seq, int _i_SeqType)
{
	TNumeric::RandomInt(30, _pi_Seq);
	int i_Const;

	switch (_i_SeqType) {
		case LINEAR:
			if(mi_Diff == EASY) {
				while(i_Const%5!=0) {
					TNumeric::RandomInt(100, &i_Const);
					i_Const+=27;
				}
			}
			if(mi_Diff == MEDIUM) {
				while(i_Const%5!=0) {
					TNumeric::RandomInt(1000, &i_Const);
					i_Const+=270;
				}
			}
			if(mi_Diff == HARD) {
				while(i_Const%5!=0) {
					TNumeric::RandomInt(10000, &i_Const);
					i_Const+=2700;
				}
			}
			for(int i=1;i<SEQLEN;i++) {
				_pi_Seq[i] = _pi_Seq[0] + i_Const * i;
			}
			break;

		case POLY:
			int i_Exp;
			TNumeric::RandomInt(2, &i_Exp);
			i_Exp+=2;
			if(mi_Diff == EASY) {
				TNumeric::RandomInt(2, &i_Const);
				i_Const+=2;
			}
			if(mi_Diff == MEDIUM) {
				TNumeric::RandomInt(10, &i_Const);
				i_Const+=5;
			}
			if(mi_Diff == HARD) {
				TNumeric::RandomInt(100, &i_Const);
				i_Const+=5;
				i_Exp+=2;
			}
			for(int i=1;i<SEQLEN;i++) {
				_pi_Seq[i] = _pi_Seq[0] + i_Const * pow(i,i_Exp);
			}
			break;
	}

}

void TMainGame::createdisplaystring(const int* _pi_Seq, const int* _pi_WrongAns, int* _pi_stringarray, int _i_Diff)
{
	if(_i_Diff == EASY) {
		_pi_stringarray[0] = _pi_Seq[0];
		_pi_stringarray[1] = _pi_Seq[1];
		_pi_stringarray[2] = _pi_Seq[2];
	}
	else if(_i_Diff == MEDIUM) {
		_pi_stringarray[0] = _pi_Seq[0];
		_pi_stringarray[1] = _pi_Seq[1];
		_pi_stringarray[2] = _pi_Seq[4];
	}
	else if(_i_Diff == HARD) {
		_pi_stringarray[0] = _pi_Seq[0];
		_pi_stringarray[1] = _pi_Seq[3];
		_pi_stringarray[2] = _pi_Seq[4];
	}

	//Whcih of the five GUI options is the correct one
	TNumeric::RandomInt(5, &_pi_stringarray[SEQLEN+8]);
	(_pi_stringarray[SEQLEN+8])++;

	//Randomly get which of the wrong answer series will be used for the 4 wrong answer options in the GUI
	int i_randomwrongansorder[4];
	int* pi_wronganswers = new int[NOWRONGANS];
	for(int i=0; i<NOWRONGANS; i++) {
		pi_wronganswers[i] = i;
	}
	for(int i=0; i<4; i++) {
		int i_Wrongans;
		TNumeric::RandomInt(NOWRONGANS-i, &i_Wrongans);
		i_randomwrongansorder[i] = pi_wronganswers[i_Wrongans];
		int j=i_Wrongans;
		for(j; j<NOWRONGANS-1; j++) {
			pi_wronganswers[j] = pi_wronganswers[j+1];
		}
	}



	//which of the two answers to be displayed in the options
	int i_First;
	int i_Second;
	if(_i_Diff == EASY) {
		i_First = 3;
		i_Second = 4;
	}
	else if(_i_Diff == MEDIUM) {
		i_First = 2;
		i_Second = 3;
	}
	else if(_i_Diff == HARD) {
		i_First = 1;
		i_Second = 2;
	}

	int j=0;
	for(int i=0; i<5; i++) {
		if(i+1==_pi_stringarray[SEQLEN+8]) { //write the correct answer sequence
			//Array position: Question Sequence + Correct answer minus one to correct for range times 2 since two missing sequence elements
			_pi_stringarray[SEQLEN-2+(_pi_stringarray[SEQLEN+8]-1)*2] = _pi_Seq[i_First];
			_pi_stringarray[SEQLEN-1+(_pi_stringarray[SEQLEN+8]-1)*2] = _pi_Seq[i_Second];
		}
		else { //write the incorrect answer sequence
			_pi_stringarray[SEQLEN-2+i*2] = _pi_WrongAns[i_First+i_randomwrongansorder[j]*5];
			_pi_stringarray[SEQLEN-1+i*2] = _pi_WrongAns[i_Second+i_randomwrongansorder[j]*5];
			j++;
		}
	}

	delete [] pi_wronganswers;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
