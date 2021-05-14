#include "DSString.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;
DSString::DSString() {
    this->string= nullptr;
}


DSString::DSString(const char* userInput){
    //Create memory allocate string  then add nullptrptr at the end
    int len = strlen(userInput) + 1;
    string = new String[len];
    strcpy(string, userInput);
    string[strlen(string)] = '\0';
    //Count size
    cal_Size();

};

DSString::DSString(const DSString& oldString){
    if(this != &oldString || oldString.string != nullptr) {
        // Same process as previous but this time copy data from old String to this one
        int len = strlen(oldString.string) + 1;
//    delete[] string ;
        string = new String[len];
        strcpy(string, oldString.string);
        string[strlen(string)] = '\0';
        size = oldString.size;
    }
}


//Utilities


void DSString::cal_Size(){

    for(uint16_t i = 0; string[i] != '\0'; i++){
        size++;
    }

}
//
//bool DSString::isExist(char* target){
//    vector<DSString> split_result = this->split(" ");
//    //Get a vector of words
//
//   for(int i = 0; i < split_result.size(); i++){
//       if(strcmp(split_result[i].c_str(), target) == 0){
//           return true;
//       }
//   }
//   return false;
//}

//bool DSString::isExist(DSString s){
//    vector<DSString> split_result = this->split(" ");
//    //Get a vector of words
//
//    for(int i = 0; i < split_result.size(); i++){
//        if(strcmp(split_result[i].c_str(), s.c_str()) == 0){
//            return true;
//        }
//    }
//    return false;
//
//}

int DSString::find(DSString& key, int start) {

    if(start >= size){
        throw "STR_FIND: out of bound";
    }

    bool inConsecutive = false;
    int j = 0;
    int keySize = key.getLength();
    int index;
    for(int i = start; this->string[i] != '\0';i++){
        if(this->string[i] == key[j]){
            if(inConsecutive == false){
                index = i;
            }

            inConsecutive = true;

            if(j == keySize-1){
                return index;
            }

            j++;

        }else{
            inConsecutive = false;
            j = 0;
        }

    }

    return -1;
}


int DSString::find(const char* key, int start) {

    if(start >= size){
        throw "STR_FIND: out of bound";
    }

    bool inConsecutive = false;
    int j = 0;
    int keySize = strlen(key);
    int index;
    for(int i = start; this->string[i] != '\0';i++){
        if(this->string[i] == key[j]){
            if(inConsecutive == false){
                index = i;
            }

            inConsecutive = true;

            if(j == keySize-1){
                return index;
            }

            j++;

        }else{
            inConsecutive = false;
            j = 0;
        }

    }

    return -1;
}

bool DSString::findWord(DSString& key, int start){

    //hey

    if(start >= size){
        throw "STR_FIND: out of bound";
    }

    bool inConsecutive = false;
    int j = 0;
    int keySize = key.getLength();

    int index;

    for(int i = start; this->string[i] != '\0';i++){
        if(this->string[i] == key[j]){


            if(j == keySize-1){
                return true;
            }

            j++;

        }else{
            j = 0;

        }

    }
    return false;
}

void DSString::changeValStringAt(int index, char val){
    string[index] = val;
}

void DSString::split(const char* delimiter,DSVector<DSString>& myList, int time)
{
    if(!myList.empty()){
        myList.clear();
    }

    char* s = new char[1000];
    if(!myList.empty()){
        myList.clear();
    }
    int i = 0;
    // Returns first token

    char *token = strtok(string, delimiter);

    while (token != nullptr)
    {
        if(i == time){
          strcpy(s,myList.back().c_str());
          s[strlen(s)] = '\0';
          myList.pop_back();
        }else if((i > time) && (time != -1)){
          strcat(s, token);
        }
        else{
            myList.push_back(DSString(token));
        }
        token = strtok(nullptr, delimiter);
        if(time != -1) {i++;}
    }
    if((i > time) && (time != -1)) {
        myList.push_back(s);
    }
    delete[] s;

}
void DSString::lower(){

        for(int i = 0; string[i] !='\0'; i++){
            this->string[i] = tolower(string[i]);
        }

}
void DSString::upper(){
    for(int i = 0; string[i] !='\0'; i++){
        this->string[i] = toupper(string[i]);
    }
}


