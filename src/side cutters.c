/* 
    compile:
	
		windres icon.rc -O coff -o icon.res  
		windres info.rc -O coff -o info.res  
		gcc "side cutters.c" icon.res info.res -o "side cutters.exe"
 
	On my monitor, the size of A4 is 1054 x 748 pixel = 297,3 x 210,2 mm  
	Include path starts from ./src where the code is, 
	Resource path starts from . where the executable is.
*/

#include <windows.h>
#include <stdio.h>
#include "../rsc/resource.h"
#include "generatebutton.c"
#include "msgbox.c"
#include "messages.c"

const char g_szClassName[] = "myWindowClass";
INT iRefreshButton;
INT iHsize, iVsize, iBtn;
INT iClientX, iClientY;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	generatebutton(100, 100, 100, 100, "rsc/side cutters a.bmp");  
    switch(msg)
    {
        case WM_LBUTTONDOWN:
        {
			iBtn = message(msg, wParam, lParam, iClientX, iClientY);
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);
            GetModuleFileName(hInstance, szFileName, MAX_PATH);
			if (iBtn == 1) msgbox(583, 400, 514, 249, "rsc/msgbox.bmp");
			if (iBtn == 2) msgbox(583, 400, 514, 249, "rsc/clear.bmp");
			if (iBtn == 3) msgbox(583, 400, 514, 249, "rsc/clear.bmp");
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
	iHsize = GetSystemMetrics(SM_CXSCREEN);
	iVsize = GetSystemMetrics(SM_CYSCREEN);
	printf("Screen Resolution w x h %d x %d \n", iHsize, iVsize);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//MoveWindow(GetConsoleWindow(), iHsize/2, 0, iHsize/2, iVsize - 80, TRUE);	
    //ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
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
    hWnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Side Cutters",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, iHsize, iVsize,
        NULL, NULL, hInstance, NULL);

    if(hWnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }	
    ShowWindow(hWnd, nCmdShow || AW_ACTIVATE);
	LPPOINT lpPoint;
	lpPoint->x=0;
	lpPoint->y=0;
    UpdateWindow(hWnd);
	BOOL bRet = ClientToScreen(hWnd, lpPoint);
	iClientX = lpPoint->x;
	iClientY = lpPoint->y;
	printf("Client to screen: %d, %d\n", iClientX, iClientY); 
	generatebutton(100, 100, 100, 100, "rsc/side cutters a.bmp");
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}