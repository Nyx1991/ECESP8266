#include "ECUtil.h"

void ECUtil::str_to_uint16(char *str, uint16_t *res)
{
    char *end;
    long val = strtol(str, &end, 10);
    if (end == str || *end != '\0' || val < 0 || val >= 0x10000) {
        res = new uint16_t(0);
    }
    else
    {
        *res = (uint16_t)val;
    }    
}

ECDictEntry* ECUtil::FindDictEntryByKey(ECDictEntry* _dict[], size_t _dictSize, String _key)
{
    ECDictEntry* _entry;    
    for (size_t i = 0; i < _dictSize; i++)
    {        
        _entry = _dict[i];
        if (String(_entry->key).equals(_key))
        {            
            return _entry;
        }
    }
    return nullptr;
}