void DSString::concat(const char* token){
    String* src = new String[strlen(token) + 1];
    strcpy(src, token);
    src[strlen(src)] = '\0';
    strcat(string, src);
    size = strlen(string);
}

void DSString::concatChar(char token){

    if(string == nullptr){
        string = new String[2];
        size += 1;
        string[0] = token;
        string[size] = '\0';
    }else {

        String *newString = new String[getLength() + 1];
        strcpy(newString, string);
        string[getLength() - 1] = token;
        string[getLength()] = '\0';
        size = strlen(newString);
        delete string;
        string = newString;

    }
}

int DSString::getLength(){
    return this->size;
};

char* DSString::c_str() {
    return this->string;
}

void DSString::clear(){
    if(string != nullptr) {
        delete[] string;
        string = nullptr;
        size = 0;
    }
}

DSString DSString::substring(int start, int numChars) {
    if(isdigit(numChars) != 0){
        throw "ERROR substring function, must be INTEGER";
    }

    DSString cpy;

    if(start==size){
        return DSString("");
    }

    int len = getLength()-start + 1;
    if (numChars == -1) {
        String* newString = new String[len];
        int j = 0;
        for (int i = start;this->string[i] !='\0'; i++) {
            newString[j] = this->string[i];
            j++;
        }

        newString[j] = '\0';

        cpy = newString;
        delete[] newString;

    }else{
        String* newString = new String[numChars + 1];
        int j = 0;
        for (int i = start; i < start + numChars; i++) {
            newString[j] = this->string[i];
            // i= 1 2 3 4
            // j= 0 1 2 3
            j++;
        }
        newString[j] = '\0';
        cpy = newString;
        delete[] newString;
    }
    return cpy;
}

//Overload  Relational Operator
DSString& DSString::operator= (const char* newString){
    if(this->string != nullptr){
    delete[] string;
    this->size = 0;
    }

    string = new String[strlen(newString)+1];
    strcpy(string,newString);
    string[strlen(string)] = '\0';
    this->cal_Size();
    return *this;
}

DSString& DSString::operator= (const DSString& oldString){

    if(this == &oldString) {
        return *this;
    }else if(oldString.string == nullptr){
        if(string != nullptr) {
            string = nullptr;
            size = 0;
        }
    }
    else if(oldString.string != nullptr) {
        if(string != nullptr) {
            string = nullptr;
            this->size = 0;
        }


        string = new String[oldString.size];
        strcpy(string, oldString.string);
        string[strlen(string)] = '\0';
        this->size = oldString.size;
    }
    
    return *this;
}
DSString& DSString::operator+=(const DSString& oldString){
    this->string = strcat(this->string, oldString.string);
    this->size = this->size + oldString.size;
    return *this;
}

DSString DSString::operator+(const DSString& oldString){
    DSString newString = strcat(this->string, oldString.string);
    return newString;
}

//==
bool DSString::operator==(const char* otherStr){
    if(strcmp(this->c_str(), otherStr) == 0){
        return true;
    }

    return false;
}
//==
bool DSString::operator== (const DSString& otherStr){
    if(strcmp(this->c_str(), otherStr.string) == 0){
        return true;
    }

    return false;
}
//>
bool DSString::operator> (const DSString& otherStr){
    return this->size > otherStr.size;
}
char& DSString::operator[] (const int i){
    return string[i];
}

void DSString::removePunctuation(char* p){
    // input string
    if(nullptr == p)
        return;
    char* pDest = p;
    while(*p){
        if(!ispunct(*p)){
            *pDest++ = *p;

        }
        p++;
    }
    *pDest = '\0';

}

void DSString::removeChar(char garbage){
    char *src, *dst;
    for (src = dst = string; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}


//<<
std::ostream& operator<< (std::ostream& output, const DSString& self){
    output << self.string;
    return output;
}

std::istream& operator>> (std::istream& input, DSString& self){
    input >> self.string;
    self.cal_Size();
    return input;
}
