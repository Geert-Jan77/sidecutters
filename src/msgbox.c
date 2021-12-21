#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

int msgbox(int iLeft, int iTop, int	iWidth, int iHeight, char * sName)
{
	HMODULE libHandle;
	FARPROC GetDesktopWindow, GetWindowDC, GetDC, CreateSolidBrush, FillRgn, 
	CreateRectRgn, DeleteObject, CreateBitmap, CreatePatternBrush, GetObject, BitBlt, 
	CreateCompatibleDC, SelectObject, DeleteDC;
	HDC hDC1,hDC2;
	INT_PTR hDesk;
	INT_PTR hOrig, hBmp;
    //printf("testbutton [iLeft=%d], [iBottom=%d], [iWidth=%d], [iHeight=%d] \n", iLeft, iBottom, iWidth, iHeight);		
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
	
	hBmp = (INT_PTR)LoadImage(NULL, sName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBmp != (INT_PTR)NULL)
	{
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
					SelectObject(hDC2, hOrig);
					DeleteObject(hBmp);					
					DeleteDC(hDC1);
				}
				ReleaseDC((HWND)hDesk, hDC2);
			}
		}
	}
	return 0;
}
	