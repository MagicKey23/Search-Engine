#include "hashFunction.h"

#define TABLE_SIZE 1000003
unsigned int hashFunction::hash_function(const string &key)
{
    unsigned int h = 0;
    unsigned int o = 31415;
    const unsigned int t = 27183;
    const char *k = key.c_str();
    while (*k)
    {
        h = (o * h + *k++) % TABLE_SIZE;
        o = o * t % (TABLE_SIZE - 1);
    }
    return h;
}

unsigned int hashFunction::hash_function(const unsigned int key)
{
    // make sure table size is actually (TABLE_SIZE+1) (more about this below)
    return(key & TABLE_SIZE);
}

