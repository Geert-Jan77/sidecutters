#if __linux__
    //Defined on Linux
#elif __sun
    //Defined on Solaris
#elif __FreeBSD__
    //Defined on FreeBSD
#elif __NetBSD__
    //Defined on NetBSD
#elif __OpenBSD__  
    //Defined on OpenBSD
#elif __APPLE__ 
    //Defined on Mac OS X
#elif __hpux
    //Defined on HP-UX
#elif__osf__ 
    //Defined on Tru64 UNIX (formerly DEC OSF1)
#elif __sgi  
    //Defined on Irix
#elif _AIX 
    //Defined on AIX
#elif _WIN32 
    //Defined on Windows
	#include <stdio.h>
	#include <windows.h>
	INT iHsize, iVsize, iBtn;
	RECT rect2;
	gint taskbar(gint *left, gint *right, gint *top, gint *bottom)
	{
		BOOL bRet;
		LPPOINT lp1,lp2;
		iHsize = GetSystemMetrics(SM_CXSCREEN);
		iVsize = GetSystemMetrics(SM_CYSCREEN);
		printf("Screen Resolution w x h %d x %d \n", iHsize, iVsize);  
		RECT rect, rect1;
		HWND taskBar = FindWindow("Shell_traywnd", NULL); 
		if(taskBar && GetWindowRect(taskBar, &rect)) 
		{
			//printf("Desktop: left 0, right %d, top 0, bottom %d\n", iHsize, iVsize);
			//printf("Taskbar: left %d, right %d, top %d, bottom %d\n", rect.left, rect.right, rect.top, rect.bottom);
			if (rect.right < iHsize) rect1.left = rect.right; else rect1.left = 0;
			if (rect.left > 0) rect1.right = rect.left; else rect1.right = iHsize;
			if (rect.bottom < iVsize) rect1.top = rect.bottom; else rect1.top = 0; 
			if (rect.top > 0) rect1.bottom = rect.top; else rect1.bottom = iVsize;
			//printf("Max size: left %d, right %d, top %d, bottom %d\n", rect1.left, rect1.right, rect1.top, rect1.bottom);
			*left = (gint)rect1.left;
			*right = (gint)rect1.right;
			*top = (gint)rect1.top;
			*bottom = (gint)rect1.bottom;
		}
		return 0;
	}

#endif