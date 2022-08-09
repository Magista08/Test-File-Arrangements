#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>      /*FOR: clock_t, clock()*/
#include <string.h>    /*FOR: strcpy*/
#include <unistd.h>

/* #define ALL_FILE_NUM 256 */
#define ALL_FILE_NUM 262144
/* #define ALL_FILE_NUM 16777216 */

unsigned int g_u4RandomSeed = 0;

typedef struct T_TestFile
{
    unsigned long nFileName;
    char szFilePath[256];
}
T_TestFile;

void open_files(unsigned long _u4TestFilesNum, T_TestFile *T_TestFileList);    /* */
void file_path(char *pOutputsentence, unsigned long _pFileName, unsigned int N);                /* Test Passed */

unsigned long random_files_creator();                                /* Test Passed */



int main(int args, char** argv) {
    /* Make sure the there are three passing parameters */
    if ( args < 4 )
    {
        printf("USAGE: $0 <N> <looping_times> <random_seed>\n");
        return -1;
    }

    /* Transfer two passing parameters into the unsigned int, and one into unsigned long */
    char *pLeftChar;
    unsigned int N = strtoul(argv[1], &pLeftChar, 10);
    unsigned long u4TestFilesNum = strtoul(argv[2], &pLeftChar,10);
    g_u4RandomSeed = strtoul(argv[3], &pLeftChar, 10);

    /* Initialize the random library and make sure the input is correct */
    srand(g_u4RandomSeed);
    if (N == 0 || u4TestFilesNum == 0)
    {
        printf("You cannot input N or test_files_num as 0, or typing any thing excpet digits\n");
        return -1;
    }

    /* Calculate the Layer */

    double dDemoniator = log((double) N);
    double dDevider    = log((double) ALL_FILE_NUM);
    double dQuotient   = dDevider / dDemoniator;
    int M = (int) dQuotient;

    /* Begin to Test! */

    T_TestFile T_AllTestFile[u4TestFilesNum];
    for (unsigned long i = 0; i < u4TestFilesNum; i++)
    {
        T_TestFile T_TempTestFile;
        T_TempTestFile.nFileName = random_files_creator();
        file_path(T_TempTestFile.szFilePath, T_TempTestFile.nFileName, N);
        T_AllTestFile[i] = T_TempTestFile;
    }

    /* Test Part */
    struct timeval tmTimeStorageBeg, tmTimeStorageEnd;
    gettimeofday(&tmTimeStorageBeg, NULL);
    open_files(u4TestFilesNum, T_AllTestFile);
    gettimeofday(&tmTimeStorageEnd, NULL);

    /* Calculate the time */
    long long u8SecBeg      = (long long) tmTimeStorageBeg.tv_sec;
    long long u8SecEnd      = (long long) tmTimeStorageEnd.tv_sec;
    long long u8MicroSecBeg = (long long) tmTimeStorageBeg.tv_usec;
    long long u8MicroSecEnd = (long long) tmTimeStorageEnd.tv_usec;

    long long u8TimeUsed = (u8SecEnd - u8SecBeg) * 1000000 + u8MicroSecEnd - u8MicroSecBeg;
    double dOutput   = (double) u8TimeUsed / (double) u4TestFilesNum;

    FILE *fpLogFile = fopen("FileArrangeMent.log", "a");
    fprintf(fpLogFile, "Average time used for opening a file Layer: %u , Files: %u is: %f\n", M, N, dOutput);
    fclose(fpLogFile);
}



void open_files(unsigned long _u4TestFilesNum, T_TestFile *T_TestFileList)
{
    unsigned char u1ReadDigit[1] = {0};
    for (unsigned long i = 0; i < _u4TestFilesNum; i++)
    {

        FILE *fpOpenFile = fopen(T_TestFileList[i].szFilePath, "r");
        if (fpOpenFile == NULL)
        {
            printf("Could not open the file!!!\n");
            exit(-1);
        }
        else if (fread(u1ReadDigit, sizeof(u1ReadDigit), 1, fpOpenFile) != 1)
        {
            printf("Could Not Read the File!!!\n");
            exit(-1);
        }
        fclose(fpOpenFile);
    }

}

void file_path(char *_pOutputSentence, unsigned long _pFileName, unsigned int N)
{
    unsigned long dDevider = ALL_FILE_NUM;
    unsigned long  dDenominator = _pFileName;
    char szFileLocation[256] = {0};
    char szFileLastPath[20] = {0};
    getcwd(szFileLocation, sizeof(szFileLocation));
    sprintf(szFileLastPath, "/%lu.bin", _pFileName);
    while(dDevider != 1)
    {
        char szTempFilePath[10] = {0};
        ldiv_t dFilePath = ldiv(dDenominator, dDevider);
        sprintf(szTempFilePath, "/%ld",dFilePath);
        strcat(szFileLocation, szTempFilePath);
        dDenominator = dDenominator % dDevider;
        dDevider = dDevider / N;
    }
    strcat(szFileLocation, szFileLastPath);
    strcpy(_pOutputSentence, szFileLocation);
}

unsigned long random_files_creator()
{
    unsigned long lRandFileName = rand();
    lRandFileName = lRandFileName % ALL_FILE_NUM;
    return lRandFileName;
}