#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define ALL_FILE_NUM 256


void file_path(char *_pOutputSentence, unsigned long _pFileName, unsigned int N);
void create_folders(char *_pFilePath, unsigned int _nFileNum, int _nLayer);
void input_files(unsigned long _u4AllFilesNum, unsigned int N);

int main(int args, char **argv){
    if ( args < 2 )
    {
        printf("USAGE: $0 <N> <looping_times>\n");
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
    int M = (int) dQuotient;
    char szFileInitPath[256] = {0};
    getcwd(szFileInitPath, sizeof(szFileInitPath));
    strcat(szFileInitPath, "/0");
    if (mkdir(szFileInitPath, 777) == -1)
    {
        printf("Current path is not valid. Please execute this function into another path\n");
        return -1;
    }

    create_folders(szFileInitPath, N, (M - 1));

    input_files(ALL_FILE_NUM, N);
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

void input_files(unsigned long _u4AllFilesNum, unsigned int N){
    unsigned char aInputArray[256] = {0};
    for(int i = 0; i < 256; i++)
    {
        aInputArray[i] = i;
    }
    for (unsigned long i = 0; i < _u4AllFilesNum; i++){
        char szFilePath[256] = {0};
        file_path(szFilePath, i, N);
        FILE *fpCreateFile = fopen(szFilePath, "w+");
        for(unsigned char j = 0; j < 2; j++)
        {
            if(fwrite(aInputArray, sizeof(aInputArray), 1, fpCreateFile) != 1)
            {
                printf("Could Not Write Data into the file%s!!!\n", szFilePath);
                exit(-1);
            }
        }
        fclose(fpCreateFile);
    }

}

void create_folders(char *_pFilePath, unsigned int _nFileNum, int _nLayer)
{
    if (_nLayer == 0){
        return;
    }
    else
    {
        for(int i = 0; i < _nFileNum; i++){
            char szFilePath[100] = {0};
            sprintf(szFilePath, "%s/%d",_pFilePath, i);
            if (mkdir(szFilePath,777) == -1)
            {
                printf("Could not create folder!\n");
                exit(-1);
            }
            create_folders(szFilePath, _nFileNum, (_nLayer - 1));
        }
    }
}