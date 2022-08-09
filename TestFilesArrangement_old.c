#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>      /*FOR: clock_t, clock()*/
#include <string.h>    /*FOR: strcpy*/
#include <unistd.h>

/* #define ALL_FILE_NUM 256 */
#define ALL_FILE_NUM 262144
/* #define ALL_FILE_NUM 16777216 */

void open_files(unsigned int _u4TestFilesNum, unsigned int *_aAllFilesName, unsigned int N);    /* */
void file_path(char *pOutputsentence, unsigned long _pFileName, unsigned int N);                /* Test Passed */

unsigned long random_files_creator(unsigned long _u8FilesTimes);                                /* Test Passed */


int main(int args, char** argv) {
    if ( args < 3 )
    {
        printf("USAGE: $0 <N> <looping_times>\n");
        return -1;
    }
    char *pLeftChar;
    unsigned int N = strtol(argv[1], &pLeftChar, 10);
    unsigned int u4TestFilesNum = strtol(argv[2], &pLeftChar,10);
    if (N == 0 || u4TestFilesNum == 0)
    {
        printf("You cannot input N or test_files_num as 0, or typing any thing excpet digits\n");
        return -1;
    }

    double dDemoniator = log((double) N);
    double dDevider    = log((double) ALL_FILE_NUM);
    double dQuotient   = dDevider / dDemoniator;
    int M = (int) dQuotient;

    /* Begin to Test! */

    unsigned int aAllFilesName[u4TestFilesNum];
    for (unsigned long i = 0; i < u4TestFilesNum; i++){
        aAllFilesName[i] = 0;
        aAllFilesName[i] = random_files_creator(i);
    }

    struct timeval tmTimeStorageBeg, tmTimeStorageEnd;
    unsigned long u8SecBeg = 0, u8MicroSecBeg = 0;
    unsigned long u8SecEnd = 0, u8MicroSecEnd = 0;

    gettimeofday(&tmTimeStorageBeg, NULL);
    open_files(u4TestFilesNum, aAllFilesName, N);
    gettimeofday(&tmTimeStorageEnd, NULL);

    u8SecBeg = tmTimeStorageBeg.tv_sec;
    u8SecEnd = tmTimeStorageEnd.tv_sec;
    u8MicroSecBeg = tmTimeStorageBeg.tv_usec;
    u8MicroSecEnd = tmTimeStorageEnd.tv_usec;

    unsigned long dTimeUsed = (u8SecEnd - u8SecBeg) * 1000000 + u8MicroSecEnd - u8MicroSecBeg;
    double dOutput   = (double) dTimeUsed / u4TestFilesNum;

    char szOutputSentence[200] = {0};
    sprintf(szOutputSentence, "Average time used for opening a file Layer: %u , Files: %u is: %f\n\n", M, N, dOutput);
    FILE *fpLogFile = fopen("FileArrangeMent.log", "a");
    if ( fpLogFile == NULL )
    {
        printf("Could not find the file FileArrangeMent.log");
        return -1;
    }
    else if ( fwrite(szOutputSentence, sizeof(szOutputSentence), 1, fpLogFile) != 1)
    {
        printf("Cannot write data into the file FileArrangeMent.log\n");
        return -1;
    }
    fclose(fpLogFile);
}



void open_files(unsigned int _u4TestFilesNum, unsigned int *_aAllFilesName, unsigned int N)
{
    for (unsigned int i = 0; i < _u4TestFilesNum; i++)
    {
        unsigned char u1ReadDigit[2] = {0};
        char szFileLocation[256] = {0};
        file_path(szFileLocation, _aAllFilesName[i], N);
        FILE *fpOpenFile = fopen(szFileLocation, "r");
        if (fpOpenFile == NULL)
        {
            printf("Could not open the file!!!\n");
            exit(-1);
        }
        else if (fread(u1ReadDigit, sizeof(u1ReadDigit), 1, fpOpenFile) != 1 ||
             u1ReadDigit[0] != 0){
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

unsigned long random_files_creator(unsigned long _u8FilesTimes)
{
    srand(_u8FilesTimes);
    unsigned long lRandFileName = rand();
    lRandFileName = lRandFileName % ALL_FILE_NUM;
    return lRandFileName;
}