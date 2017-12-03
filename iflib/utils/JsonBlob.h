#pragma once
#include <memory>
#include "cjson/cJSON.h"
#include "../Archive.h"
#include <vector>

namespace iflib
{
	struct JsonBlob
	{
		struct JsonItem
		{
			cJSON * item;
			enum JsonType : int
			{
				JsonInvalid = 0,
				JsonFalse = 1 << 0,
				JsonTrue = 1 << 1,
				JsonNull = 1 << 2,
				JsonNumber = 1 << 3,
				JsonString = 1 << 4,
				JsonArray = 1<<5,
				JsonObject = 1 <<6,
				JsonRaw = 1 <<7,
			};

			struct Value
			{
				union
				{
					int32_t		vInt;
					float		vFloat;
					const char* vlpcString;
				};
			};

			JsonType Type() const
			{
				if (!item)
					return JsonInvalid;
				return (JsonType)item->type;
			}
		};

		typedef std::shared_ptr<JsonBlob> JsonBlobPtr;
		typedef std::shared_ptr<JsonItem> JsonItemPtr;
		cJSON * json;
		/*
		 FindNode("root/array[1]/player/name")
		*/
		JsonItemPtr FindItem(const char * _keyPath);

		JsonBlob();
		~JsonBlob();

		static JsonBlobPtr FromFile( IBlob * _blob );
		static JsonBlobPtr FromString(const char * _path);
	};





}