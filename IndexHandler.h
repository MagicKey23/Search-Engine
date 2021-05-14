
#include <deque>
#include "Document.h"
#include "scripts/AvlTree.h"
#include "Index.h"
#include "word.h"
#ifndef SEARCH_ENGINE_INDEXHANDLER_H
#define SEARCH_ENGINE_INDEXHANDLER_H


class IndexHandler {
public:
    IndexHandler(const deque<Document*>& list){
        //Assign the list
        documents = list;
    }
    IndexHandler() = default;

    void addWord();
    void addAuthors();

    void SearchOR(const vector<string> &, const vector<string> &, const vector<string> &);
    void SearchAND(const vector<string> &, const vector<string> &, const vector<string> &);
    void SearchDefault(const vector<string> &, const vector<string> &, const vector<string> &);

    void Sort();

    void PrintResult();
    void printQueryIndex();
    void printAuthorIndex();
    void AddToHistory(vector<word>);
    void ClearHistory();
    void ShowHistory();
    void Clear();
    deque<Document*> documents;
    AvlTree queryIndex;
    AvlTree authors;
    vector<word> searchResult;
    vector<vector<word>> History;
};


#endif //SEARCH_ENGINE_INDEXHANDLER_H
