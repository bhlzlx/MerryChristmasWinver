#pragma once
#include <stdint.h>
#include <memory>
#include <string>

namespace iflib
{
	struct IBlob
	{
		enum eBlobType:uint8_t 
		{
			eMemBlob = 0,
			eStreamBlob = 1
		};
		virtual size_t 		Size() = 0;
		virtual size_t		Seek(uint8_t _flag, uint32_t _offset) = 0;
		virtual size_t		Read(void* _pOut, uint32_t _nSize) = 0;
		virtual size_t		Write(const void* _pIn, uint32_t _nSize) = 0;
		virtual size_t		Tell() = 0;
		/* return 0 if success, or return -1 if failed */
		virtual size_t 	Resize(size_t _nSize) = 0;
		virtual bool 		Eof() = 0;
		virtual char* 		GetCurr() = 0;
		virtual char* 		GetBuffer() = 0;
		virtual void 		Release() = 0;
		virtual const char * Filepath() = 0;
		virtual eBlobType Type() = 0;
		virtual ~IBlob() {};
	};

	class Archive
	{
	private:
		std::string m_root;
	public:
		Archive();
		IBlob * Open(const char * _fp, IBlob::eBlobType _type = IBlob::eMemBlob);
		bool Exist(const char * _fp);
		const std::string& GetRoot() const;
		void Init( const char * _root);
		~Archive();
		static std::string FormatFilePath(const std::string& _filepath);
	};

	Archive * GetDefArchive();

	inline std::string GetAssertPath()
	{
		return "/asset/";
	}

}



