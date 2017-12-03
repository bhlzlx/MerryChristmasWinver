#include "JsonBlob.h"
#include <memory.h>

namespace iflib
{
	JsonBlob::JsonItemPtr JsonBlob::FindItem(const char * _keyPath)
	{
		JsonItemPtr itemPtr;
		const char * set = _keyPath;
		const char * it = _keyPath;
		cJSON * item = json;
		char keyI[64];
		char keyII[64];
		do
		{
			if (*it == '/')
			{
				set = ++it;
			}
			while ('/' != *it && 0 != *it)
			{
				++it;
			}
			memcpy(keyI, set, it - set);
			keyI[it - set] = 0;
			int index = 0;
			int ret = sscanf(keyI, "%[^[][%d]", keyII, &index);
			if (ret == 0)
			{
				return itemPtr;
			}
			if (ret == 1)
			{
				item = cJSON_GetObjectItem(item, keyI);
				if (!item)
				{
					return itemPtr;
				}
			}
			else if (ret == 2)
			{
				item = cJSON_GetObjectItem(item, keyII);
				if (!item) return itemPtr;
				item = cJSON_GetArrayItem(item, index);
				if (!item) return itemPtr;
			}
		} while (*it != 0);
		itemPtr.reset(new JsonItem);
		itemPtr->item = item;
		return itemPtr;
	}
	JsonBlob::JsonBlob()
	{
	}

	JsonBlob::~JsonBlob()
	{
	}

	JsonBlob::JsonBlobPtr JsonBlob::FromFile(IBlob * _blob)
	{
		const char * buff = _blob->GetBuffer();
		if (buff)
		{
			cJSON * json = cJSON_Parse(buff);
			if (json)
			{
				JsonBlobPtr ptr(new JsonBlob());
				ptr->json = json;
				return ptr;
			}
			return nullptr;
		}
		else
		{
			char * blobBuff = new char[_blob->Size() + 1];
			blobBuff[_blob->Size()] = 0;
			_blob->Read(blobBuff, _blob->Size());
			cJSON * json = cJSON_Parse(buff);
			delete[]blobBuff;
			if (json)
			{
				JsonBlobPtr ptr(new JsonBlob());
				ptr->json = json;
				return ptr;
			}
			return nullptr;
		}
	}

	JsonBlob::JsonBlobPtr JsonBlob::FromString(const char * _str)
	{
		cJSON * json = cJSON_Parse(_str);
		if (json)
		{
			JsonBlobPtr ptr(new JsonBlob());
			ptr->json = json;
			return ptr;
		}
		return nullptr;
	}



}