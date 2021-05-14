#include "DocumentParser.h"
#include "OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"

int DocumentParser::reading_file(const string& directName){
    struct dirent *entry = nullptr; // A dirent object, which stores the contents of a file in a directory.
    DIR *dp = nullptr;              // A DIR object. Think of it as a 'directory iterator' -- it reads through all the files in a directory.

    // Set our 'dir' variable to the absolute directory path.
    string absolutePath = "/mnt/c/";
    string dir = absolutePath + directName;

    // This will be in the form "<directory>/<current_file>".
    string thisFilePath = "";

    dp = opendir(dir.c_str());  // Sets dp to the first file in the directory with path 'dir.'
    // Think of this as a 'begin()' function for a standard sequential container iterator (std::vector iterator, etc.).

    // If the DIR object (directory iterator) successfully opened a directory, iterate through all files using readdir() in a while loop.
    if (dp != nullptr) {
        // If readdir() executed successfully, perform an iteration of the while loop; otherwise, stop reading.
        while ((entry = readdir(dp))) {
            thisFilePath = dir + "/" + entry->d_name; // This will set 'thisFilePath' to the ABSOLUTE path of the FILE.
            // Often times, directories read include '.' (current directory) and '..' (previous directory).
            // In our implementation, we're ignoring them.
            if (thisFilePath.find_last_of(".") == thisFilePath.size() - 1 || thisFilePath.find_last_of("..") == thisFilePath.size() - 1 ) continue;
            // '.' - current directory. [C:]/<path_to_DirentDemo>/DirectoryToRead
            // '..' - [C:]/<path_to_DirentDemo>/

            //Check if file is a json

            if(is_file_json(thisFilePath)) {
                cout << thisFilePath << endl;
                parsing_json(thisFilePath);
            }
        }
    }
    else {
        cout << "DirentDemo - main(): Directory not found" << std::endl;
        return 1;
    }

    // Close the directory when done.
    closedir(dp);

    return 0;

}


void DocumentParser::parsing_json(const string& fileName){
    //Parser
    ondemand::parser parser;
    padded_string json = padded_string::load(fileName);
    auto doc = parser.iterate(json);
    auto* document = new Document();
    string_view data_str_view;
    string data;

    //Get Title
    data_str_view = doc["metadata"]["title"].get_string();

    document->setTitle(data_str_view.to_string());
    data = StemmerAndRemoveStop(data_str_view.to_string());
    document->addTitleWordList(data);


    //Get Paper ID

    data_str_view = doc["paper_id"].get_string();
    document->setPaperID(data_str_view.to_string());

    //Get Author Name
    for(auto authors : doc["metadata"]["authors"]){
        data_str_view = authors["last"].get_string();
        data = data_str_view.to_string();
        document->addAuthor(data);
    }


    // Get Abstract
    for(auto abstract : doc["abstract"]){
        data_str_view = abstract["text"].get_string();
        data = StemmerAndRemoveStop(data_str_view.to_string());
        document->addAbstract(data);
    }

    // Get Back Matter

    for(auto back_matter : doc["back_matter"]){
        data_str_view = back_matter["text"].get_string();
        data = StemmerAndRemoveStop(data_str_view.to_string());
        document->addBackMatter(data);
    }

    //Get Body Text
    for(auto bodyText : doc["body_text"]){
            data_str_view = bodyText["text"].get_string();
            data = StemmerAndRemoveStop(data_str_view.to_string());
            document->addBodyText(data);
    }


    document->AddAllWord();
    document->calFrequency();
    //document->readMetaData();
    documents.push_back(document);


}

bool DocumentParser::is_file_json(const string& fileName) {
    stack<string> directoryPath;
    stringstream ss(fileName);
    string token;
    //Make sure file is is a json by having ending json
    while (getline(ss, token, '.')) {
            directoryPath.push(token);
    }
    if(directoryPath.top() == "json"){
        return true;
    }
    return false;
}



string DocumentParser::StemmerAndRemoveStop(const string& words){

    stemming::english_stem<> StemEnglish;
    string read;
    string newString;
    vector<string> word_split;
    string temp;
    stringstream ss(words);

    ifstream fileO("/mnt/c/Users/knguyen/Desktop/data_structure_project/21s-srch-eng-python-is-lame/scripts/StopWord/stopwords.txt");

    if(!fileO.is_open()){
        cout << "Stop file was not open";
        return "Stop file was not open \n";
    }

    bool foundStopWord = false;


//Remove punctation
    while(getline(ss, temp, ' ')){
        string result;
        string result2;
        //remove punctation
        std::remove_copy_if(temp.begin(), temp.end(),
                            std::back_inserter(result), //Store output
                            std::ptr_fun<int, int>(&std::ispunct)
        );

        //Remove Digit
        std::remove_copy_if(result.begin(), result.end(),
                            std::back_inserter(result2), //Store output
                            std::ptr_fun<int, int>(&std::isdigit)
        );

        //Lower Case
        std::transform(result2.begin(), result2.end(), result2.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if(result2.size() > 3){
            word_split.push_back(result2);
        }


        }

//Check stop word and stemming

    for(int i = 0; i < word_split.size(); i++){
        while(getline(fileO, read)){

            if(read == word_split[i]){
                foundStopWord = true;
                break;
            }

        }
        if(!foundStopWord){
            string word = word_split[i];
            //Steming and Trim

                wstring ws;
                StringToWString(ws, word);
                StemEnglish(ws);
                WStringToString(word, ws);
                newString.append(word);
                newString.append(" ");

        }
        foundStopWord = false;
    }

    fileO.close();
    return newString;
}

deque<Document*> DocumentParser::getDocument(){
    return documents;
}


int DocumentParser::StringToWString(std::wstring &ws, const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());

    ws = wsTmp;

    return 0;
}

int DocumentParser::WStringToString(std::string &s, std::wstring &ws){
     string newString(ws.begin(),ws.end());
     s = newString;
     return 0;
}