#include "QueryEngine.h"



void QueryEngine::DisplayOption(){
    cout << "Please type in the Query Format to Search" << endl;
    cout << "Example:" << endl;
    cout << "  1.biology --- search all documents contained biology" << endl;
    cout << "  2.virus AUTHOR Donneley --- search all documents contained virus and author Donneley" << endl;
    cout << "  3.AND biology virus --- search all documents that contained biology and virus " << endl;
    cout << "  4.OR membrane barrier --- search for all documents that contained either membrane or barrier" << endl;
    cout << "  5.AND membrane barrier NOT mitochondria --- search all documents that contained membrane and barrier but not mitochondria" << endl;
    cout << "  6.membrance NOT mitochondria --- search all documents contained membrance but not mitochondria " << endl;
    cout << "Other Command" << endl;
    cout << "* q --- to clear history" << endl;
    cout << "* s --- show history" << endl;
}

void QueryEngine::prompt(){
    //Take User Input
    string userInput;
    getline(cin, userInput);
    if(userInput == "q" ){
        handler.ClearHistory();
    }else if(userInput == "s"){
        handler.ShowHistory();
    }else {
        stringstream s(userInput);
        string temp;

        while (getline(s, temp, ' ')) {
            //Lowercase
            std::transform(temp.begin(), temp.end(), temp.begin(),
                           [](unsigned char c) { return std::tolower(c); });

            userInputCut.push_back(temp);
        }

        if (userInputCut[0] == "or") {
            getInformation("or");
            handler.SearchOR(wordSearch, notList, authors);
            ClearAll();
        } else if (userInputCut[0] == "and") {
            getInformation("and");
            handler.SearchAND(wordSearch, notList, authors);
            ClearAll();
        } else {
            //No query command
            getInformation("default");
            handler.SearchDefault(wordSearch, notList, authors);
            ClearAll();
        }

    }
}



void QueryEngine::getInformation(string type){

    int stopPosition;
    int authorPosition;
    bool authorExist = false;
    bool notExist = false;

    if(type == "or" || type == "and") {
        for (int i = 1; i < userInputCut.size(); i++) {
            //search for position for author and not
            if (userInputCut[i] == "author") {
                authorPosition = i;
                authorExist = true;
            } else if (userInputCut[i] == "not") {
                stopPosition = i;
                notExist = true;
            } else if (!authorExist && !notExist) {
                Porter2Stemmer::stem(userInputCut[i]);
                wordSearch.push_back(userInputCut[i]);
            }
        }
    }else if(type == "default"){
        for (int i = 0; i < userInputCut.size(); i++) {
            //search for position for author and not
            if (userInputCut[i] == "author") {
                authorPosition = i;
                authorExist = true;
            } else if (userInputCut[i] == "not") {
                stopPosition = i;
                notExist = true;
            } else if (!authorExist && !notExist) {
                Porter2Stemmer::stem(userInputCut[i]);
                wordSearch.push_back(userInputCut[i]);
            }
        }
    }

    //Get Author List
    if(authorExist) {
        //get author word
        for (int i = authorPosition+1; i < userInputCut.size(); i++) {
            string data = userInputCut[i];
            std::transform(data.begin(), data.end(), data.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            data[0] = toupper(data[0]);
            authors.push_back(data);
        }
    }
    //Get NOT List
    if(notExist) {

        for (int i = stopPosition+1; i < userInputCut.size(); i++) {
            if(userInputCut[i] == "author") {
                break;
            }

            Porter2Stemmer::stem(userInputCut[i]);
            notList.push_back(userInputCut[i]);

        }
    }

}

void QueryEngine::ClearAll() {
    userInputCut.clear();
    wordSearch.clear();
    notList.clear();
    authors.clear();
}
