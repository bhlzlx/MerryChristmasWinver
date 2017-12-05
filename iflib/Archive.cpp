#include "Archive.h"
#include <cassert>
#include <memory.h>

#include <windows.h>

namespace iflib
{
	struct MemBlob :public IBlob
	{
		std::string m_filepath;
		std::wstring m_wfilepath;
		// Ö¸Õë
		char*		m_pData;
		char*		m_pCurr;
		char*		m_pEnd;
		// ÈÝÁ¿
		size_t		m_nCapacity;

		MemBlob()
		{
			this->m_nCapacity = 0;
			this->m_pCurr = this->m_pData = this->m_pEnd = NULL;
		}

		MemBlob(const void * _pSrc, uint32_t & _nSize)
		{
			m_pData = (char*)malloc(_nSize + 1);
			memcpy(m_pData, _pSrc, _nSize);
			m_pData[_nSize] = 0x00;
			m_pCurr = m_pData;
			m_pEnd = m_pData + _nSize;
			m_nCapacity = _nSize;
		}

		MemBlob(const uint32_t& _nSize)
		{
			m_pData = (char *)malloc(_nSize + 1);
			memset(m_pData, 0, _nSize + 1);
			//m_pData[_nSize] = 0;
			m_pCurr = m_pData;
			m_pEnd = m_pData + _nSize;
			m_nCapacity = _nSize;
		}

		size_t Size()
		{
			return m_nCapacity;
		}

		size_t Seek(uint8_t _flag, ptrdiff_t _offset)
		{
			switch (_flag)
			{
			case SEEK_SET:
				m_pCurr = m_pData + _offset;
				break;
			case SEEK_CUR:
				m_pCurr += _offset;
				break;
			case SEEK_END:
				m_pCurr = m_pEnd + _offset;
				break;
			}

			if ((m_pEnd - m_pCurr) < 0)
			{
				m_pCurr = m_pEnd;
			}
			else if (m_pCurr < m_pData)
			{
				m_pCurr = m_pData;
			}

			return 1;
		}

		size_t Read( void* _pOut, uint32_t _nSize)
		{
			uint32_t sizeLeft = m_pEnd - m_pCurr;
			if (!sizeLeft)
			{
				return 0;
			}
			if (_nSize > sizeLeft)
			{
				_nSize = sizeLeft;
			}
			memcpy(_pOut, m_pCurr, _nSize);
			m_pCurr += _nSize;
			return _nSize;
		}

		size_t Resize(size_t _nSize)
		{
			assert(static_cast<size_t>(_nSize) > this->m_nCapacity);
			uint32_t currOffset = m_pCurr - m_pData;
			this->m_pData = (char *)realloc(m_pData, _nSize + 1);
			assert(m_pData);

			m_pData[_nSize] = 0x0;
			m_nCapacity = _nSize;
			m_pCurr = m_pData + currOffset;
			m_pEnd = m_pData + _nSize;

			return 0;
		}

		size_t Write(const void* _pIn, uint32_t _nSize)
		{
			size_t sizeLeft = m_pEnd - m_pCurr;
			while (sizeLeft < _nSize)
			{
				Resize(m_nCapacity * 2);
				sizeLeft = m_pEnd - m_pCurr;
			}
			memcpy(m_pCurr, _pIn, _nSize);
			m_pCurr += _nSize;
			return _nSize;
		}

		bool Eof()
		{
			if (m_pCurr >= m_pEnd)
			{
				return true;
			}
			return false;
		}

		size_t Tell()
		{
			return m_pCurr - m_pData;
		}

		char* GetCurr()
		{
			return m_pCurr;
		}

		char* GetBuffer()
		{
			return m_pData;
		}

		void Release()
		{
			free(m_pData);
			this->m_nCapacity = 0;
			this->m_pCurr = this->m_pData = this->m_pEnd = NULL;
			delete this;
		}

		const char * Filepath()
		{
			return m_filepath.c_str();
		}

