#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.c"

int label(int iLeft, int iTop, char * sName)
{
	HMODULE libHandle;
	FARPROC GetDesktopWindow, GetWindowDC, GetDC, CreateSolidBrush, FillRgn, 
	CreateRectRgn, DeleteObject, CreateBitmap, CreatePatternBrush, GetObject, BitBlt, 
	CreateCompatibleDC, SelectObject, DeleteDC;
	INT_PTR hBrush, hRect, hBmp, hDesk, hOrig;
	HDC hDC1, hDC2;
	BITMAPINFOHEAD bitmapInfoHeader;
	unsigned char *bitmapData;
	CHAR sFile1[50], sFile2[50], sFile3[50];
	CHAR cHr;
	INT length, iWidth, iHeight;
	char* str;
	BOOL bRet;
    if ((libHandle = LoadLibrary(TEXT("C:/Windows/System32/user32.dll"))) == NULL) { return 1; }
    if ((GetDesktopWindow = GetProcAddress(libHandle, "GetDesktopWindow")) == NULL){ return 1;}
	if ((GetWindowDC = GetProcAddress(libHandle, "GetWindowDC")) == NULL) { return 1;}
	if ((GetDC = GetProcAddress(libHandle, "GetDC")) == NULL) { printf("Error GetDC\n"); return 1; }
	if ((libHandle = LoadLibrary(TEXT("C:/Windows/System32/gdi32.dll"))) == NULL){ return 1;}
    if ((CreateSolidBrush = GetProcAddress(libHandle, "CreateSolidBrush")) == NULL) { return 1;}
    if ((FillRgn = GetProcAddress(libHandle, "FillRgn")) == NULL) { return 1;}
    if ((CreateRectRgn = GetProcAddress(libHandle, "CreateRectRgn")) == NULL) { return 1; }
    if ((DeleteObject = GetProcAddress(libHandle, "DeleteObject")) == NULL) { return 1; }
	if ((CreateBitmap = GetProcAddress(libHandle, "CreateBitmap")) == NULL) { printf("Error CreateBitmap\n"); return 1; }
	if ((CreatePatternBrush = GetProcAddress(libHandle, "CreatePatternBrush")) == NULL) { printf("Error CreatePatternBrush\n"); return 1; }
	if ((BitBlt = GetProcAddress(libHandle, "BitBlt")) == NULL) { printf("Error BitBlt\n"); return 1; }
	if ((CreateCompatibleDC = GetProcAddress(libHandle, "CreateCompatibleDC")) == NULL) { printf("Error CreateCompatibleDC\n"); return 1; }
	if ((SelectObject = GetProcAddress(libHandle, "SelectObject")) == NULL) { printf("Error SelectObject\n"); return 1; }
    if ((DeleteDC = GetProcAddress(libHandle, "DeleteDC")) == NULL) { printf("Error DeleteDC\n"); return 1; }
	
	INT iLen = strlen(sName);
	printf("Label length %d\n", iLen);
	for (int i = 0; i < iLen; i++)
	{
		strcpy(sFile1, "fnt14/");
		cHr = sName[i];
		length = snprintf( NULL, 0, "%d", (INT)cHr );
		str = malloc( length + 1 );
		snprintf( str, length + 1, "%d", (INT)cHr );
		if (length == 1) {strcpy(sFile2, "00"); strcat(sFile2, str); }
		if (length == 2) {strcpy(sFile2, "0"); strcat(sFile2, str);}
		if (length == 3) strcpy(sFile2, str);
		free(str);
		strcat(sFile1, sFile2);
		strcpy(sFile3, ".bmp");
		strcat(sFile1, sFile3);
		//printf("The filename is %s\n", sFile1);
		hBmp = (INT_PTR)LoadImage(NULL, sFile1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (hBmp != (INT_PTR)NULL)
		{
			bitmapData = LoadBitmapFle(sFile1,&bitmapInfoHeader);
			// The bmp is loaded for the second time here.
			iWidth = bitmapInfoHeader.biWidth;
			iHeight = bitmapInfoHeader.biHeight;
			//printf("Width x height  %d x %d\n", iWidth, iHeight);
			hDesk = GetDesktopWindow();
			if (hDesk != (INT_PTR)NULL)
			{
				hDC2 = (HDC)GetWindowDC(hDesk);
				if (hDC2 != NULL)
				{
					hDC1 = (HDC)CreateCompatibleDC(hDC2);
					if (hDC1 != NULL)
					{
						hOrig = SelectObject(hDC1, hBmp);
						BitBlt(hDC2, iLeft, iTop, iWidth, iHeight, hDC1, 0, 0, SRCCOPY);
						iLeft = iLeft + iWidth - 1;
						SelectObject(hDC2, hOrig);
						DeleteObject(hBmp);					
						DeleteDC(hDC1);
					}
				ReleaseDC((HWND)hDesk, hDC2);
				}
			}
		}
	}
	printf("Label right %d pix\n", iLeft);
	return 0;
}
