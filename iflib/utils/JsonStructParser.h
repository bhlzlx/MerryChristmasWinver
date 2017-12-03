#pragma once

#include <array>
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <cjson/cJSON.h>

#define PRIVATE_ARGS_GLUE(x, y) x y

#define PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT(_1,_2,_3,_4,_5,_6,_7,_8,_9, _10, N, ...) N
#define PRIVATE_MACRO_VAR_ARGS_IMPL(args) PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT args
#define COUNT_MACRO_VAR_ARGS(...) PRIVATE_MACRO_VAR_ARGS_IMPL((__VA_ARGS__,10, 9,8,7,6,5,4,3,2,1,0))

#define PRIVATE_MACRO_CHOOSE_HELPER2(M,count)  M##count
#define PRIVATE_MACRO_CHOOSE_HELPER1(M,count) PRIVATE_MACRO_CHOOSE_HELPER2(M,count)
#define PRIVATE_MACRO_CHOOSE_HELPER(M,count)   PRIVATE_MACRO_CHOOSE_HELPER1(M,count)

#define INVOKE_VAR_MACRO(M,...) PRIVATE_ARGS_GLUE(PRIVATE_MACRO_CHOOSE_HELPER(M,COUNT_MACRO_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

#define DEFINE_JSON_PARSE_BASE_TYPE( TYPE, CJSON_TYPE, CJSON_VALUE ) \
template< class T = TYPE >\
static bool ParseBasicType( TYPE & _v, cJSON * _json)\
{\
if (!_json) return false; \
if (_json->type != CJSON_TYPE)  return false;\
	_v = (TYPE)_json->CJSON_VALUE; \
	return true; \
}\
\
template<class T = TYPE>\
static bool ParseBasicType(std::vector< TYPE >& _v, cJSON * _json)\
{\
if (!_json) return false; \
if(!cJSON_IsArray(_json)) return false;\
int n = cJSON_GetArraySize(_json); \
for (int i = 0; i < n; ++i)\
{\
auto item = cJSON_GetArrayItem(_json, i); \
if (_json->type != CJSON_TYPE)  return false;\
_v.push_back((TYPE)item->CJSON_VALUE); \
}\
return true; \
}\
template<class T = TYPE>static bool ParseObject( TYPE & _value, cJSON* _json) { return false; }\
template<class T = TYPE>static bool ParseObject( std::vector< TYPE >& _value, cJSON* _json) { return false; }\

#define DEFINE_JSON_PARSE_BOOL \
template<class T = bool>\
static bool ParseBasicType(bool& _v, cJSON * _json)\
{\
	if (!_json) return false;\
	if (_json->type == cJSON_True)\
	{\
		_v = true;\
	}\
	else\
	{\
		_v = false;\
	}\
	return true;\
}\
\
template<class T = bool>\
static bool ParseBasicType(std::vector<bool>& _v, cJSON * _json)\
{\
	if (!_json) return false;\
	int n = cJSON_GetArraySize(_json);\
	for (int i = 0; i < n; ++i)\
	{\
		auto item = cJSON_GetArrayItem(_json, i);\
		bool v;\
		if (item->type == cJSON_True)\
		{\
			v = true;\
		}\
		else\
		{\
			v = false;\
		}\
		_v.push_back(v);\
	}\
	return true;\
}\
template<class T = bool>static bool ParseObject(bool& _value, cJSON* _json) { return false; }\
template<class T = bool>static bool ParseObject(std::vector<bool>& _value, cJSON* _json) { return false; }\


