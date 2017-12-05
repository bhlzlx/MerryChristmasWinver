#pragma once
#include <gdiplus.h>
#include <iflib/archive.h>

namespace iflib
{
    struct AssetIStream: public IStream
    {
        iflib::IBlob * blob;
        
        bool Init( uint32_t _id, const char * _type )
        {
            auto b = iflib::GetDefArchive()->OpenAsset( _id, _type);
            if( b)
            {
                blob = b;
                return true;
            }
            blob = nullptr;
            return false;
        }
        
        HRESULT __stdcall Read( void  *pv,ULONG cb,ULONG *pcbRead)
        {
            static ULONG nRead;
            nRead = blob->Read(pv, cb);
            if( pcbRead )
                *pcbRead = nRead;
            if( cb > nRead)
                return S_FALSE;
            return S_OK;
        }
        
        HRESULT __stdcall Seek( LARGE_INTEGER  dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition )
        {
            blob->Seek((uint8_t)dwOrigin, dlibMove.QuadPart);
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
           // blob->Release();
            //delete this;
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
        
        STDMETHOD(Stat)(THIS_ STATSTG* stat,DWORD flag)
        {
           stat->cbSize.QuadPart = blob->Size();
           stat->type = STGTY_LOCKBYTES;
            return S_OK;;
        }
        STDMETHOD(Clone)(THIS_ LPSTREAM*)
        {
            return S_FALSE;
        }
    };

}

