#ifndef COMMONHEADERH
#define COMMONHEADERH

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#define QUEFILEDLIM "--"
#define QD "~~" //Question String Delimiter
#define TRIVAPRE "Trivia_"

enum GameType {TEXT, TEXTNUM, RADIO};
const int iMaxQALen = 2048;
enum Difficulty {EASY, MEDIUM, HARD};
const unsigned int uiNoDiffs = 3;
const int iMaxGameNameLen = 256;
const unsigned int uiNoRadioOptions = 5;
const unsigned int uiNoRounds = 10;

const unsigned int DLLRET_OK = 0;
const unsigned int DLLRET_GAMEINDEXOUTSIDERANGE = 1;
const unsigned int DLLRET_AUXFILEERROR = 2;

const unsigned int RET_OK = 0;
const unsigned int RET_RANGEERR = 1;
const unsigned int RET_STRINGDOESNOTEXIST = 2;
const unsigned int RET_FILECORRUPT = 3;
const unsigned int RET_DLLFUNCTIONRETURNERROR = 4;
const unsigned int RET_OTHER = 5;

#endif
