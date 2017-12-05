#include "CTimer.h"

UINT_PTR  CTimer::TimernIDCounter = 0;
std::unordered_map<unsigned __int64 ,size_t> CTimer::TimerMap = std::unordered_map<unsigned __int64 ,size_t>();
HWND CTimer::HelperWnd = NULL;

CTimer::CTimer()
{
    //ctor
    this->m_pFuncTimerProc = NULL;
    this->m_TimeElapse = 0;
    this->m_TimernID = -1;
}

CTimer * CTimer::CreateTimer(unsigned int elapse,CTIMER_CALLBACK callback)
{
    if(!CTimer::HelperWnd)
    {
        HelperWnd = CreateWindowEx (0,PHANTOM_WND_CLASS_NAME,"HelperWindow",WS_OVERLAPPEDWINDOW,0,0,0,0,HWND_DESKTOP,NULL,::GetModuleHandle(0),NULL);
    }
    CTimer * pTimer = new CTimer();
    pTimer->m_TimernID = CTimer::TimernIDCounter++;
    pTimer->m_TimeElapse = elapse;
    pTimer->m_pFuncTimerProc = callback;
    SetTimer(CTimer::HelperWnd,pTimer->m_TimernID,elapse,&CTimer::TimerProc);
    //CTimer::TimerMap.insert(make_pair(pTimer->m_TimernID,pTimer));
    TimerMap[pTimer->m_TimernID] = (size_t)pTimer;
    return pTimer;
}

CTimer::~CTimer()
{
    ::KillTimer(CTimer::HelperWnd,m_TimernID);
    TimerMap.erase(this->m_TimernID);
    if(TimerMap.empty())
    {
        DestroyWindow(CTimer::HelperWnd);
    }
}

void CALLBACK CTimer::TimerProc ( HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTime)
{
    if(TimerMap.size() == 0)
    {
        return;
    }
    size_t result = TimerMap[iTimerID];
    if(result)
    {
        CTimer *pTimer = (CTimer*)result;
        pTimer->m_pFuncTimerProc(pTimer);
    }
}

unsigned int CTimer::GetElapse()
{
    return this->m_TimeElapse;
}

UINT_PTR CTimer::GetTimerID()
{
    return this->m_TimernID;
}
