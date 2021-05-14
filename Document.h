#ifndef SEARCH_ENGINE_DOCUMENT_H
#define SEARCH_ENGINE_DOCUMENT_H
#include <string>
#include "./scripts/Hashtable.h"
#include <vector>
#include <string>
#include "word.h"
#include "sstream"
#include <fstream>
#include <sstream>
using namespace std;
class Document{
public:
        Hashtable<string, int> WordList;
        vector<string> authors;
        //Hashtable<string, string> metadata;

        Document()= default;


//        int readMetaData() {
//
//
//            string temp;
//            string token;
//            fstream fin("/mnt/c/Users/knguyen/Desktop/data_structure_project/21s-srch-eng-python-is-lame/scripts/cs2341_data/metadata-cs2341.csv");
//
//            if(!fin.is_open())
//            {
//                cout << "read metadata error" << endl;
//                return -1;
//            }
//            getline(fin, temp);
//            while(getline(fin, temp)){
//                //Get title and publish date
//                vector<string> splitString;
//
//                stringstream s(temp);
//                while(getline(s, token, ',')){
//                    splitString.push_back(token);
//                }
//
//                metadata.Add(splitString[3], splitString[8]);
//            }
//            return 0;
//
//        }

        void addAbstract(const string& text){
            stringstream s(text);
            string temp;

            while(getline(s, temp,' ')){
                abstract.push_back(temp);
            }

        }



        void addBodyText(const string& text){
            stringstream s(text);
            string temp;

            while(getline(s, temp,' ')){
                bodyText.push_back(temp);
            }


        }

        void addAuthor(const string& text){
            stringstream s(text);
            string temp;

            while(getline(s, temp,' ')){
                authors.push_back(temp);
            }
        }

        void addBackMatter(const string& text){
            stringstream s(text);
            string temp;

            while(getline(s, temp,' ')){
                backMatter.push_back(temp);
            }

        }

        void addTitleWordList(const string& text){
            stringstream s(text);
            string temp;

            while(getline(s, temp,' ')){
                titleWordList.push_back(temp);
            }

        }

        void addToMetadata(){

        }


        void AddAllWord() {
            //Title
            if (!titleWordList.empty()) {
                for(int i = 0; i < titleWordList.size(); i++) {
                    WordList.Add(titleWordList[i], 0);
                }
            }
            //Abstract
            if (!abstract.empty()) {
                for (int i = 0; i < abstract.size(); i++) {
                    WordList.Add(abstract[i], 0);
                }
            }
            //body text
            if (!bodyText.empty()) {

                for(int i = 0; i < bodyText.size(); i++) {
                    WordList.Add(bodyText[i], 0);
                }


            }
            //back matter
            if (!backMatter.empty()) {
                for(int i = 0; i < backMatter.size(); i++) {
                    WordList.Add(backMatter[i], 0);
                }
            }



        }
        void calFrequency(){
            //Title score 5
            //Abstract score 4
            //Back Matter score 3
            //Body Text 2
            //Title
            for(int i = 0; i < titleWordList.size();i++){

                int freq = WordList.Search(titleWordList[i]);
                if(WordList.KeyExist(titleWordList[i])){
                    freq  += 5;
                    WordList.ChangeValue(titleWordList[i], freq);
                }

            }
            //Abstract
            for(int i = 0; i < abstract.size();i++){
                int freq = WordList.Search(abstract[i]);
                if(WordList.KeyExist(abstract[i])){
                    freq  += 4;
                    WordList.ChangeValue(abstract[i], freq);
                }
            }

            //Back Matter
            for(int i = 0; i < backMatter.size(); i++){
                int freq = WordList.Search(backMatter[i]);
                if(WordList.KeyExist(backMatter[i])){
                    freq  += 3;
                    WordList.ChangeValue(backMatter[i], freq);
                }
            }


            //body text
            for(int i = 0; i < bodyText.size();i++){
                int freq = WordList.Search(bodyText[i]);
                if(WordList.KeyExist(bodyText[i])){
                    freq  += 2;
                    WordList.ChangeValue(bodyText[i], freq);
                }
            }



        }

    //Set
        void setPaperID(const string& paperID){
            this->paperId = paperID;
        }
        void setTitle(const string& title){
            this->title = title;
        }

    //Get
        string getPaperID(){
            return paperId;
        }
        string getTitle(){
            return title;
        }

        //OverLoad Operator
        Document& operator=(const Document &other){
                if(this != &other){
                    this->setTitle(other.title);
                    this->setPaperID(other.paperId);
                    this->WordList = other.WordList;
                }

            return *this;
        }
        string getAuthor(int i){
            return authors[i];
        }
        double returnScore(string word){
           return WordList.Search(word);
        }

