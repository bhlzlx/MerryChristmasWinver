#if (JSON_TEMPLATE_STAGE == 0)
#undef DEFINE_JSON_STRUCT_BEGIN
#undef DEF_JSON_ITEM_BOOL
#undef DEF_JSON_ITEM_NUMBER
#undef DEF_JSON_ITEM_STRING
#undef DEF_JSON_ITEM_OBJECT
#undef DEF_JSON_ITEM_VECTOR_NUMBER
#undef DEF_JSON_ITEM_VECTOR_STRING
#undef DEF_JSON_ITEM_VECTOR_BOOL
#undef DEF_JSON_ITEM_VECTOR_OBJECT
#undef DEFINE_JSON_STRUCT_END
    #define DEFINE_JSON_STRUCT_BEGIN( CLASS ) struct CLASS \
    {\
        bool valid;\
        CLASS(){ valid = false; }\
        bool Init( cJSON * _json, const char ** _error );
    #define DEF_JSON_ITEM_BOOL(NAME) bool NAME;
    #define DEF_JSON_ITEM_NUMBER(NAME) double NAME;
    #define DEF_JSON_ITEM_STRING(NAME) std::string NAME;
    #define DEF_JSON_ITEM_OBJECT(TYPE, NAME ) TYPE NAME;
	#define DEF_JSON_ITEM_VECTOR_NUMBER( NAME ) std::vector<double> NAME;
	#define DEF_JSON_ITEM_VECTOR_STRING( NAME ) std::vector<std::string> NAME;
	#define DEF_JSON_ITEM_VECTOR_BOOL( NAME ) std::vector<bool> NAME;
	#define DEF_JSON_ITEM_VECTOR_OBJECT(TYPE, NAME ) std::vector<TYPE> NAME;
    #define DEFINE_JSON_STRUCT_END };
#endif

#if( JSON_TEMPLATE_STAGE == 1)
#undef DEFINE_JSON_STRUCT_BEGIN
#undef DEF_JSON_ITEM_BOOL
#undef DEF_JSON_ITEM_NUMBER
#undef DEF_JSON_ITEM_STRING
#undef DEF_JSON_ITEM_OBJECT
#undef DEF_JSON_ITEM_VECTOR_NUMBER
#undef DEF_JSON_ITEM_VECTOR_STRING
#undef DEF_JSON_ITEM_VECTOR_BOOL
#undef DEF_JSON_ITEM_VECTOR_OBJECT
#undef DEFINE_JSON_STRUCT_END

#define CREATE_PARSE_ERROR( ATTR, ERROR ) #ATTR" <-> "#ERROR

#define DEFINE_JSON_STRUCT_BEGIN( CLASS ) bool CLASS::Init( cJSON * _json, const char ** _error ){\
cJSON * item = nullptr;
#define DEF_JSON_ITEM_BOOL(NAME) item = cJSON_GetObjectItem( _json, #NAME ); if( !item ) { *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;} NAME = (item->type == cJSON_True);
#define DEF_JSON_ITEM_NUMBER(NAME) item = cJSON_GetObjectItem( _json, #NAME ); if( !item ) { *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;} NAME = item->valuedouble;
#define DEF_JSON_ITEM_STRING(NAME) item = cJSON_GetObjectItem( _json, #NAME ); if( !item ) { *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;} NAME = item->valuestring;
#define DEF_JSON_ITEM_OBJECT(TYPE, NAME ) \
item = cJSON_GetObjectItem( _json, #NAME );\
if( !item ) { *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;}\
TYPE obj;\
if( !obj.Init( item, _error )) return false;\
NAME = obj;

#define DEF_JSON_ITEM_VECTOR_NUMBER( NAME )\
item = cJSON_GetObjectItem( _json, #NAME );\
if(!item )\
{ *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;}\
if( !cJSON_IsArray(item)) { *_error = CREATE_PARSE_ERROR( NAME, NOT_AN_ARRAY ); return false;}\
int arrSz = cJSON_GetArraySize( item );\
for( int i = 0; i< arrSz; ++i ){\
	cJSON * arrItem = cJSON_GetArrayItem(item, i);\
	if( !cJSON_IsNumber(arrItem)) { *_error = CREATE_PARSE_ERROR( NAME, NOT_A_NUMBER ); return false;}\
	NAME.push_back(arrItem->valuenumber);\
}
#define DEF_JSON_ITEM_VECTOR_STRING( NAME )\
item = cJSON_GetObjectItem( _json, #NAME );\
if(!item )\
	{ *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;}\
if( !cJSON_IsArray(item)) { *_error = CREATE_PARSE_ERROR( NAME, NOT_AN_ARRAY ); return false;}\
int arrSz = cJSON_GetArraySize( item );\
for( int i = 0; i< arrSz; ++i ){\
	cJSON * arrItem = cJSON_GetArrayItem(item, i);\
	if( !cJSON_IsString(arrItem)) { *_error = CREATE_PARSE_ERROR( NAME, NOT_A_STRING ); return false;}\
	NAME.push_back(arrItem->valuestring);\
}
#define DEF_JSON_ITEM_VECTOR_BOOL( NAME )\
item = cJSON_GetObjectItem( _json, #NAME );\
if(!item )\
	{ *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;}\
if( !cJSON_IsArray(item)) { *_error = CREATE_PARSE_ERROR( NAME, NOT_AN_ARRAY ); return false;}\
int arrSz = cJSON_GetArraySize( item );\
for( int i = 0; i< arrSz; ++i ){\
	cJSON * arrItem = cJSON_GetArrayItem(item, i);\
	if( arrItem->type == cJSON_True ) NAME.push_back( true );\
	else if( arrItem->type == cJSON_False) NAME.push_back( false );\
	else { *_error = CREATE_PARSE_ERROR( NAME, NOT_BOOL_TYPE ); return false;}\
}

#define DEF_JSON_ITEM_VECTOR_OBJECT(TYPE, NAME )\
item = cJSON_GetObjectItem( _json, #NAME );\
if(!item )\
	{ *_error = CREATE_PARSE_ERROR( NAME, NOT_FONND ); return false;}\
if( !cJSON_IsArray(item)){ *_error = CREATE_PARSE_ERROR( NAME, NOT_AN_ARRAY ); return false;}\
int arrSz = cJSON_GetArraySize( item );\
for( int i = 0; i< arrSz; ++i ){\
	cJSON * arrItem = cJSON_GetArrayItem(item, i);\
	TYPE arrEle;\
	if( !arrEle.Init(arrItem, _error))\
		return false;\
	NAME.push_back(arrEle);\
}


#define DEFINE_JSON_STRUCT_END valid = true; return true; }
#endif