/*
-----------------------------------------------------------------------------------------
 testsound performs a beep test using the soundcard. 
 
 To compile and run:

     gcc testsound.c -o testsound.exe
	 
-----------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <Windows.h>

int main(int argc, char * argv[])
{
    HMODULE libHandle;
	FARPROC procHandle;
	UINT uFreq, uDuration;
	BOOL bRet;
	if(argc > 2)
	{
		uFreq = (int) strtol(argv[1], (char **)NULL, 10);
		uDuration = (int) strtol(argv[2], (char **)NULL, 10);
		printf("Use frequeny and duration: testsound [uFreq=%d] [uDuration=%d]\n", uFreq, uDuration);
	}
    else
	{
		uFreq = 300;
		uDuration = 1200;
        printf("Use default frequeny and duration: testsound [uFreq=300] [uDuration=1200]\n");
    }
    if ((libHandle = LoadLibrary(TEXT("C:/Windows/System32/kernel32.dll"))) == NULL)
    {
        printf("LoadLibrary failed\n");
        return 1;
    }
    if ((procHandle = GetProcAddress(libHandle, "Beep")) == NULL)
    {
        printf("GetProcAddress failed\n");
        printf("%d\n", GetLastError());
        return 1;
    }
	/*printf("procHandle %d\n", procHandle);*/
	if (!(bRet = procHandle(uFreq, uDuration)))
	{
		printf("Testsound failed\n");
		return 1;
	}
    return 0;
}
