
#ifndef SEARCH_ENGINE_QUERYENGINE_H
#define SEARCH_ENGINE_QUERYENGINE_H
#include "IndexHandler.h"
#include "./scripts/porter2_stemmer/porter2_stemmer.h"

using namespace std;
class QueryEngine {
    public:
        QueryEngine() = default;
        QueryEngine(const IndexHandler &handler){
            this->handler = handler;
        }
        void DisplayOption();
        void prompt();
        void getInformation(string);
        void ClearAll();
    private:
    IndexHandler handler;
    vector<string> userInputCut;
    vector<string> wordSearch;
    vector<string> notList;
    vector<string> authors;
};


#endif //SEARCH_ENGINE_QUERYENGINE_H