        word AuthorSearchOR(const vector<string>& searchList, const vector<string> &notList, const string &author){
            //check if there is not key word
            word holder;
            bool validator = false;
            vector<int> wordPosition;

            //check if there is list for not to show word
            if(!notList.empty()) {

                for(int i = 0; i < notList.size(); i++) {
                    //if word not to show not exist in the list then set validator true
                    if (WordList.KeyExist(notList[i])) {
                        validator = false;
                        //exit
                        break;
                    }
                    validator = true;
                }
                //if validator is true, continue to check if the word looking for iis in this document if not set false'
                if(validator) {
                    for (int i = 0; i < searchList.size(); i++) {
                        if (WordList.KeyExist(searchList[i])) {
                            wordPosition.push_back(i);
                        }

                    }


                }
                //If validator true, return the word


                if(!wordPosition.empty()){

                        //Push all the word into the vector
                        for(int i = 0; i < wordPosition.size();i++){
                            //add the word to the list
                            holder.setFreq(WordList.Search(searchList[i]));
                            holder.addWord(searchList[wordPosition[i]]);
                        }

                        holder.setTitle(title);
                        holder.setAuthor(authors);
                        //holder.setDate(metadata.Search(title));
                        holder.setID(getPaperID());

                }

            }else{
                //If not list isn't there
                for(int i = 0; i < searchList.size(); i++){
                    if(WordList.KeyExist(searchList[i])){
                        validator = true;
                        wordPosition.push_back(i);
                    }

                }

                if(validator){

                    for(int i = 0; i < wordPosition.size();i++){
                        holder.setFreq(WordList.Search(searchList[i]));
                        holder.addWord(searchList[wordPosition[i]]);
                    }

                    holder.setTitle(title);
                    holder.setAuthor(authors);
                    //holder.setDate(metadata.Search(title));
                    holder.setID(getPaperID());
                }


            }
            return holder;
        }



        word AuthorSearchAND(const vector<string>& searchList, const vector<string> &notList, const string &author){
            //check if there is not key word
            word holder;
            bool validator = false;
            vector<int> wordPosition;
            //check if there is list for not to show word
            if(!notList.empty()) {

                for(int i = 0; i < notList.size(); i++) {
                    //if word not to show not exist in the list then set validator true
                    if (WordList.KeyExist(notList[i])) {
                        validator = false;
                        //exit
                        break;
                    }
                    validator = true;
                }


                //if one of the word isn't exist in the list set false
                if(validator) {
                    for (int i = 0; i < searchList.size(); i++) {
                        if (!WordList.KeyExist(searchList[i])) {
                            validator = false;
                            break;
                        }
                        wordPosition.push_back(i);
                    }


                }
                //If validator true, return the word


                if(validator){


                    //Push all the word into the vector
                    for(int i = 0; i < wordPosition.size();i++){
                        //add the word to the list
                        holder.setFreq(WordList.Search(searchList[wordPosition[i]]));
                        holder.addWord(searchList[wordPosition[i]]);
                    }

                    holder.setTitle(title);
                    holder.setAuthor(authors);
                    //holder.setDate(metadata.Search(title));
                    holder.setID(getPaperID());

                }

            }else{
                //If not list isn't there
                for(int i = 0; i < searchList.size(); i++){
                    if(!WordList.KeyExist(searchList[i])){
                        validator = false;
                        break;
                    }
                        validator = true;
                        wordPosition.push_back(i);
                }
                if(validator){
                    for(int i = 0; i < wordPosition.size();i++){
                        holder.setFreq(WordList.Search(searchList[wordPosition[i]]));
                        holder.addWord(searchList[wordPosition[i]]);
                    }

                    holder.setTitle(title);
                    holder.setAuthor(authors);
                    //holder.setDate(metadata.Search(title));
                    holder.setID(getPaperID());
                }


            }
            return holder;


        }

        word AuthorSearchDefault(const vector<string>& searchList, const vector<string> &notList, const string &author){

            //check if there is not key word
            word holder;
            bool validator = false;
            vector<int> wordPosition;
            //check if there is list for not to show word
            if(!notList.empty()) {

                for(int i = 0; i < notList.size(); i++) {
                    //if word not to show not exist in the list then set validator true
                    if (WordList.KeyExist(notList[i])) {
                        validator = false;
                        //exit
                        break;
                    }
                    validator = true;
                }
                //if one of the word isn't exist in the list set false
                if(validator) {
                    for (int i = 0; i < searchList.size(); i++) {
                        if (WordList.KeyExist(searchList[i])) {
                            wordPosition.push_back(i);
                        }

                    }
                }
                //If validator true, return the word


                if(!wordPosition.empty()){


                    //Push all the word into the vector
                    for(int i = 0; i < wordPosition.size();i++){
                        //add the word to the list
                        holder.setFreq(WordList.Search(searchList[wordPosition[i]]));
                        holder.addWord(searchList[wordPosition[i]]);
                    }

                    holder.setTitle(title);
                    holder.setAuthor(authors);
                    //holder.setDate(metadata.Search(title));
                    holder.setID(getPaperID());

                }

            }else {
                //If not list isn't there
                for(int i = 0; i < searchList.size(); i++){
                    if(WordList.KeyExist(searchList[i])) {
                        wordPosition.push_back(i);
                    }
                }

                if(!wordPosition.empty()){
                    for(int i = 0; i < wordPosition.size();i++){
                        holder.setFreq(WordList.Search(searchList[wordPosition[i]]));
                        holder.addWord(searchList[wordPosition[i]]);
                    }

                    holder.setTitle(getTitle());
                    holder.setAuthor(authors);
                    //holder.setDate(metadata.Search(title));
                    holder.setID(getPaperID());
                }


            }

            return holder;



        }

