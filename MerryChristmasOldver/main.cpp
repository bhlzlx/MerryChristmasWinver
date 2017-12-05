#include <windows.h>
#include <gdiplus.h>
#include <tchar.h>
#include "resource.h"

#include "CPhantomWnd.h"
#include "TrayIcon.h"
#include "CTimer.h"


char TrayIconMessage[] = "MerryChristmas!";

#define  SNOW_COUNT 20

std::shared_ptr<WndData>    pSnowWnds[SNOW_COUNT];
std::shared_ptr<TrayIcon>   pTrayIcon;
std::shared_ptr<WndData>    pThemeWnd;

CTimer*                   pTimers[SNOW_COUNT];

HINSTANCE g_hInstance;

void CTimerCallBackTest(CTimer *pTimer)
{
    bool rand = CRandGen::Rand()%2 & 0x1;
    pSnowWnds[pTimer->GetTimerID()]->StepMove(rand);
}

//extern HDC g_ImageCacheDC[18];
/*  GDI+ startup token */
ULONG_PTR gdiplusStartupToken;

long unsigned int SnowWindowThreadProc(void *pVoid)
{
    for(int i = 0;i<20;i++)
    {
        pSnowWnds[i] = CreateSnowWindow(GetDCArray());
        pTimers[i] = CTimer::CreateTimer(150,&CTimerCallBackTest);
    }
    /* Run the message loop. It will run until GetMessage() returns 0 */
    MSG messages;
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    Gdiplus::GdiplusShutdown(gdiplusStartupToken);
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

long unsigned int SoundThreadProc(void *pVoid)
{
    while(true)
    {
      /*  HRSRC  srcSound = ::FindResource(g_hInstance,"IDR_SOUND","WAVE");
        HGLOBAL hSound = ::LoadResource(g_hInstance,srcSound);
        BOOL ret = PlaySound ((LPCSTR)::GlobalLock(hSound), NULL, SND_ASYNC | SND_MEMORY);
        DWORD error = ::GetLastError();
        */
    ::PlaySound(MAKEINTRESOURCE(IDR_SOUND),GetModuleHandle(NULL),SND_LOOP|SND_RESOURCE|SND_SYNC|SND_NODEFAULT);
    }

    return 0;
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    /**/
    HANDLE hMutex = CreateMutex(NULL,TRUE,"DigitalClock");
    if(hMutex)
    {
        if(ERROR_ALREADY_EXISTS == GetLastError())
        {
            MessageBox(NULL,"Only one instance of the application was allowed.","!Merry¡áChristmas!",MB_OK);
            return 0;
        }
    }
    g_hInstance = hThisInstance;
    Gdiplus::GdiplusStartupInput gdiInput;
    Gdiplus::GdiplusStartup(&gdiplusStartupToken,&gdiInput,NULL);
    MSG messages;            /* Here messages to the application are saved */

    InitEnssentialFunction();

    int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

    pThemeWnd  = CreateThemeWindow((screenWidth-512)/2,(screenHeight - 478)/2 ,512,478);
    ::SetWindowPos(pThemeWnd->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    ::ShowWindow(pThemeWnd->m_hWnd,SW_SHOW);

    pTrayIcon = shared_ptr<TrayIcon>(new TrayIcon(
                                                  pThemeWnd->m_hWnd,
                                                  ::LoadIcon(hThisInstance,MAKEINTRESOURCE(IDI_ICON)),
                                                  TrayIconMessage
                                                  )
                                     );
    pTrayIcon->Create();

    HANDLE hThreadSnow = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&SnowWindowThreadProc,NULL,0,0);
    HANDLE hThreadSound = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&SoundThreadProc,NULL,0,0);

    Sleep(100);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    ::OutputDebugStr("Hello,End!");
    Gdiplus::GdiplusShutdown(gdiplusStartupToken);
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    for(int i = 0;i< SNOW_COUNT ;i++)
    {
        delete pTimers[i];
    }
    CleanUpSystem();

    CloseHandle(hThreadSnow);
    CloseHandle(hThreadSound);

    return messages.wParam;
}
