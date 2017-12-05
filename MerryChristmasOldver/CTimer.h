#ifndef CTIMER_H
#define CTIMER_H
#include "CPhantomWnd.h"
#include <windows.h>
#include <map>
#include <utility>
#include <unordered_map>

class CTimer;

typedef void (*CTIMER_CALLBACK)(CTimer *);

class CTimer
{
private:
    CTimer();
public:
    virtual ~CTimer();
    unsigned int GetElapse();
    UINT_PTR GetTimerID();
public:
    static CTimer* CreateTimer(unsigned int,CTIMER_CALLBACK);
    static void CALLBACK TimerProc ( HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTime);
protected:
    static HWND HelperWnd;
private:
    UINT_PTR                    m_TimernID;
    unsigned int                m_TimeElapse;
    CTIMER_CALLBACK             m_pFuncTimerProc;

    static UINT_PTR             TimernIDCounter;
    static std::unordered_map<unsigned __int64 ,size_t> TimerMap;
};

#endif // CTIMER_H
