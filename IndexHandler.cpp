
#include "IndexHandler.h"

void IndexHandler::addWord(){

    for(int i = 0; i < documents.size(); i++){
        //Point at first Item in the table
        HashtableItem<string, int>* items = documents[i]->WordList.GetFirst();
        while(items){
            //Create Index
            string s = items->Key();
            Index newIndex(s);
            //Check if Index is in the tree
            bool condition = queryIndex.search(queryIndex.root, newIndex) == nullptr;
            //If the word hasn't in the tree yet, add it
            if(condition){
                newIndex.addDocumentIndex(documents[i]);
                AvlNode* newNode = new AvlNode(newIndex);
                queryIndex.root = queryIndex.insert(queryIndex.root, newNode);
            }else{
                //Add the document to the word
                //Get the location of the index
                AvlNode* s = queryIndex.search(queryIndex.root, newIndex);
                s->element.addDocumentIndex(documents[i]);
            }

            items = documents[i]->WordList.GetNext();
        }

    }


}

void IndexHandler::addAuthors(){
    //Go through document
    for(int i = 0; i < documents.size(); i++){
        //go through all author
        for(int j = 0; j < documents[i]->authors.size(); j++){

            Index author(documents[i]->getAuthor(j));
            bool condition = authors.search(authors.root, author) == nullptr;
            if(condition){
                author.addDocumentIndex(documents[i]);
                AvlNode* a = new AvlNode(author);
                authors.root = authors.insert(authors.root, a);
            }else{
                AvlNode* a = authors.search(authors.root, author);
                a->element.addDocumentIndex(documents[i]);
            }


        }
    }

}


void IndexHandler::SearchAND(const vector<string> &searchList, const vector<string> &notList, const vector<string> &authorList){
    word holder;
    bool materialExist = false;
    if(!authorList.empty()){
        for(int i = 0; i < authorList.size(); i++){
            AvlNode* s = authors.search(authors.root, authorList[i]);
            if(s != nullptr) {
                for (int j = 0; j < s->element.documents.size(); j++) {
                    holder = s->element.documents[j]->AuthorSearchAND(searchList, notList, authorList[i]);
                    if (!holder.isEmpty()) {
                        searchResult.push_back(holder);
                        materialExist = true;
                    }
                }
            }
        }
        if(materialExist) {
            Sort();
            PrintResult();
            AddToHistory(searchResult);
            Clear();
        }else{
            cout << "Not Found" << endl;
        }
    }else {

            AvlNode *s = queryIndex.search(queryIndex.root, searchList[0]);
            if(s != nullptr) {
                for (int j = 0; j < s->element.documents.size(); j++) {
                    holder = s->element.documents[j]->SearchAND(searchList[0], searchList, notList);
                    if (!holder.isEmpty()) {
                        searchResult.push_back(holder);
                         materialExist= true;
                    }
                }
            }

        if(materialExist) {
            Sort();
            PrintResult();
            AddToHistory(searchResult);
            Clear();
        }else {
            cout << "Not Found" << endl;
        }
    }
}


void IndexHandler::SearchOR(const vector<string> &searchList, const vector<string> &notList, const vector<string> &authorList){
    word holder;
    bool materialExist = false;
    if(!authorList.empty()){
        for(int i = 0; i < authorList.size(); i++){
            AvlNode* s = authors.search(authors.root, authorList[i]);
            if(s != nullptr){
                for(int j = 0; j < s->element.documents.size();j++){
                    holder =  s->element.documents[j]->AuthorSearchOR(searchList, notList, authorList[i]);
                    if(!holder.isEmpty()){
                        searchResult.push_back(holder);
                        materialExist = true;
                    }
                }
            }

        }
        if(materialExist) {
            Sort();
            PrintResult();
            AddToHistory(searchResult);
            Clear();
        }else{
            cout << "Not Found" << endl;
        }
    }else {
        for(int i = 0; i < searchList.size(); i++) {
            AvlNode *s = queryIndex.search(queryIndex.root, searchList[i]);
            if(s != nullptr){
                //make sure the word exist
                for(int j = 0; j < s->element.documents.size(); j++) {
                     holder = s->element.documents[j]->SearchOR(searchList[i], searchList, notList);
                    if(!holder.isEmpty()){
                        searchResult.push_back(holder);
                        materialExist = true;
                    }
                }

            }

        }
        if(materialExist) {
            Sort();
            PrintResult();
            AddToHistory(searchResult);
            Clear();
        }else {
            cout << "Not Found" << endl;
        }

    }
}




void IndexHandler::SearchDefault(const vector<string> &searchList, const vector<string> &notList, const vector<string> &authorList){
    word holder;
    bool materialExist = false;
    if(!authorList.empty()){
        for(int i = 0; i < authorList.size(); i++){
            AvlNode* s = authors.search(authors.root, authorList[i]);
            if(s != nullptr) {
                for(int j = 0; j < s->element.documents.size(); j++) {
                    holder = s->element.documents[j]->AuthorSearchDefault(searchList, notList, authorList[i]);
                    if (!holder.isEmpty()) {
                        searchResult.push_back(holder);
                        materialExist = true;
                    }

                }
            }
        }
        if(materialExist) {
            Sort();
            PrintResult();
            AddToHistory(searchResult);
            Clear();
        }else {
            cout << "Not Found" << endl;
        }

    }else {
        for(int i = 0; i < searchList.size(); i++) {
            AvlNode *s = queryIndex.search(queryIndex.root, searchList[i]);
            if( s != nullptr){
                for(int j = 0; j < s->element.documents.size(); j++) {
                    holder = s->element.documents[j]->SearchDefault(searchList[i], notList);
                    if (!holder.isEmpty()) {
                        searchResult.push_back(holder);
                        materialExist = true;
                    }
                }
            }
        }
        //Print
        if(materialExist) {
            Sort();
            PrintResult();
            AddToHistory(searchResult);
            Clear();
        }else {
            cout << "Not Found" << endl;
        }

    }
}



void IndexHandler::PrintResult(){

    for(int i = searchResult.size()-1; i >-1 ; i--) {
        cout << "Title: " << searchResult[i].getTitle() << endl;
        cout << "Author: ";
        for (int j = 0; j < searchResult[i].getAuthorSize(); j++) {
            cout << searchResult[i].getAuthor(j) << " ";
        }
        cout << endl;

        cout << "Paper ID: " << searchResult[i].getID() << endl;
        cout << "Words: ";
        for (int j = 0; j < searchResult[i].getSize(); j++) {
            cout << searchResult[i].getWord(j) << " ";

        }
        cout << endl;
        cout << "Score: " << searchResult[i].getFreq() << endl;
    }

}

void IndexHandler::Sort(){

    for(int i = 1; i < searchResult.size();i++){
        word key = searchResult[i];
        int j = i;
        while(j > 0 && searchResult[j-1] > key){
            searchResult[j] = searchResult[j-1];
            j = j-1;
        }
        searchResult[j] = key;
    }


}

void IndexHandler::printQueryIndex(){
    queryIndex.printTree(queryIndex.root, 4);
}
void IndexHandler::printAuthorIndex(){
    authors.printTree(authors.root, 4);
}

void IndexHandler::Clear(){
    searchResult.clear();
}
void IndexHandler::AddToHistory(vector<word> data){
    History.push_back(data);
}
void IndexHandler::ClearHistory(){
    History.clear();
}
void IndexHandler::ShowHistory(){
    for(int i =0; i < History.size();i++){
        for(int j = 0; j < History[i].size();j++){
            cout << History[i][j].getTitle() << endl;
        }
    }
}