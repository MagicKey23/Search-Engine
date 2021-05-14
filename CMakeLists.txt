cmake_minimum_required(VERSION 3.15)
project(search_engine)
set(CMAKE_CXX_STANDARD 14)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "")
set (input02 "")
set (input03 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()

# Create the executable for sorting
add_executable(search_engine main.cpp  scripts/DSVector.h scripts/DSString.h scripts/DSString.cpp scripts/DSLinkedList.h scripts/DSStack.h scripts/test.cpp scripts/DLListNode.h scripts/ExportData.h ./scripts/AvlTree.h scripts/Hashtable.h ./scripts/catch.hpp
        DocumentParser.cpp DocumentParser.h Index.h IndexHandler.cpp IndexHandler.h QueryEngine.cpp QueryEngine.h scripts/json_parser/simdjson.cpp ./scripts/json_parser/simdjson.h scripts/Hashtable.h Document.h ./scripts/hashFunction.cpp ./scripts/hashFunction.h
        ./scripts/porter2_stemmer/porter2_stemmer.h scripts/porter2_stemmer/porter2_stemmer.cpp word.h ./OleanderStemmingLibrary/include/olestem/stemming/english_stem.h ./scripts/AvlTree.cpp)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")