		eBlobType Type()
		{
			return eMemBlob;
		}

		~MemBlob()
		{
			return;
		}
	};

	struct FileBlob :public IBlob
	{
		FILE * file;
		size_t length;
		std::string filepath;
		std::wstring wfilepath;
		// Í¨¹ý IBlob ¼Ì³Ð
		virtual size_t Size() override
		{
			return length;
		}
		virtual size_t Seek(uint8_t _flag, ptrdiff_t _offset) override
		{
			return fseek(file, _offset, _flag);
		}
		virtual size_t Read(void * _pOut, uint32_t _nSize) override
		{
			return fread(_pOut, 1, _nSize, file);
		}

		virtual size_t Tell()override
		{
			return ftell(file);
		}
		virtual size_t Write(const void * _pIn, uint32_t _nSize) override
		{
			size_t r = fwrite( _pIn, 1, _nSize, file );
			auto cur = ftell(file);
			fseek(file, 0, SEEK_SET);
			auto set = ftell(file);
			fseek(file, 0, SEEK_END);
			auto end = ftell(file);
			length = end - set;
			fseek(file, cur, SEEK_SET);
			return r;
		}
		virtual size_t Resize(size_t _nSize) override
		{
			return 0;
		}
		virtual bool Eof() override
		{
			return feof(file);
		}
		virtual char * GetCurr() override
		{
			return nullptr;
		}
		virtual char * GetBuffer() override
		{
			return nullptr;
		}
		virtual void Release() override
		{
			fclose(file);
			delete this;
		}
		virtual const char * Filepath() override
		{
			return filepath.c_str();
		}

		eBlobType Type()
		{
			return eStreamBlob;
		}
	};
    
    struct AssetBlob :public IBlob
	{
        const void *    memptr;
        const void *    memptrend;
        const void *    currptr;
        HANDLE          hRes;
        HGLOBAL         hGlobal;
		size_t          length;
        size_t          resid;
        std::string     resname;
        
		virtual size_t Size() override
		{
			return length;
		}
		virtual size_t Seek(uint8_t _flag, ptrdiff_t _offset) override
		{
            switch( _flag )
            {
            case SEEK_CUR:
            {
                currptr += _offset;
                if( currptr < memptr ) currptr = memptr;
                else if( currptr > memptrend) memptr = memptrend;
                break;
            }
            case SEEK_SET:
            {
                if( _offset < 0 ) currptr = memptr;
                else if( _offset > length) memptr = memptrend;
                else currptr = memptr + _offset;
                break;
            }
            case SEEK_END:
            {
                if( _offset > 0 ) currptr = memptrend;
                else if( _offset < -length) currptr = memptr;
                else currptr = memptrend + _offset;
                break;
            }
            }
            return 1;
		}
		virtual size_t Read(void * _pOut, uint32_t _nSize) override
		{
            ptrdiff_t left = (ptrdiff_t)memptrend - (ptrdiff_t)currptr;
            if( left > _nSize )
            {
                memcpy(_pOut, currptr, _nSize);
                currptr += _nSize;
                return _nSize;
            }
            else
            {
                memcpy(_pOut, currptr, left);
                currptr += left;
                return left;
            }            
		}

		virtual size_t Tell()override
		{
			return (ptrdiff_t)currptr - (ptrdiff_t)memptr;
		}
		virtual size_t Write(const void * _pIn, uint32_t _nSize) override
		{
			return 0;
		}
		virtual size_t Resize(size_t _nSize) override
		{
			return 0;
		}
		virtual bool Eof() override
		{
			return currptr>=memptrend;
		}
		virtual char * GetCurr() override
		{
			return nullptr;
		}
		virtual char * GetBuffer() override
		{
			return nullptr;
		}
        
		virtual void Release() override
		{
            //::UnlockResource ( hGlobal) ;
            ::FreeResource(hRes);
            delete this;
		}
		virtual const char * Filepath() override
		{
			return nullptr;
		}

