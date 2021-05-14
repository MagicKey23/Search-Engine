#include "./catch.hpp"
                 #include "DSString.h"
                 #include "DSStack.h"
                 #include "DSLinkedList.h"
                 #include "DSVector.h"
                 #include "AvlTree.h"
                 #include <string>
                 #include "./Hashtable.h"


    TEST_CASE("DSString functionality test", "[DSString]"){


        DSString myName("Kaney Nguyen");

        SECTION("Testing Name input and size")
        {
            REQUIRE(strcmp(myName.c_str(), "Kaney Nguyen") ==  0); //Test Passes
            REQUIRE(myName.getLength() == 12); //Test passes

        }
        SECTION("lower and upper case the string")

        {
            myName.upper();
            REQUIRE(strcmp(myName.c_str(), "KANEY NGUYEN") == 0); //Test Passes
            myName.lower();
            REQUIRE(strcmp(myName.c_str(), "kaney nguyen") == 0); //Test passes
        }


        SECTION("Substring test"){

            DSString s = myName.substring(4);


            REQUIRE(strcmp(s.c_str(), "y Nguyen") == 0);

            DSString a = myName.substring(2, 6);

            REQUIRE(strcmp(a.c_str(), "ney Ng") == 0);
        }

        DSVector<DSString> hello;
        hello.push_back("Sauce");
        hello.push_back("is");
        hello.push_back("sauce");
        DSString whatUp = "Sauce is sauce";
        DSVector<DSString> hi;
        whatUp.split(" ", hi);

        SECTION("String split test, return a  DSVector<DSString>"){
            REQUIRE(hi.getSize() == hello.getSize());
        }
        DSString keyTest = "Sauce is sauce";
        DSString key = "sauce";

        int i = keyTest.find(key);

        SECTION("FIND THE STRING"){
            REQUIRE(i == 9);
        }


    }

//DSS VECTOR

    TEST_CASE("DSVector test", "[DSVector]"){

        DSVector<DSString> words;

        words.push_back("hello");
        words.push_back("hi");
        words.push_back("hola");

        SECTION("Testing accessing vector") {
            REQUIRE(strcmp(words[0].c_str(), "hello") == 0);
            REQUIRE(strcmp(words[1].c_str(), "hi") == 0);
            REQUIRE(strcmp(words[2].c_str(), "hola") == 0);
        }
        SECTION("Test size and capacity"){
            REQUIRE(words.getSize() == 3 );
            REQUIRE(words.getCapacity() == 10);

        }

        SECTION("TESTING FRONT AND BACK"){
            REQUIRE(strcmp(words.back().c_str(), "hola" ) == 0);
            REQUIRE(strcmp(words.front().c_str(), "hello" ) == 0);

        }

        DSString item = words.pop_back();

        SECTION("TEST POP BACK"){
            REQUIRE(words.getSize() == 2);
            REQUIRE(strcmp(words.front().c_str(),"hello") == 0);
            REQUIRE(strcmp(item.c_str(), "hola") == 0);

        }


        DSString s("back");


//    words.resize();

        words.resize();
        words.insert(s, 0);



        SECTION("TEST INSERT"){
            REQUIRE(strcmp(words.back().c_str(), "hi") == 0);
            REQUIRE(strcmp(words.front().c_str(), "back") == 0);
        }


        words.swap(0,1);
        SECTION("TEST SWAP") {
            REQUIRE(strcmp(words.back().c_str(), "hi" ) == 0);
            REQUIRE(strcmp(words.front().c_str(), "hello" ) == 0);
        }
        // Assignment Operator
        DSVector<DSString> temp = words;

        SECTION("TEST ASSIGNMENT OPERATOR") {
            REQUIRE(strcmp(temp.back().c_str(), "hi" ) == 0);
            REQUIRE(strcmp(temp.front().c_str(), "hello" ) == 0);
        }

    }

