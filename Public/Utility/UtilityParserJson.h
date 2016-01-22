#ifndef _UtilityJson_H_
#define _UtilityJson_H_
#include <UtilityJson.h>

class UtilityParserJson
{
public:
    UtilityParserJson();
    virtual ~UtilityParserJson();

    int SetJson(cJSON * in_json);
    int SetJson(const char * in_buff);

protected:
    cJSON * m_jsRoot;

public:
    int ReadString(const char * in_name, char * out_data, int in_size);
    int ReadDouble(const char * in_name, double & out_data);
    int ReadInteger(const char * in_name, int & out_data);
    int ReadLongLong(const char * in_name, INT64 & out_data);

public:
    int ReadJson(const char * in_name, UtilityParserJson & out_data);
    int ReadArrayJson( int in_index, UtilityParserJson & out_data );
    int GetArraySize();
 };

#endif // _UtilityJson_H_
