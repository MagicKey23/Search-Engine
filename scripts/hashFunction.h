

#ifndef SEARCH_ENGINE_HASHFUNCTION_H
#define SEARCH_ENGINE_HASHFUNCTION_H
#include <string>
#include <string_view>
#include "json_parser/simdjson.h"

using namespace std;
class hashFunction {
public:
    hashFunction()= default;;
    unsigned int hash_function(const string &key);
    unsigned int hash_function(unsigned int key);

};


#endif //SEARCH_ENGINE_HASHFUNCTION_H
