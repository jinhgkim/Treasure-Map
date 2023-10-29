#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);

    // my tests
    Stack<int> myStack;
    for (int i = 1; i <= 5; i++)
    {
        myStack.push(i);
    }
    myStack.pop();
    REQUIRE(myStack.myStack.n1 == 0);
    REQUIRE(myStack.myStack.n2 == 4);

    myStack.pop();
    myStack.pop();
    myStack.pop();
    REQUIRE(myStack.myStack.n1 == 0);
    REQUIRE(myStack.myStack.n2 == 1);

    myStack.pop();
    REQUIRE(myStack.myStack.n1 == 0);
    REQUIRE(myStack.myStack.n2 == 0);
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);

    // my tests
    Queue<int> myQueue;
    for (int i = 1; i <= 5;i++){
        myQueue.enqueue(i);
    }
    REQUIRE (myQueue.myQueue.n1 == 0);
    REQUIRE(myQueue.myQueue.n2 == 5);

    myQueue.dequeue();
    myQueue.dequeue();
    REQUIRE(myQueue.myQueue.n1 == 2); 
    REQUIRE(myQueue.myQueue.n2 == 5);

    myQueue.enqueue(6);
    REQUIRE(myQueue.myQueue.n1 == 2);
    REQUIRE(myQueue.myQueue.n2 == 6);

    myQueue.dequeue();
    REQUIRE(myQueue.myQueue.n1 == 0); // resize
    REQUIRE(myQueue.myQueue.n2 == 3);
}
 