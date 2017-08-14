//---------------------------------------------------------------------------
#ifndef MiscUtilsH
#define MiscUtilsH

class TMiscUtils
{
public:
    static bool IntFromString(const char* _pc_string, int& _i_int);
    static void charTowchar(const char* _pc_in, wchar_t* _pwc_out); 
    static void shuffleArray(const char* _pc_in);
    static void strToLowerCase(char* _pc_in);
    static int caseIndepstrcmp(const char * str1, const char * str2);
};

#endif