//TEST DSSTACK
    TEST_CASE("DSStacktest", "[DSStack]"){

        DSStack<DSString> stacks;

        stacks.push_back("hello");
        stacks.push_back("hi");
        stacks.push_back("hola");

        SECTION("Testing accessing vector") {
            REQUIRE(strcmp(stacks[0].c_str(), "hello") == 0);
            REQUIRE(strcmp(stacks[1].c_str(), "hi") == 0);
            REQUIRE(strcmp(stacks[2].c_str(), "hola") == 0);
        }
        SECTION("Test size and capacity"){
            REQUIRE(stacks.getSize() == 3 );
            REQUIRE(stacks.getCapacity() == 10);
        }

        SECTION("TESTING PEEK"){
            REQUIRE(strcmp(stacks.peek().c_str(),"hola") == 0);
        }

        stacks.pop();

        SECTION("TESTING POP"){
            REQUIRE(strcmp(stacks.peek().c_str(),"hi") == 0);
        }

        DSStack<DSString> stacks2;
        SECTION("IsEmpty"){
            REQUIRE(stacks.empty() == false);
            REQUIRE(stacks2.empty() == true);
        }

    }


//TEST DSSLINKEDLIST

//
//    TEST_CASE("DLLinkedList Test", "[DLLinkedList]"){
//
//        DSString value = "Hello";
//        DSString value2 = "Hola";
//
//        DSLinkedList<DSString> list;
//
//        list.push_back(value);
//    list.push_back(value2);
//
//    for(auto it = list.begin(); it != list.end(); it++){
//        cout << *it << endl;
//    }
//
//
//    SECTION("Test front and back") {
//        REQUIRE(strcmp(list.front().c_str(), "Hello") == 0);
//        REQUIRE(strcmp(list.back().c_str(), "Hola") == 0);
//    }
//
//    SECTION("Get Size") {
//        REQUIRE(list.getSize() == 2);
//    }
//
//}

//AVL Tree

//TEST_CASE("AvlTree Test", "[AvlTree]"){
//    AvlTree<int> tree;
//
//
//    AvlNode<int>* node1 = new AvlNode<int>(1, Index(__cxx11::basic_string()));
//    AvlNode<int>* node2 = new AvlNode<int>(5, Index(__cxx11::basic_string()));
//    AvlNode<int>* node3 = new AvlNode<int>(3, Index(__cxx11::basic_string()));
//    AvlNode<int>* node4 = new AvlNode<int>(7, Index(__cxx11::basic_string()));
//    AvlNode<int>* node5 = new AvlNode<int>(10, Index(__cxx11::basic_string()));
//    AvlNode<int>* node6 = new AvlNode<int>(8, Index(__cxx11::basic_string()));
//
//
//    tree.root = tree.insert(tree.root, node1);
//    tree.root = tree.insert(tree.root, node2);
//    tree.root = tree.insert(tree.root, node3);
//    tree.root = tree.insert(tree.root, node4);
//    tree.root = tree.insert(tree.root, node5);
//    tree.root = tree.insert(tree.root, node6);
//    tree.printTree(tree.root, 3);
//
//    bool f = tree.search(tree.root, 4) != nullptr;
//    bool t =  tree.search(tree.root, 3) != nullptr;
//
//    SECTION("search") {
//        REQUIRE(f == 0);
//        REQUIRE(t == 1);
//    }
//}

//HASH TABLE

//
//TEST_CASE("HashTable Test", "[Hashtable]"){
//
//    double value;
//    Hashtable<string, double> hashtable;
//    HashtableItem<string, double> *item;
//    string key;
//    double result;
//    key = "Item 1";
//    value = 1;
//    hashtable.Add(key, value);
//    key = "Item 2";
//    value = 2;
//    hashtable.Add(key, value);
//    key = "Item 3";
//    value = 3;
//    hashtable.Add(key, value);
//    key = "Item 4";
//    value = 4;
//    hashtable.Add(key, value);
//
//    SECTION("Test Key Exist") {
//        REQUIRE( hashtable.KeyExist("Item 5") == 0);
//        REQUIRE( hashtable.KeyExist("Item 4")  == 1);
//    }
//
//    hashtable.ChangeValue("Item 4", 5);
//    result = hashtable.Search("Item 4");
//    cout <<"Result:" << result << endl;
//    item = hashtable.GetFirst();
//
//    while(item){
//        cout << "Key: " << item->Key() << " Value: " << item->Value() << endl;
//        item = hashtable.GetNext();
//    }
//
//    Hashtable<string, double> ht2;
//
//    ht2 = hashtable; // test the Hashtable assignment operator
//    item = ht2.GetNext();
//    cout << item->Key() << "=" << item->Value() << endl;
//    item = ht2.GetNext();
//    cout << item->Key() << "=" << item->Value() << endl;
//
//}