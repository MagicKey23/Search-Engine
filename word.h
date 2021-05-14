

#ifndef SEARCH_ENGINE_WORD_H
#define SEARCH_ENGINE_WORD_H
#include <string>
using namespace std;
    class word{
    public:
        word(){
            if(size == 0){
                empty = true;
            }
        }
        word(string text, double score, string title, string ID, string date, string au) : freq(score), title(title),paperID(ID), publish_date(date){
            if(size == 0){
                empty = true;
            }

        }



        void setFreq(double score){
            this->freq += score;
        }
        void addWord(string Word){
            words.push_back(Word);
            size++;
            updateCondition();
        }
        void setID(string ID){
            this->paperID = ID;
        }
        void setAuthor(vector<string> author){
            this->authors = author;
        }
        void setTitle(string t){
            this->title = t;
        }

        void setDate(string date){
            this->publish_date = date;
        }

        string getTitle(){
            return title;
        }

        string getText(int i){
            return words[i];
        }

        string getID(){
            return paperID;
        }
        string getAuthor(int i){
            return authors[i];
        }
        bool isEmpty(){
            return empty;
        }
        double getFreq(){
            return freq;
        }
        int getAuthorSize(){
            return authors.size();
        }
        int getSize(){
            return size;
        }
        string getDates(){
            return publish_date;
        }
        string getWord(int j){
            return words[j];
        }

        bool operator >(const word &other){
            if(freq > other.freq){
                return true;
            }
            return false;

        }
        bool operator <(const word &other){
            if (freq < other.freq){
                return true;
            }
            return false;
        }

        word& operator =(const word &other){
            if(this != &other){
                size = other.size;
                freq = other.freq;
                title = other.title;
                words = other.words;
                paperID = other.paperID;
                authors = other.authors;
                publish_date = other.publish_date;
                empty = other.empty;
            }

            return *this;
        }

    private:
        void updateCondition(){
            if(size > 0){
                empty = false;
            }else{
                empty = true;
            }
        }


        int size = 0;
        double freq = 0;
        string title;
        vector<string> words;
        string paperID;
        vector<string> authors;
        string publish_date;
        bool empty;

    };


#endif //SEARCH_ENGINE_WORD_H
