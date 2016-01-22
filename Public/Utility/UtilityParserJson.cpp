#include <UtilityDefine.h>
#include "UtilityParserJson.h"

using std::cout;
using std::endl;

UtilityParserJson::UtilityParserJson()
{
    m_jsRoot = NULL;
}

UtilityParserJson::~UtilityParserJson()
{

}

int UtilityParserJson::SetJson(cJSON * in_json) {
     m_jsRoot = in_json;
     if (m_jsRoot) {
        return 0;
    }
    return -1;
}

int UtilityParserJson::SetJson(const char * in_buff) {
    m_jsRoot = cJSON_Parse( in_buff );
    if (m_jsRoot) {
        return 0;
    }
    return -1;
}

int UtilityParserJson::ReadString(const char * in_name, char * out_data, int in_size)
{
    if ( m_jsRoot == NULL ) {
		return -1;
	}

	// json_data id
	cJSON * json_data = cJSON_GetObjectItem( m_jsRoot, in_name );
	if ( json_data ) {
        int json_len = 0;
	    if (json_data->type==cJSON_Number){
            char temp[32] = {0};
            sprintf( temp, "%d", json_data->valueint );
            json_len = strlen( temp );
            if ( json_len > in_size ) {
                return 0;
            }
            memcpy( out_data, temp, json_len + 1);
            return json_len;
	    }
	    else if (json_data->type==cJSON_String){
            json_len = strlen( json_data->valuestring );
            if ( json_len > in_size ) {
                return 0;
            }
            memcpy( out_data, json_data->valuestring, json_len + 1);
            return json_len;
	    }
	}
    return 0;
}

int UtilityParserJson::ReadDouble(const char * in_name, double & out_data)
{
   if ( m_jsRoot == NULL ) {
		return -1;
	}

	// json_data id
	cJSON * json_data = cJSON_GetObjectItem( m_jsRoot, in_name );
	if ( json_data ) {
	    if (json_data->type==cJSON_Number){
            out_data = json_data->valuedouble;
            return sizeof(double);
	    }
	    if (json_data->type==cJSON_String){
            out_data = strtod( json_data->valuestring, NULL );
            return sizeof(double);
	    }
	}
    return 0;
}

int UtilityParserJson::ReadInteger(const char * in_name, int & out_data)
{
   if ( m_jsRoot == NULL ) {
		return -1;
	}

	// json_data id
	cJSON * json_data = cJSON_GetObjectItem( m_jsRoot, in_name );
	if ( json_data ) {
	    if (json_data->type==cJSON_Number){
            out_data = json_data->valueint;
            return sizeof(double);
	    }
	    if (json_data->type==cJSON_String){
            out_data = atol( json_data->valuestring );
            return sizeof(double);
	    }
	}
    return 0;
}

int UtilityParserJson::ReadLongLong(const char * in_name, INT64 & out_data)
{
  if ( m_jsRoot == NULL ) {
		return -1;
	}

	// json_data id
	cJSON * json_data = cJSON_GetObjectItem( m_jsRoot, in_name );
	if ( json_data ) {
	    if (json_data->type==cJSON_Number){
            out_data = json_data->valueint;
            return sizeof(double);
	    }
	    if (json_data->type==cJSON_String){
            out_data = atol(json_data->valuestring );
            return sizeof(double);
	    }
	}
    return 0;
}


int UtilityParserJson::ReadJson(const char * in_name, UtilityParserJson & out_data)
{
   if ( m_jsRoot == NULL ) {
		return -1;
	}

	// json_data id
	cJSON * json_data = cJSON_GetObjectItem( m_jsRoot, in_name );
	if ( json_data ) {
        out_data.SetJson(json_data);
        return 0;
	}
    return -1;
}


int UtilityParserJson::ReadArrayJson( int in_index, UtilityParserJson & out_data )
{
   if ( m_jsRoot == NULL ) {
		return -1;
	}

	// json_data id
	cJSON * json_data = cJSON_GetArrayItem( m_jsRoot, in_index );
	if ( json_data ) {
        out_data.SetJson(json_data);
        return 0;
	}
    return -1;
}

int UtilityParserJson::GetArraySize()
{
    if ( m_jsRoot != NULL ) {
		return cJSON_GetArraySize(m_jsRoot);
	}
    return 0;
}
