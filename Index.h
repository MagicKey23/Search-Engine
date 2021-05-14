
#ifndef SEARCH_ENGINE_INDEX_H
#define SEARCH_ENGINE_INDEX_H
#include <vector>
#include <string>
#include "Document.h"
using namespace std;


class Index{
        public:
            vector<Document*> documents;



            Index(const string& word){
                this->word = word;
            }

            void addDocumentIndex(const Document* document){
                bool alreadyExist = false;
                for(int i = 0; i < documents.size(); i++){
                    if(documents[i] == document){
                        alreadyExist = true;
                    }

                }
                if(!alreadyExist){
                    documents.push_back(const_cast<Document *&&>(document));
                }

            }


            string getWord(){
                return word;
            }


            bool operator >(const Index &other){
                if(this->word > other.word){
                    return true;
                }
                return false;
            }
            bool operator <(const Index &other){
                if(this->word < other.word){
                    return true;
                }
                return false;
            }


            bool operator ==(const Index &other){
                if(this->word == other.word){
                    return true;
                }
                return false;
            }


            Index& operator =(const Index &other){
                if(this != &other){
                    this->word = other.word;
                    for(int i = 0; i < other.documents.size();i++){
                        this->documents[i] = other.documents[i];
                    }
                }

                return *this;
            }


        private:
        string word;

};

#endif //SEARCH_ENGINE_INDEX_H
