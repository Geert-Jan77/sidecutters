/*

 directories used: C:/Windows/System32/
 TODO:  user32.TrackMouseEvent redraws the rectangle, rounded buttons, etc.
-----------------------------------------------------------------------------------------
 testbutton performs a display test using the graphics card. 
 Paint a bitmap file on the monitor with BitBlt.
 
 To compile and run:

     gcc testbutton.c -o testbutton.exe
	 
 Run:
	 
	 testbmp [iLeft=0], [iRight=508], [iTop=0], [iBottom=495]
	 
-----------------------------------------------------------------------------------------
*/
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

int generatebutton(int iLeft, int iTop, int	iWidth, int iHeight, char * sName)
{
	HMODULE libHandle;
	FARPROC GetDesktopWindow, GetWindowDC, GetDC, CreateSolidBrush, FillRgn, 
	CreateRectRgn, DeleteObject, CreateBitmap, CreatePatternBrush, GetObject, BitBlt, 
	CreateCompatibleDC, SelectObject, DeleteDC;
	INT_PTR hBrush, hRect;
	BOOL bRet;
	UINT bitmapArray[10000];
	UINT *ptr = bitmapArray;
	INT_PTR hArr = *ptr;
	HDC hDC1,hDC2;
	HBITMAP hBmp;
	hBmp = (HBITMAP)LoadImage(NULL, sName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bmInfo;
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
	hDC2 = (HDC)GetWindowDC(GetDesktopWindow());
	hDC1 = (HDC)CreateCompatibleDC(hDC2);
	INT_PTR hOrig = SelectObject(hDC1, (INT_PTR)hBmp);
	BitBlt(hDC2, iLeft, iTop, iWidth, iHeight, hDC1, 0, 0, SRCCOPY);
	DeleteDC(hDC1);
	return 0;
}
	