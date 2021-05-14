
#ifndef INC_20F_AUTO_IDX_DSSTRING_H
#define INC_20F_AUTO_IDX_DSSTRING_H

#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <deque>
#include "DSVector.h"

using namespace std;
class DSString{
private:
    /**
     *  You will need to add some private data members here.
     *  This is up to your discretion.  However, we **strongly**
     *  encourage you to implement your string class as a wrapper
     *  for typical null-terminated c-strings.  In doing this, you
     *  may use c-sting functions in the methods in this class such
     *  as:
     *    * strlen(...)
     *    * strcpy(...)
     *    * strcmp(...)
     *    * strncpy(...)
     *    * strcat(...)
     *    * strncat(...)
     *
     *    A quick google search will return plenty of references on
     *    the c-string functions.
     **/


    //Member Variable
    typedef char String;
    String* string;
    int size = 0;

public:

    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString(){
        if(string != NULL) {
            string = nullptr;

        }
        delete[] string;

    };

    /**
     * Standard relational operators.  You are free to expand this
     * list if you'd like.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a String object
     *    one that takes a null-terminated c-string
     *
     **/
    DSString& operator= (const char*);
    DSString& operator=(const DSString&);
    DSString& operator+=(const DSString&);
    DSString operator+(const DSString&);
    bool operator== (const char*);
    bool operator== (const DSString&);
    bool operator> (const DSString&);
    char& operator[] (const int);

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength();


    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     **/
    DSString substring(int, int end = -1);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str();

    /**
     * Calculate the size of the string
     * cal_size()
     */
     void cal_Size();
    /** String split takes in an delimiter then return back a vector
       * @param delimiter, deque, number of time you want to split
       *
       */
   void split(const char*, DSVector<DSString>&,int times = -1);

    /**Find
     *  find character
     *  return the position
     *  @param key, start
     *  @return index if found otherwise -1
     */
     int find(DSString& key, int start = 0);
     int find(const char* key, int start = 0);
     bool findWord(DSString& key, int start = 0);

    /**Lower
     * Lower all characters in the string
     */
    void lower();
    /**Upper
     * Upper all characters in the string
     */
    void upper();
     /** Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/

     /** check if the character exist in the string
      * @param character
      * @return true if exist elese false
      */
      bool isExist(char*);
      bool isExist(DSString);

      void removePunctuation(char*);
      void removeChar(char);
      void concat(const char*);
      void concatChar(char);
      void clear();
      void changeValStringAt(int index, char val);
      void erase(int pos, int length);
    friend std::ostream& operator<< (std::ostream&, const DSString&);
    friend std::istream& operator>> (std::istream&, DSString&);

    //You are free to add more functionality to the class.  For example,
    //you may want to add a find(...) function that will search for a
    //string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.

};

#endif //INC_20F_AUTO_IDX_DSSTRING_H