#define DEFINE_JSON_SAVE_NUMBER(TYPE) \
template< class T = TYPE> static bool SaveObject( TYPE & _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\
template< class T = TYPE> static bool SaveObject(std::vector< TYPE >& _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\
\
template < class T = TYPE> static bool SaveBasicType(TYPE & _value, cJSON* _json, const char * _key)\
{\
	cJSON_AddNumberToObject(_json, _key, (double)_value);\
	return true;\
}\
\
template< class T = TYPE> static bool SaveBasicType(std::vector< TYPE >& _value, cJSON* _json, const char * _key)\
{\
	cJSON* arr = cJSON_CreateArray();\
	cJSON_AddItemToObject(_json, _key, arr);\
	for (auto& v : _value)\
	{\
		cJSON* item = cJSON_CreateNumber((double)v);\
		cJSON_AddItemToArray(_json, item);\
	}\
	return true;\
}\


#define DEFINE_JSON_SAVE_STRING \
template < class T = std::string> static bool SaveBasicType(std::string& _value, cJSON* _json, const char * _key)\
{\
	cJSON_AddStringToObject(_json, _key, _value.c_str());\
	return true;\
}\
template <class T = std::string> static bool SaveBasicType(std::vector< std::string >& _value, cJSON* _json, const char * _key)\
{\
	cJSON* arr = cJSON_CreateArray();\
	cJSON_AddItemToObject(_json, _key, arr);\
	for (auto& v : _value)\
	{\
		cJSON* item = cJSON_CreateString(v.c_str());\
		cJSON_AddItemToArray(_json, item);\
	}\
	return true;\
}\
template<class T = std::string> static bool SaveObject(std::string& _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\
template<class T = std::string> static bool SaveObject(std::vector< std::string >& _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\


#define DEFINE_JSON_SAVE_BOOL \
template <class T = bool> static bool SaveBasicType(bool& _value, cJSON* _json, const char * _key)\
{\
	cJSON_AddBoolToObject(_json, _key, _value);\
	return true;\
}\
template <class T = bool> static bool SaveBasicType(std::vector<bool>& _value, cJSON* _json, const char * _key)\
{\
	cJSON* arr = cJSON_CreateArray();\
	cJSON_AddItemToObject(_json, _key, arr);\
	for (auto&& v : _value)\
	{\
		cJSON* item = cJSON_CreateBool(v);\
		cJSON_AddItemToArray(_json, item);\
	}\
	return true;\
}\
template<class T = bool> static bool SaveObject(bool& _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\
template<class T = bool> static bool SaveObject(std::vector<bool>& _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\

#define DEFINE_JSON_SAVE_COMMON \
template <class T> static bool SaveObject(T& _value, cJSON* _json, const char * _key)\
{\
	if (!_json)\
		return false;\
	cJSON* item = cJSON_CreateObject();\
	cJSON_AddItemToObject(_json, _key, item);\
	T::X::Save(_value, _json);\
}\
template <class T> static bool SaveObject(std::vector< T >& _value, cJSON* _json, const char * _key)\
{\
	if (!_json)\
		return false;\
	int nItem = _value.size();\
	cJSON* arr = cJSON_CreateArray();\
	cJSON_AddItemToObject(_json, _key, arr);\
	for (int i = 0; i < nItem; ++i)\
	{\
		cJSON * item = cJSON_CreateObject();\
		T::X::Save(_value[i], item);\
		cJSON_AddItemToArray(arr, item);\
	}\
	return true;\
}\
template< class T> static bool SaveBasicType(T& _value, cJSON* _json, const char * _key)\
{\
	return false;\
}\


#define DEFINE_JSON_PARSE_COMMON \
template< class T>\
static bool ParseObject(T& _value, cJSON* _json)\
{\
	if (!_json) return false;\
	T::X::Parse(_value, _json);\
}\
\
template< class T >\
static bool ParseObject(std::vector<T>& _value, cJSON* _json)\
{\
	if (!_json) return false;\
\
	int nItem = cJSON_GetArraySize(_json);\
	for (int i = 0; i < nItem; ++i)\
	{\
		auto item = cJSON_GetArrayItem(_json, i);\
		T value;\
		T::X::Parse(value, item);\
		_value.push_back(value);\
	}\
	return true;\
}\
\
template< class T>\
static bool ParseBasicType(T& _value, cJSON* _json)\
{\
	return false;\
}\

#define DEFINE_JSON_PARSE_FUNC_BEGIN \
	template< class T >\
	static bool Parse(T& _value, cJSON* _json)\
	{\
		if (!_json) return false;\
		cJSON* item = nullptr;

#define DEFINE_JSON_PARSE_FUNC_END return true ;}

#define DEFINE_JSON_SAVE_FUNC_BEGIN\
	template<class T> static bool Save(T& _value, cJSON* _json)\
	{\
		if (!_json)\
			return false;\
		cJSON* item = _json;

#define DEFINE_JSON_SAVE_FUNC_END \
			return true;\
		}

#define DEFINE_JSON_X_BEGIN\
	struct X \
	{ \
		DEFINE_JSON_PARSE_COMMON \
		DEFINE_JSON_SAVE_COMMON \

#define DEFINE_JSON_X_END\
	DEFINE_JSON_PARSE_BASE_TYPE(double, cJSON_Number, valuedouble)\
	DEFINE_JSON_PARSE_BASE_TYPE(int, cJSON_Number, valuedouble)\
	DEFINE_JSON_PARSE_BASE_TYPE(float, cJSON_Number, valuedouble)\
	DEFINE_JSON_PARSE_BASE_TYPE(std::string, cJSON_String, valuestring)\
	DEFINE_JSON_PARSE_BOOL\
	DEFINE_JSON_SAVE_BOOL\
	DEFINE_JSON_SAVE_NUMBER(double)\
	DEFINE_JSON_SAVE_NUMBER(int)\
	DEFINE_JSON_SAVE_NUMBER(float)\
	DEFINE_JSON_SAVE_STRING\
	};



#define PITEM__( ITEM )\
item = cJSON_GetObjectItem(_json, #ITEM );\
if (IsBasicType(_value.ITEM))\
{\
	ParseBasicType(_value.ITEM, item);\
}\
else\
{\
	ParseObject(_value.ITEM, item);\
}

#define PITEMA( ITEM, ALIAS )\
item = cJSON_GetObjectItem(_json, #ALIAS );\
if (IsBasicType(_value.ITEM))\
{\
	ParseBasicType(_value.ITEM, item);\
}\
else\
{\
	ParseObject(_value.ITEM, item);\
}

#define SITEM__(ITEM) \
if (IsBasicType(_value.ITEM))\
{\
	SaveBasicType(_value.ITEM, item, #ITEM);\
}\
else\
{\
	SaveObject(_value.ITEM, item, #ITEM);\
}

#define SITEMA(ITEM, ALIAS) \
if (IsBasicType(_value.ITEM))\
{\
	SaveBasicType(_value.ITEM, item, #ALIAS);\
}\
else\
{\
	SaveObject(_value.ITEM, item, #ALIAS);\
}\

//#define XJSON_PARSE( ITEMS ) DEFINE_PARSER_HEADER ITEMS DEFINE_PARSER_TAIL

#define PITEMO(X) PITEM__(X)
#define PITEMS1( a ) PITEMO(a)
#define PITEMS2( a, b) PITEMS1(a) PITEMS1(b) 
#define PITEMS3( a, b, c ) PITEMS1(a) PITEMS2(b,c)
#define PITEMS4( a,b,c,d ) PITEMS1(a) PITEMS3(b,c,d)
#define PITEMS5( a,b,c,d,e )  PITEMS1(a) PITEMS4( b,c,d,e )
#define PITEMS6( a,b,c,d,e,f)  PITEMS1(a) PITEMS5( b,c,d,e,f)
#define PITEMS7( a,b,c,d,e,f,g)  PITEMS1(a) PITEMS6(b,c,d,e,f,g)
#define PITEMS8( a,b,c,d,e,f,g,h)  PITEMS1(a) PITEMS7(b,c,d,e,f,g,h)
#define PITEMS9( a,b,c,d,e,f,g,h,i)  PITEMS1(a) PITEMS8(b,c,d,e,f,g,h,i)
#define PITEMS10(a,b,c,d,e,f,g,h,i,j)  PITEMS1(a) PITEMS9(b,c,d,e,f,g,h,i,j)

#define SITEMO(X) SITEM__(X)
#define SITEMS1( a ) SITEMO(a)
#define SITEMS2( a, b) SITEMS1(a) SITEMS1(b) 
#define SITEMS3( a, b, c ) SITEMS1(a) SITEMS2(b,c)
#define SITEMS4( a,b,c,d ) SITEMS1(a) SITEMS3(b,c,d)
#define SITEMS5( a,b,c,d,e )  SITEMS1(a) SITEMS4( b,c,d,e )
#define SITEMS6( a,b,c,d,e,f)  SITEMS1(a) SITEMS5( b,c,d,e,f)
#define SITEMS7( a,b,c,d,e,f,g)  SITEMS1(a) SITEMS6(b,c,d,e,f,g)
#define SITEMS8( a,b,c,d,e,f,g,h)  SITEMS1(a) SITEMS7(b,c,d,e,f,g,h)
#define SITEMS9( a,b,c,d,e,f,g,h,i)  SITEMS1(a) SITEMS8(b,c,d,e,f,g,h,i)
#define SITEMS10(a,b,c,d,e,f,g,h,i,j)  SITEMS1(a) SITEMS9(b,c,d,e,f,g,h,i,j)

#define DEFINE_JSON_X_PARSE_ATTRS( ... ) INVOKE_VAR_MACRO(PITEMS,__VA_ARGS__)
#define DEFINE_JSON_X_SAVE_ATTRS( ... ) INVOKE_VAR_MACRO(SITEMS,__VA_ARGS__)
#define DEFINE_JSON_X_PARSE(...) DEFINE_JSON_PARSE_FUNC_BEGIN DEFINE_JSON_X_PARSE_ATTRS(__VA_ARGS__) DEFINE_JSON_PARSE_FUNC_END
#define DEFINE_JSON_X_SAVE(...) DEFINE_JSON_SAVE_FUNC_BEGIN DEFINE_JSON_X_SAVE_ATTRS(__VA_ARGS__) DEFINE_JSON_SAVE_FUNC_END

#define XJSON(...) DEFINE_JSON_X_BEGIN  DEFINE_JSON_X_PARSE(__VA_ARGS__)  DEFINE_JSON_X_SAVE(__VA_ARGS__)  DEFINE_JSON_X_END

std::array<std::type_index, 10> BasicTypes =
{
	typeid(double),
	typeid(float),
	typeid(std::string),
	typeid(bool),
	typeid(int),
	typeid(std::vector<double>),
	typeid(std::vector<float>),
	typeid(std::vector<std::string>),
	typeid(std::vector<bool>),
	typeid(std::vector<int>)
};

template< class T>
bool IsBasicType(T& _v)
{
	for (auto& type : BasicTypes)
	{
		if (type == typeid(_v))
		{
			return true;
		}
	}
	return false;
}

template<>
bool IsBasicType(double& _v) { return true; }