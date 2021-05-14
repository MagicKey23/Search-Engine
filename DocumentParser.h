

#ifndef SEARCH_ENGINE_DOCUMENTPARSER_H
#define SEARCH_ENGINE_DOCUMENTPARSER_H
#include <string>
#include <iostream>
#include <utility>
#include <dirent.h>
#include <fstream>
#include <stack>
#include <sstream>
#include "./scripts/json_parser/simdjson.h"
#include "./scripts/porter2_stemmer/porter2_stemmer.h"
#include "Document.h"
#include <sstream>
#include <algorithm>
#include <deque>
#include "./OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"

using namespace std;
using namespace simdjson;

class DocumentParser{

    public:
            explicit DocumentParser(const string& direct_name){
                reading_file(direct_name);
            }


            DocumentParser()= default;
            string StemmerAndRemoveStop(const string&);
            void parsing_json(const string&);
            int reading_file(const string&);
            bool is_file_json(const string&);
            int StringToWString(wstring &ws, const string &s);
            int WStringToString(std::string &s, std::wstring &ws);
            deque<Document*> getDocument();

    private:
            deque<Document*> documents;

};


#endif //SEARCH_ENGINE_DOCUMENTPARSER_H
