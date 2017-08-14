//---------------------------------------------------------------------------

#pragma hdrstop

#include "AnswerStringHelper.h"
#include "CommonHeader.h"
#include "Numeric.h"
#include <stdio.h>
#include <string.h>

void TAnswerStringHelper::CreateAnswerStringInt(char* _pc_QA, char* _pc_QAbase, int _i_Answer)
{
#ifdef TEST
	sprintf(_pc_QA,"%s%d;%d",_pc_QAbase,_i_Answer,_i_Answer);
#else
	sprintf(_pc_QA,"%s;%d",_pc_QAbase,_i_Answer);
#endif
}

void TAnswerStringHelper::CreateAnswerStringRoundedDouble(char* _pc_QA, char* _pc_QAbase, double _d_Answer, int _i_DecimalPlaces)
{
	double d_RoundedAnswer;
	TNumeric::RoundPrecision(_d_Answer, &d_RoundedAnswer, _i_DecimalPlaces);
	char pc_FormatString[256];
	pc_FormatString[0] = 0;
	char pc_TempString[56];
	pc_TempString[0] = 0;
#ifdef TEST
	strcpy(pc_FormatString,_pc_QAbase);
	sprintf(pc_TempString,"\%.");
	strcat(pc_FormatString,pc_TempString);
	sprintf(pc_TempString,"%df%s\%.",_i_DecimalPlaces,QD);
	strcat(pc_FormatString,pc_TempString);
	sprintf(pc_TempString,"%df",_i_DecimalPlaces);
	strcat(pc_FormatString,pc_TempString);
	sprintf(_pc_QA,pc_FormatString,d_RoundedAnswer,d_RoundedAnswer);
#else
	strcpy(pc_FormatString,_pc_QAbase);
	sprintf(pc_TempString,"%s\%.",QD);
	strcat(pc_FormatString,pc_TempString);
	sprintf(pc_TempString,"%df",_i_DecimalPlaces);
	strcat(pc_FormatString,pc_TempString);
	sprintf(_pc_QA,pc_FormatString,d_RoundedAnswer);
#endif
}

void TAnswerStringHelper::CreateAnswerStringDoubleToNearestInt(char* _pc_QA, char* _pc_QAbase, double _d_Answer)
{
 	int i_Answer;
	TNumeric::RoundToNearestInt(_d_Answer, &i_Answer);
#ifdef TEST
	sprintf(_pc_QA,"%s%d%s%d",_pc_QAbase,i_Answer,QD,i_Answer);
#else
	sprintf(_pc_QA,"%s%s%d",_pc_QAbase,QD,i_Answer);
#endif
}

void TAnswerStringHelper::CreateAnswerStringDoubleToNearestHalf(char* _pc_QA, char* _pc_QAbase, double _d_Answer)
{
	int i_Inter;
	TNumeric::RoundToNearestInt(_d_Answer*2, &i_Inter);
#ifdef TEST
	sprintf(_pc_QA,"%s%.1f%s%.1f",_pc_QAbase,(double)i_Inter/2,QD,(double)i_Inter/2);
#else
	sprintf(_pc_QA,"%s%s%.1f",_pc_QAbase,QD,(double)i_Inter/2);
#endif
}