        word SearchOR(const string& s, const vector<string>& searchList, const vector<string> &notList){
            word holder;
            bool validator = false;
            vector<int> wordPosition;

            if(!notList.empty()){
                for(int i = 0; i < notList.size();i++){
                    if(WordList.KeyExist(notList[i])){
                       validator = false;
                       break;
                    }
                    validator = true;
                }

                if(validator){
                    //if not keyword is not in the article
                   for(int i = 0; i < searchList.size();i++){
                       if(WordList.KeyExist(searchList[i])){
                           holder.addWord(searchList[i]);
                           holder.setFreq(WordList.Search(searchList[i]));
                       }
                   }

                    holder.setID(getPaperID());
                   // holder.setDate(metadata.Search(getTitle()));
                    holder.setTitle(getTitle());
                    holder.setAuthor(authors);

                }
            }else{
                for(int i = 0; i < searchList.size();i++){
                    if(WordList.KeyExist(searchList[i])){
                        holder.addWord(searchList[i]);
                        holder.setFreq(WordList.Search(searchList[i]));
                    }
                }

                holder.setID(getPaperID());
               // holder.setDate(metadata.Search(getTitle()));
                holder.setTitle(getTitle());
                holder.setAuthor(authors);
            }

            return holder;
        }
    word SearchAND(const string& s, const vector<string>& searchList, const vector<string> &notList){
        word holder;
        bool validator = false;
        vector<int> wordPosition;

            if(!notList.empty()){
            for(int i = 0; i < notList.size();i++){
                if(WordList.KeyExist(notList[i])){
                    validator = false;
                    break;
                }
                validator = true;
            }
            if(validator){
                //if pass the first check
                for(int i =0; i < searchList.size();i++){
                    if(!WordList.KeyExist(searchList[i])){
                        validator = false;
                        break;
                    }
                    wordPosition.push_back(i);
                }
                if(validator) {
                    for (int j = 0; j < wordPosition.size(); j++) {
                        holder.addWord(searchList[wordPosition[j]]);
                        holder.setFreq(WordList.Search(searchList[wordPosition[j]]));
                    }
                    holder.setID(getPaperID());
                    //holder.setDate(metadata.Search(getTitle()));
                    holder.setTitle(getTitle());
                    holder.setAuthor(authors);
                }

            }
            //Doesn't have exclusive list
        }else{

            for(int i  = 1; i < searchList.size();i++){
                if(!WordList.KeyExist(searchList[i])){
                    //check if it pass the and condition
                    validator = false;
                    break;
                }
                validator = true;
                wordPosition.push_back(i);
            }
            if(validator){
                for(int j = 0; j < wordPosition.size();j++){
                    holder.addWord(searchList[wordPosition[j]]);
                    holder.setFreq(WordList.Search(searchList[wordPosition[j]]));
                }
                holder.setID(getPaperID());
                //holder.setDate(metadata.Search(getTitle()));
                holder.setTitle(getTitle());
                holder.setAuthor(authors);
                holder.addWord(s);
            }



        }

        return holder;
    }


        word SearchDefault(const string& s, const vector<string> &notList){

            word holder;
            bool validator = false;
            vector<int> wordPosition;

            if(!notList.empty()){
                for(int i = 0; i < notList.size();i++){
                    if(WordList.KeyExist(notList[i])){
                        validator = false;
                        break;
                    }
                    validator = true;
                }
                    if(validator) {

                        if(WordList.KeyExist(s)) {
                            holder.addWord(s);
                            holder.setFreq(WordList.Search(s));
                            holder.setID(getPaperID());
                            //holder.setDate(metadata.Search(getTitle()));
                            holder.setTitle(getTitle());
                            holder.setAuthor(authors);
                        }
                    }
                //Doesn't have exclusive list
            }else{
                if(WordList.KeyExist(s)){
                    holder.addWord(s);
                    holder.setFreq(WordList.Search(s));
                    holder.setID(getPaperID());
                    //holder.setDate(metadata.Search(getTitle()));
                    holder.setTitle(getTitle());
                    holder.setAuthor(authors);
                }

            }
            return holder;
        }
        bool operator ==(const Document &other){
            if(title == other.title){
                return true;
            }
            return false;
        }
private:
    string title;
    string paperId;
    vector<string> abstract;
    vector<string> bodyText;
    vector<string> backMatter;
    vector<string> titleWordList;





};

#endif //SEARCH_ENGINE_DOCUMENT_H
