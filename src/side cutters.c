/* 

    compile:
	
		windres icon.rc -O coff -o icon.res  
		windres info.rc -O coff -o info.res  
		gcc "side cutters.c" icon.res info.res -o "side cutters.exe"
 
	On my monitor, the size of A4 is 1054 x 748 pixel = 297,3 x 210,2 mm  
	Include path starts from ./src where the code is, 
	Resource path starts from . where the executable is.
*/
#define CYCLES_REFRESH 33750000 //10 ms 3,375 GHz
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../rsc/resource.h"
#include "generatebutton.c"
#include "msgbox.c"
#include "messages.c"
#include "label.c"

BOOL bDebug = FALSE;
const char g_szClassName[] = "Side Cutters";
INT iHsize, iVsize, iBtn;
RECT rect2;
unsigned long long remember_time;

void delay(int milli_seconds)
{
	unsigned long long cycles = (unsigned long long) milli_seconds * 3375000; 
	unsigned long long start_time = _rdtsc();
    while (_rdtsc() < start_time + cycles);
	printf("Waited %d Mcycles\n", cycles / 1000000 );
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT point;
	char* str;
	INT length;
	CHAR sStr1[50],sStr2[50],sStr3[50];
	if ((_rdtsc()-remember_time) > CYCLES_REFRESH) 
	{
		if (bDebug) message(msg, wParam, lParam);
		if (lParam==33554432) 
		{
			delay(200);
			generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");
			label(120 + iClientX, 205 + iClientY, "Generate");
			remember_time = _rdtsc();
		}
	}
	
	switch(msg)
    {
        case WM_LBUTTONDOWN:
        {
			if ((_rdtsc()-remember_time) > CYCLES_REFRESH) 
			{
				iBtn = message(msg, wParam, lParam);
				char szFileName[MAX_PATH];
				HINSTANCE hInstance = GetModuleHandle(NULL);
				GetModuleFileName(hInstance, szFileName, MAX_PATH);
				if (iBtn == 1) msgbox(583 + iClientX, 300 + iClientY, 514, 249, "rsc/msgbox.bmp");
				if (iBtn == 2) msgbox(583 + iClientX, 300 + iClientY, 514, 249, "rsc/clear.bmp");
				if (iBtn == 3) msgbox(583 + iClientX, 300 + iClientY, 514, 249, "rsc/clear.bmp");
				remember_time = _rdtsc();
			}
		}
        break;
		case WM_EXITMENULOOP:
		{
			if ((_rdtsc()-remember_time) > CYCLES_REFRESH) 
			{	
				generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
				label(120 + iClientX, 205 + iClientY, "Generate");
				remember_time = _rdtsc();
			}
		}
		break;
		case WM_SETFOCUS:
		{
			if ((_rdtsc()-remember_time) > CYCLES_REFRESH) 
			{
				delay(300);
				generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");
				label(120 + iClientX, 205 + iClientY, "Generate");
				remember_time = _rdtsc();
			}
		}
		break;
		case WM_MOUSEMOVE:
		{
			if ((_rdtsc()-remember_time) > CYCLES_REFRESH) 
			{
				if (GetCursorPos(&point)) 
				{
					length = snprintf( NULL, 0, "Cursor: %d, %d   ", point.x, point.y );
					str = malloc( length + 1 );
					snprintf( str, length + 1, "Cursor: %d, %d   ", point.x, point.y );
					printf("%s\n", str);
					label(120 + iClientX, 300 + iClientY, str);
					free(str);
					remember_time = _rdtsc();
				}
			}
		}
		break;
		case WM_NCMOUSEMOVE:
		{
			if ((_rdtsc()-remember_time) > CYCLES_REFRESH) 
			{
				if (GetCursorPos(&point)) 
				{
					length = snprintf( NULL, 0, "Cursor: %d, %d   ", point.x, point.y );
					str = malloc( length + 1 );
					snprintf( str, length + 1, "Cursor: %d, %d   ", point.x, point.y );
					printf("%s\n", str);
					label(120 + iClientX, 300 + iClientY, str);
					free(str);
					remember_time = _rdtsc();
				}
			
				switch(wParam)
				{
					case 2:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 5:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 8:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 9:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 10:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 11:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 15:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 16:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 18:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					case 20:
					{
						generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");  
						label(120 + iClientX, 205 + iClientY, "Generate");
						remember_time = _rdtsc();
					}
					break;
					default:
				}
			}
		}
		break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
	}
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	BOOL bRet;
	LPPOINT lp1,lp2;
	iHsize = GetSystemMetrics(SM_CXSCREEN);
	iVsize = GetSystemMetrics(SM_CYSCREEN);
	printf("Screen Resolution w x h %d x %d \n", iHsize, iVsize);
	if (!bDebug) ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (bDebug) MoveWindow(GetConsoleWindow(), iHsize/2, 0, iHsize/2 - 6, iVsize - 50, TRUE);	
	WNDCLASSEX wc;
    HWND hWnd;
    MSG Msg;
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = g_szClassName;
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wc.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "Side Cutters", 
	(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ), 
	CW_USEDEFAULT, CW_USEDEFAULT, iHsize, iVsize, NULL, NULL, hInstance, NULL); // WS_MAXIMIZEBOX, WS_THICKFRAME , WS_DISABLED
    if(hWnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }	
    ShowWindow(hWnd, nCmdShow || AW_ACTIVATE);
	UpdateWindow(hWnd);
	lp1->x=0;
	lp1->y=0;
	bRet = ClientToScreen(hWnd, lp1);
	iClientX = lp1->x;
	iClientY = lp1->y;
	printf("Client to screen: %d, %d\n", iClientX, iClientY); 
	RECT rect, rect1;
    HWND taskBar = FindWindow("Shell_traywnd", NULL);
    if(taskBar && GetWindowRect(taskBar, &rect)) {
		printf("Desktop: left 0, right %d, top 0, bottom %d\n", iHsize, iVsize);
        printf("Taskbar: left %d, right %d, top %d, bottom %d\n", rect.left, rect.right, rect.top, rect.bottom);
		if (rect.right != iHsize) rect1.left = rect.right; else rect1.left = 0;
		if (rect.left != 0) rect1.right = rect.left; else rect1.right = iHsize;
		if (rect.bottom != iVsize) rect1.top = rect.bottom; else rect1.top = 0;
		if (rect.top != 0) rect1.bottom = rect.top; else rect1.bottom = iVsize;
		printf("Max size: left %d, right %d, top %d, bottom %d\n", rect1.left, rect1.right, rect1.top, rect1.bottom);
		rect2.left = rect1.left + 6;
		rect2.top = rect1.top + 6;
		rect2.right = rect1.right - 6;
		rect2.bottom = rect1.bottom - 6;
		printf("Side Cutters: left %d, right %d, top %d, bottom %d\n", rect2.left, rect2.right, rect2.top, rect2.bottom);
	}
	if (bDebug) MoveWindow(hWnd, rect2.left, rect2.top, rect2.right / 2 - rect2.left, rect2.bottom - rect2.top, TRUE);	
	if (!(bDebug)) MoveWindow(hWnd, rect1.left, rect1.top, rect1.right - rect1.left, rect1.bottom - rect1.top, TRUE);
	UpdateWindow(hWnd);
	lp1->x=0;
	lp1->y=0;
	bRet = ClientToScreen(hWnd, lp1);
	iClientX = lp1->x;
	iClientY = lp1->y;
	printf("Client to screen: %d, %d\n", iClientX, iClientY); 
	delay(200);
	generatebutton(100 + iClientX, 100 + iClientY, 100, 100, "rsc/side cutters a.bmp");
	label(120 + iClientX, 205 + iClientY, "Generate");
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
