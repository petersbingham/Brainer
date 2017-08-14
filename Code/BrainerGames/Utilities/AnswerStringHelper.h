//---------------------------------------------------------------------------

#ifndef AnswerStringHelperH
#define AnswerStringHelperH

class TAnswerStringHelper
{
	public:
		static void CreateAnswerStringInt(char* _pc_QA, char* _pc_QAbase, int _i_Answer);
		static void CreateAnswerStringRoundedDouble(char* _pc_QA, char* _pc_QAbase, double _d_Answer, int _i_DecimalPlaces);
		static void CreateAnswerStringDoubleToNearestInt(char* _pc_QA, char* _pc_QAbase, double _d_Answer);
		static void CreateAnswerStringDoubleToNearestHalf(char* _pc_QA, char* _pc_QAbase, double _d_Answer);
};

//---------------------------------------------------------------------------
#endif
