#include <windows.h> 
#include <gdiplus.h>
#include <iflib/utils/JsonStructParser.h>
#include <iflib/utils/JsonBlob.h>
#include "resource.h"

struct ResIStream: public IStream
{
    iflib::IBlob * blob;
    HRESULT __stdcall Read( void  *pv,ULONG cb,ULONG *pcbRead)
    {
        ULONG v = blob->Read(pv, cb);
        *pcbRead = v;
        if( cb > v )
            return S_FALSE;
        return S_OK;
    }
    HRESULT __stdcall Seek( LARGE_INTEGER  dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition )
    {
        blob->Seek((uint8_t)dwOrigin, dlibMove.LowPart);
        return S_OK;
    }
    
    STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*)
    {
        return S_OK;
    }
	STDMETHOD_(ULONG,AddRef)(THIS)
    {
        return 0;
    }
	STDMETHOD_(ULONG,Release)(THIS)
    {
        blob->Release();
        delete this;
    }
	STDMETHOD(Write)(THIS_ void const*,ULONG,ULONG*)
    {
        return S_FALSE;
    }
	STDMETHOD(SetSize)(THIS_ ULARGE_INTEGER)
    {
        return S_FALSE;
    }
	STDMETHOD(CopyTo)(THIS_ IStream*,ULARGE_INTEGER,ULARGE_INTEGER*,ULARGE_INTEGER*)
    {
        return S_FALSE;
    }
	STDMETHOD(Commit)(THIS_ DWORD)
    {
        return S_FALSE;
    }
	STDMETHOD(Revert)(THIS) 
    {
        return S_FALSE;
    }
	STDMETHOD(LockRegion)(THIS_ ULARGE_INTEGER,ULARGE_INTEGER,DWORD)
    {
        return S_OK;
    }
	STDMETHOD(UnlockRegion)(THIS_ ULARGE_INTEGER,ULARGE_INTEGER,DWORD)
    {
        return S_OK;
    }
	STDMETHOD(Stat)(THIS_ STATSTG*,DWORD)
    {
        return S_OK;
    }
	STDMETHOD(Clone)(THIS_ LPSTREAM*)
    {
        return S_FALSE;
    }
};

ResIStream resIStream;

class Image;
struct PngWindowLoadConfig
{
    std::string image;
    XJSON(image)
    ;
};
 
/*  GDI+ startup token */ 
ULONG_PTR gdiplusStartupToken; 
 
/*  Declare Windows procedure  */ 
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM); 
 
// UpdateLayeredWindow Defination 
typedef BOOL(*UPDATELAYEREDWINDOWFUNCTION)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD); 
 
/*  Make the class name into a global variable  */ 
char szClassName[ ] = "PNGDialog"; 
 
