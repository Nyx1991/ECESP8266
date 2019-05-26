#ifndef ECUTIL_H
#define ECUTIL_H
#include <ESP8266WiFi.h>
#include "ECTypes.h"
#include <string>

class ECUtil
{
    public:
        static void str_to_uint16(char *str, uint16_t *res);
        static ECDictEntry* FindDictEntryByKey(ECDictEntry* _dict[], size_t _dictSize, String _key);
};

#endif