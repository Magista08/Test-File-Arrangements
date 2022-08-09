#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

/* #define ALL_FILE_NUM 256 */
#define ALL_FILE_NUM 262144
/* #define ALL_FILE_NUM 16777216 */


long long g_llFileName = 0;

void create_folders(char *_pFilePath, unsigned int _nFileNum, int _nLayer, FILE *_fpCreatedfile, unsigned char *_aInputArray);

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

    unsigned char aInputArray[256] = {0};
    for(int i = 0; i < 256; i++)
    {
        aInputArray[i] = i;
    }
    FILE *fpCreatedfile = NULL;

    create_folders(szFileInitPath, N, (M - 1), fpCreatedfile, aInputArray);

}


/*Using the Dynamic Allocation to build the all folders and create 1kb .bin documents at the bottom*/
void create_folders(char *_pFilePath, unsigned int _nFileNum, int _nLayer, FILE *_fpCreatedfile, unsigned char *_aInputArray)
{

    /*Jusdge if it is in the botoom layer or not*/
    if (_nLayer == 0){

        /*Looping to build the */
        char szFileName[100] = {0};
        char szWholeFileName[200] = {0};
        for (unsigned int i = 0; i < _nFileNum; i++)
        {
            sprintf(szFileName, "/%lld.bin", g_llFileName);
            strcat(szWholeFileName, _pFilePath);
            strcat(szWholeFileName, "/");
            strcat(szWholeFileName, szFileName);
            _fpCreatedfile = fopen(szWholeFileName, "w+");
            for(unsigned char j = 0; j < 2; j++)
            {
                if ( fwrite(_aInputArray, sizeof(_aInputArray), 1, _fpCreatedfile) != 1)
                {
                    printf("Could Not Write Data into the file%s!!!\n", szFileName);
                    exit(-1);
                }
            }
            g_llFileName++;
            memset(szWholeFileName, 0, sizeof(szWholeFileName));
            fclose(_fpCreatedfile);
        }
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
            create_folders(szFilePath, _nFileNum, (_nLayer - 1), _fpCreatedfile, _aInputArray);
        }
    }
}