int WINAPI WinMain (HINSTANCE hThisInstance, 
                     HINSTANCE hPrevInstance, 
                     LPSTR lpszArgument, 
                     int nCmdShow) 
{ 
 
   // HANDLE hImage = ::FindResource(nullptr,MAKEINTRESOURCE(IDR_PNG_BRAND),"PNG");
    
    iflib::Archive * arch = iflib::GetDefArchive();
    iflib::IBlob * blob = arch->OpenAsset(IDR_PNG_BRAND, "PNG");
    resIStream.blob = blob;
    /**/ 
    Gdiplus::GdiplusStartupInput gdiInput; 
    Gdiplus::GdiplusStartup(&gdiplusStartupToken,&gdiInput,NULL); 
    /**/ 
    HWND hwnd;               /* This is the handle for our window */ 
    MSG messages;            /* Here messages to the application are saved */ 
    WNDCLASSEX wincl;        /* Data structure for the windowclass */ 
 
    /* The Window structure */ 
    wincl.hInstance = hThisInstance; 
    wincl.lpszClassName = szClassName;//+-69+ 
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */ 
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */ 
    wincl.cbSize = sizeof (WNDCLASSEX); 
 
    /* Use default icon and mouse-pointer */ 
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION); 
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION); 
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW); 
    wincl.lpszMenuName = NULL;                 /* No menu */ 
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */ 
    wincl.cbWndExtra = 0;                      /* structure or the window instance */ 
    /* Use Windows's default colour as the background of the window */ 
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND; 
 
    /* Register the window class, and if it fails quit the program */ 
    if (!RegisterClassEx (&wincl)) 
        return 0; 
 
    /* The class is registered, let's create the program*/ 
    hwnd = CreateWindowEx ( 
           WS_EX_LAYERED|WS_EX_TOPMOST|WS_EX_TOOLWINDOW,                   /* Extended possibilites for variation */ 
           szClassName,         /* Classname */ 
           "PNGDialog Example Application",       /* Title Text */ 
           WS_OVERLAPPEDWINDOW, /* default window */ 
           CW_USEDEFAULT,       /* Windows decides the position */ 
           CW_USEDEFAULT,       /* where the window ends up on the screen */ 
           20,                 /* The programs width */ 
           20,                 /* and height in pixels */ 
           HWND_DESKTOP,        /* The window is a child-window to desktop */ 
           NULL,                /* No menu */ 
           hThisInstance,       /* Program Instance handler */ 
           NULL                 /* No Window Creation data */ 
           ); 
 
    /* Make the window visible on the screen */ 
    ShowWindow (hwnd, nCmdShow); 
    LONG style = ::GetWindowLong(hwnd,GWL_STYLE); 
    if(style&WS_CAPTION) 
        style^=WS_CAPTION; 
    if(style&WS_THICKFRAME) 
        style^=WS_THICKFRAME; 
    if(style&WS_SYSMENU) 
        style^=WS_SYSMENU; 
    ::SetWindowLong(hwnd,GWL_STYLE,style); 
 
    style = ::GetWindowLong(hwnd,GWL_EXSTYLE); 
    if(style&WS_EX_APPWINDOW) 
        style^=WS_EX_APPWINDOW; 
    ::SetWindowLong(hwnd,GWL_EXSTYLE,style); 
 
    /******************************************** 
    *   step 1. 
    *   Using Gdiplus to load the image 
    ********************************************/ 
    RECT wndRect; 
    ::GetWindowRect(hwnd,&wndRect); 
    SIZE wndSize = {wndRect.right-wndRect.left,wndRect.bottom-wndRect.top}; 
    HDC hdc = ::GetDC(hwnd); 
    HDC memDC = ::CreateCompatibleDC(hdc); 
    HBITMAP memBitmap = ::CreateCompatibleBitmap(hdc,wndSize.cx,wndSize.cy); 
    ::SelectObject(memDC,memBitmap); 
    
  /*  auto arch = iflib::GetDefArchive();
    auto blob = arch->Open("configure.json");
    auto jsonBlob = iflib::JsonBlob::FromFile(blob);
    iflib::JsonBlob::JsonItemPtr item = jsonBlob->FindItem("mc");
    PngWindowLoadConfig conf;
    PngWindowLoadConfig::X::Parse( conf, item->item);
    */
    
   Gdiplus::Image image( &resIStream ); 
   //Gdiplus::Image
  // Gdiplus::Image image(L"");
    Gdiplus::Graphics graphics(memDC); 
    //graphics.DrawImage(&image,0,0,wndSize.cx,wndSize.cy); 
    /******************************************** 
    *   step 2. 
    *   Get "UpdateLayeredWindow" function's 
    *   proc address. 
    ********************************************/ 
    HMODULE hUser32 = ::LoadLibrary("User32.dll"); 
    if(!hUser32) 
    { 
        return FALSE; 
    } 
    UPDATELAYEREDWINDOWFUNCTION UpdateLayeredWindow = (UPDATELAYEREDWINDOWFUNCTION)::GetProcAddress(hUser32,"UpdateLayeredWindow"); 
    if(!UpdateLayeredWindow) 
    { 
        return FALSE; 
    } 
    // get screen dc 
    HDC screenDC = GetDC(NULL); 
    POINT ptSrc = {0,0}; 
 
    /********************************************* 
    *   step 3. 
    *   Use UpdateLayeredWindow to Draw the Window 
    * 
    *********************************************/ 
    BLENDFUNCTION blendFunction; 
    blendFunction.AlphaFormat = AC_SRC_ALPHA; 
    blendFunction.BlendFlags = 0; 
    blendFunction.BlendOp = AC_SRC_OVER; 
    blendFunction.SourceConstantAlpha = 255; 
    UpdateLayeredWindow(hwnd,screenDC,&ptSrc,&wndSize,memDC,&ptSrc,0,&blendFunction,2); 
 
    ::DeleteDC(memDC); 
    ::DeleteObject(memBitmap); 
 
    /* Run the message loop. It will run until GetMessage() returns 0 */ 
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
 
 
/*  This function is called by the Windows function DispatchMessage()  */ 
 
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    switch (message)                  /* handle the messages */ 
    { 
        case WM_DESTROY: 
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */ 
            break; 
        case WM_LBUTTONDOWN: 
            //::SendMessage(hwnd,WM_HIT) 
            break; 
        default:                      /* for messages that we don't deal with */ 
            return DefWindowProc (hwnd, message, wParam, lParam); 
    } 
    return 0; 
} 