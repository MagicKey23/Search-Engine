#define CATCH_CONFIG_RUNNER
#include "scripts/catch.hpp"
#include <iostream>
#include "./DocumentParser.h"
#include "./IndexHandler.h"
#include "./QueryEngine.h"
int main(int argc, char** argv) {

   DocumentParser parser(argv[1]);
   IndexHandler handler(parser.getDocument());
   handler.addWord();
   handler.addAuthors();

   //handler.printAuthorIndex();

   QueryEngine processor(handler);
   while(true) {
       processor.DisplayOption();
       processor.prompt();
   }


    return 0;
}