		eBlobType Type()
		{
			return eAssetBlob;
		}
	};

	Archive::Archive()
	{

	}

	Archive::~Archive()
	{
	}

	std::string Archive::FormatFilePath(const std::string & _filepath)
	{
		int nSec = 0;
		std::string curSec;
		std::string fpath;
		const char * ptr = _filepath.c_str();
		while (*ptr != 0)
		{
			if (*ptr == '\\' || *ptr == '/')
			{
				if (curSec.length() > 0)
				{
					if (curSec == ".") {}
					else if (curSec == ".." && nSec >= 2)
					{
						int secleft = 2;
						while (!fpath.empty() && secleft == 0)
						{
							if (fpath.back() == '\\' || fpath.back() == '/')
							{
								--secleft;
							}
							fpath.pop_back();
						}
					}
					else
					{
						if( !fpath.empty() )
							fpath.push_back('/');
						fpath.append(curSec);
						++nSec;
					}
					curSec.clear();
				}
			}
			else
			{
				curSec.push_back( *ptr );
				if (*ptr == ':')
				{
					--nSec;
				}
			}
			++ptr;
		}
		if (curSec.length() > 0)
		{
			if (!fpath.empty())
				fpath.push_back('/');
			fpath.append(curSec);
		}
		return fpath;
	}
    
    IBlob * Archive::OpenAsset( uint32_t _id, const char * _type )
    {
        HANDLE res = ::FindResource(nullptr, MAKEINTRESOURCE(_id), _type);
        DWORD dwSize  = 0;
        if( res )
        {
            dwSize = ::SizeofResource(nullptr, (HRSRC)res);
            if( dwSize )
            {
                HGLOBAL hGlobal = ::LoadResource(nullptr, (HRSRC)res);
                LPVOID pBuffer = LockResource(hGlobal);
                if( pBuffer )
                {
                    AssetBlob * blob = new AssetBlob;
                    blob->hGlobal = hGlobal;
                    blob->hRes = res;
                    blob->length = dwSize;
                    blob->memptr = pBuffer;
                    blob->memptrend = pBuffer + dwSize;
                    blob->currptr = pBuffer;
                    return blob;
                }
            }
        }
        return nullptr;
    }

	IBlob * Archive::Open(const char * _fp, FileBlob::eBlobType _type)
	{
		std::string validPath = _fp;
		FILE * fp = nullptr;
		fp = fopen( _fp, "rb");
		if (!fp)
		{
			validPath = m_root + validPath;
			fp = fopen(validPath.c_str(), "rb");
		}		
		if (!fp)
		{
			return nullptr;
		}
		uint32_t set = ftell(fp);
		fseek(fp, 0, SEEK_END);
		uint32_t end = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		IBlob * blob = nullptr;
		if (_type == IBlob::eMemBlob)
		{
			MemBlob* memBlob = new MemBlob(end - set);
			memBlob->m_filepath = validPath;
			char * buffer = memBlob->GetBuffer();
			long long ret = fread(buffer, 1, memBlob->Size(), fp);
			blob = memBlob;
		}
		else
		{
			FileBlob* fileBlob = new FileBlob();
			fileBlob->length = end - set;
			fileBlob->filepath = validPath;
			fileBlob->file = fp;
			blob = fileBlob;
		}
		return blob;
	}

	bool Archive::Exist(const char * _fp)
	{
		std::string fullpath = m_root + _fp;
		FILE* fp = fopen(fullpath.c_str(), "rb");
		if (!fp)
		{
			return false;
		}
		fclose(fp);
		return true;
	}

	const std::string& Archive::GetRoot() const
	{
		return m_root;
	}

	void Archive::Init(const char * _root)
	{
		m_root = _root;
		m_root = Archive::FormatFilePath(m_root);
		m_root.push_back('/');
	}
	Archive * GetDefArchive()
	{
		static Archive arch;
		return &arch;
	}
}