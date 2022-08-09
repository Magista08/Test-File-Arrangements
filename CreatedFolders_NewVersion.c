#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define ALL_FILE_NUM 256
/* #define ALL_FILE_NUM 262144 */
/* #define ALL_FILE_NUM 16777216 */

long long g_llFileName = 0;

void dfs_try(char *_pszFilePath, unsigned int _nLayer, unsigned int _nFileNum);
unsigned long looping_times(int _nFileNum);

int main(int args, char** argv){
    if ( args < 2 )
    {
        printf("USAGE: $0 <N>\n");
        return -1;
    }
    char *pLeftChar;
    unsigned int N = strtol(argv[1], &pLeftChar, 10);
    if (N == 0)
    {
        printf("You cannot input N as 0, or typing any thing excpet digits\n");
        return -1;
    }
    double dDemoniator = log((double) N);
    double dDevider    = log((double) ALL_FILE_NUM);
    double dQuotient   = dDevider / dDemoniator;
    unsigned int M = (unsigned int) dQuotient;
    char szFileInitPath[256] = {0};
    getcwd(szFileInitPath, sizeof(szFileInitPath));
    dfs_try(szFileInitPath, M, N);
}

void dfs_try(char *_pszFilePath, unsigned int _nLayer, unsigned int _nFileNum){
    char aTempPath[_nLayer];
    memset(aTempPath, 0, sizeof(aTempPath));
    int FoldersPtr = 0;
    unsigned char u1InputArray[256] = {0};
    char szFileName[100] = {0};
    char szWholeFileName[200] = {0};
    char szCreatedFolderPath[10] = {0};
    for (int i = 0; i < 256; i++)
    {
        u1InputArray[i] = i;
    }
    unsigned char u1SignalCreatNewFolder = 0;
    unsigned long LoopingNum = looping_times(_nFileNum);
    for(unsigned long i = 0; i < LoopingNum; i ++){
        if ( FoldersPtr == _nLayer )
        {
            /* creat files in the current folder*/
            for (unsigned int j = 0; j < _nFileNum; j++)
            {
                sprintf(szFileName, "/%lld.bin", g_llFileName);
                strcat(szWholeFileName, _pszFilePath);
                for(int k = 0; k < FoldersPtr; k++)
                {
                    sprintf(szCreatedFolderPath, "/%d", aTempPath[k]);
                    strcat(szWholeFileName, szCreatedFolderPath);
                    memset(szCreatedFolderPath, 0, sizeof(szCreatedFolderPath));
                }
                strcat(szWholeFileName, szFileName);
                FILE *fpCreatedfile = fopen(szWholeFileName, "w+");
                for(unsigned char k = 0; k < 2; k++)
                {
                    if ( fwrite(u1InputArray, sizeof(u1InputArray), 1, fpCreatedfile) != 1)
                    {
                        printf("Could Not Write Data into the file%s!!!\n", szFileName);
                        exit(-1);
                    }
                }
                g_llFileName++;
                memset(szWholeFileName, 0, sizeof(szWholeFileName));
                memset(szFileName, 0, sizeof(szFileName));
                fclose(fpCreatedfile);
            }
            u1SignalCreatNewFolder = 0;

            /* Change the current path and layer*/
            FoldersPtr--;
            while(u1SignalCreatNewFolder == 0)
            {
                aTempPath[(FoldersPtr)]++;
                if ( aTempPath[(FoldersPtr)] == _nFileNum)
                {
                    FoldersPtr--;
                }
                else
                {
                    u1SignalCreatNewFolder = 1;
                }
            }
            for (unsigned int k = FoldersPtr + 1; k < _nLayer; k++)
            {
                aTempPath[k] = 0;
            }
        }
        else
        {
            /* Move the path and creat only one folder */
            /* Creat the foldes*/
            strcat(szWholeFileName, _pszFilePath);
            for(int k = 0; k <= FoldersPtr; k++)
            {
                sprintf(szCreatedFolderPath, "/%d", aTempPath[k]);
                strcat(szWholeFileName, szCreatedFolderPath);
                memset(szCreatedFolderPath, 0, sizeof(szCreatedFolderPath));
            }
            if (mkdir(szWholeFileName,777) == -1)
            {
                printf("Could not create folder!\n");
                printf("%s\n", szWholeFileName);
                exit(-1);
            }
            printf("%s\n", szWholeFileName);
            /* Move the stack*/
            FoldersPtr++;
            memset(szWholeFileName, 0, sizeof(szWholeFileName));
        }
    }
}

unsigned long looping_times(int _nFileNum)
{
    unsigned long u8FoldersNum = 0;
    unsigned long u8CurrentFolders = 1;
    while(u8CurrentFolders != ALL_FILE_NUM)
    {
        u8FoldersNum += u8CurrentFolders;
        u8CurrentFolders = u8CurrentFolders * _nFileNum;
    }
    u8CurrentFolders = u8CurrentFolders / _nFileNum;
    u8FoldersNum += u8CurrentFolders;
    return u8FoldersNum;
}