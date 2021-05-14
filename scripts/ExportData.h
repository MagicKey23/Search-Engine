
#ifndef PA04_AMAZING_EXPORTDATA_H
#define PA04_AMAZING_EXPORTDATA_H
#include <fstream>
#include <iostream>

class ExportData{
public:
    ExportData(char* fileName, int value){
        extractFile(fileName, value);
    }


    ExportData(){}
    //MODIFY THIS
    void extractFile(char* fileName, int value){
        ofstream fileO(fileName);
        fileO << to_string(value) << endl;
        fileO.close();
    }

};


#endif //PA04_AMAZING_EXPORTDATA_H
