/// @file tests.cpp
/// @Riya Patel 
/// CS 251 Project4: testing priority queue using Catch2.x framework
/// @date October 20, 2023

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

// This is a basic test case example with sections.
// Requires: <no oter functions>
TEST_CASE("Test 0: The Null Test") 
{
    // In this section we test Scenario 1.
    SECTION("Test 0: Empty Truths")
    {
        REQUIRE(true == true);
    }

    // In this section we test Scenario 2.
    SECTION("Test 0: Empty Falsehoods")
    {
        REQUIRE(false == false);
    }
}

//This is a basic test case testing prqueue operations - constructor, enqueue, size
//Requires <enqueue(), size(), toString()>
TEST_CASE("PriorityQueue operations"){

    prqueue<int> pq;

    //testing constructors of different prqueue like int, string
    SECTION("Construct empty priority queue"){
        REQUIRE(pq.size() == 0);
    }

    SECTION("Construct empty string priority queue"){
        prqueue<string> strQueue;
        REQUIRE(strQueue.size() == 0);
    }

    SECTION("Empty priority queue"){
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }   
    
    //testing enqueue and size using int
    SECTION("Enqueue singal element"){
        pq.enqueue(1,1);
        REQUIRE(pq.size() == 1);
    }

    SECTION("Enqueue multiple elements"){
        pq.enqueue(5,2);
        REQUIRE(pq.size() == 1);

        pq.enqueue(10,2);
        REQUIRE(pq.size() == 2);

        pq.enqueue(15,5);
        REQUIRE(pq.size() == 3);
    }

    prqueue<string> strQueue;

    //testing enqueue, toString and size using a string prqueue
    SECTION("Empty string priority queue"){
        REQUIRE(strQueue.size() == 0);
        REQUIRE(strQueue.toString() == "");
    }

    SECTION("Construct empty priority queue"){
        prqueue<int> pq;
        REQUIRE(pq.size() == 0);
    }

    SECTION("Enqueue single element"){ 
        pq.enqueue(5, 1);
        REQUIRE(pq.size() == 1);
    }
   
    SECTION("Enqueue multiple string element"){
        strQueue.enqueue("Kim", 1);
        REQUIRE(strQueue.size() == 1);

        strQueue.enqueue("Bob", 2);
        REQUIRE(strQueue.size() == 2);

        strQueue.enqueue("Charlie", 5);
        REQUIRE(strQueue.size() == 3);
    }

    //enqueuing and clearing
    SECTION("Enqueue and clear priority queue"){
        pq.enqueue(10, 3);
        pq.enqueue(20, 1);
        pq.enqueue(30, 4);
        pq.enqueue(40, 2);

        REQUIRE(pq.size() == 4);
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }
} 

//This is a test case for toString
//Requires <toString(), enqueue(), dequeue(), size()>
TEST_CASE("PriorityQueue toString()"){

    prqueue<string> pq;

    //testing an empty, singular, multiple queue
    SECTION("toString empty queue"){
        string expectedOutput = "";
        REQUIRE(pq.toString() == expectedOutput);
    }

    SECTION("toString singular element") {
        pq.enqueue("Ben", 1);
        string expectedOutput = "1 value: Ben\n";
        REQUIRE(pq.toString() == expectedOutput);
    }

    SECTION("toString multiple elements"){
        pq.enqueue("Ben", 1);
        pq.enqueue("Jen", 2);
        pq.enqueue("Sven", 2);
        pq.enqueue("Gwen", 3);
        REQUIRE(pq.size() == 4);
        string expectedOutput = "1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n";
        REQUIRE(pq.toString() == expectedOutput);
    }

    //testing ascending and descending order
    SECTION("toString with ascending priority order"){
        prqueue<int> pq1;
        pq1.enqueue(5, 1);
        pq1.enqueue(10, 2);
        pq1.enqueue(15, 3);
        string expectedOutput = "1 value: 5\n2 value: 10\n3 value: 15\n";
        REQUIRE(pq1.toString() == expectedOutput);
        REQUIRE(pq1.size() == 3);
    }

    SECTION("toString with descending priority order"){
        prqueue<int> descendingPQ;
        descendingPQ.enqueue(15, 3);
        descendingPQ.enqueue(10, 2);
        descendingPQ.enqueue(5, 1);
        string expectedOutput = "1 value: 5\n2 value: 10\n3 value: 15\n";
        REQUIRE(descendingPQ.toString() == expectedOutput);
        REQUIRE(descendingPQ.size() == 3);
        descendingPQ.clear();
        REQUIRE(descendingPQ.size() == 0);
    }

    SECTION("toString with ascending priority order after dequeue"){
        prqueue<int> pq1;
        pq1.enqueue(5, 10);
        pq1.enqueue(10, 20);
        pq1.enqueue(15, 30);

        REQUIRE(pq1.size() == 3);
        int dequeued = pq1.dequeue();
        REQUIRE(dequeued == 5);
        string expectedOutputAfterDequeue = "20 value: 10\n30 value: 15\n";
        REQUIRE(pq1.toString() == expectedOutputAfterDequeue);
        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("toString with descending priority order after dequeue"){
        prqueue<int> descendingPQ;
        descendingPQ.enqueue(15, 30);
        descendingPQ.enqueue(10, 20);
        descendingPQ.enqueue(5, 10);
        REQUIRE(descendingPQ.size() == 3);
        int dequeued = descendingPQ.dequeue();
        REQUIRE(dequeued == 5);
        string expectedOutputAfterDequeue = "20 value: 10\n30 value: 15\n";
        REQUIRE(descendingPQ.toString() == expectedOutputAfterDequeue);
        descendingPQ.clear();
        REQUIRE(pq.size() == 0);
    }

    //testing enqueing and dequeuing together
    SECTION("toString after mixing enqueuing and dequeuing different types"){
        prqueue<string> strQueue;
        strQueue.enqueue("Apple", 1);
        strQueue.enqueue("Banana", 2);
        strQueue.enqueue("Cherry", 3);
        REQUIRE(strQueue.size() == 3);
        string dequeue = strQueue.dequeue();
        prqueue<int> intQueue;
        intQueue.enqueue(5, 4);
        intQueue.enqueue(10, 5);
        intQueue.enqueue(15, 6);
        intQueue.dequeue();

        string expectedOutput = "2 value: Banana\n3 value: Cherry\n";
        REQUIRE(strQueue.toString() == expectedOutput);
        string expectedOutput2 = "5 value: 10\n6 value: 15\n";
        REQUIRE(intQueue.toString() == expectedOutput2);
        intQueue.clear();
        REQUIRE(intQueue.size() == 0);
    }   
}

//This is a test case for assignment operator
//Requires <size(), enqueue(), toString(), 
TEST_CASE("PriorityQueue assignmentOperator"){
    prqueue<int> pq1, pq2;

    //testing an empty priority queue
    SECTION("Assign an empty prqueue to another empty prqueue"){
        pq1 = pq2;
        REQUIRE(pq1.size() == 0);
    }

    SECTION("Assign an empty prqueue to a non-empty prqueue"){
        pq1.enqueue(5, 2);
        pq1.enqueue(10, 4);

        pq1 = pq2;

        REQUIRE(pq1.size() == 0);
    }

    SECTION("Assign an initialized prqueue to an empty prqueue"){
        pq1.enqueue(2,4);
        pq2 = pq1;

        REQUIRE(pq1.size() == pq2.size());
        REQUIRE(pq1.toString() == pq2.toString());
    }

    //testing with multiple assignments
    SECTION("Assign an initialized prequeue with multiple queue"){
        pq1.enqueue(10, 2);
        pq1.enqueue(8, 4);
        pq1.enqueue(6, 6);
        pq1.enqueue(4, 8);
        pq1.enqueue(2, 10);
        REQUIRE(pq1.size() == 5);
        pq2 = pq1;
        REQUIRE(pq1.size() == pq2.size());
        REQUIRE(pq1.toString() == pq2.toString());

        pq2.clear();
        REQUIRE(pq2.size() == 0);
    }

    SECTION("toString with stringStream"){
        pq1.enqueue(5, 1);
        pq1.enqueue(10,2);
        pq1.enqueue(15,3);
        REQUIRE(pq1.size() == 3);
        stringstream expectedOutput;

        expectedOutput << "1 value: 5\n2 value: 10\n3 value: 15\n";

        REQUIRE(pq1.toString() == expectedOutput.str());
    }

    SECTION("Multiple assignments and with dequeue"){
        pq1.enqueue(2, 1);
        pq1.enqueue(4, 2);
        pq1.enqueue(6, 3);
        REQUIRE(pq1.size() == 3);;
        pq2 = pq1;

        pq2.dequeue();
        pq2.enqueue(8, 4);
        REQUIRE(pq1.size() == 3);
        pq1 = pq2;

        REQUIRE(pq1.toString() == "2 value: 4\n3 value: 6\n4 value: 8\n");
        pq1.clear();
        pq2.clear();
        REQUIRE(pq1.size() == pq2.size());
    }

    //testing ascending and descending priority queue
    SECTION("toString with descending priority order"){
        prqueue<int> descendingPQ;
        descendingPQ.enqueue(15, 3);
        descendingPQ.enqueue(10, 2);
        descendingPQ.enqueue(5, 1);

        string expectedOutputAfterDequeue = "1 value: 5\n2 value: 10\n3 value: 15\n";
        REQUIRE(descendingPQ.toString() == expectedOutputAfterDequeue);
    }

    SECTION("Multiple consecutive assignments and dequeue"){
        pq1.enqueue(5, 2);
        pq1.enqueue(10, 4);
        pq1.enqueue(15, 6);

        pq2 = pq1;

        pq2.dequeue();
        pq2.enqueue(20, 1);

        pq1 = pq2;
        pq2.dequeue();
        pq2.enqueue(25, 3);

        pq1 = pq2;

        REQUIRE(pq1.size() == 3);
        REQUIRE(pq1.toString() == pq2.toString());
    }

    SECTION("Assign an initialized prqueue with multiple elements to another prqueue"){
        pq1.enqueue(10, 2);
        pq1.enqueue(8, 4);
        pq1.enqueue(6, 6);
        pq1.enqueue(4, 8);
        pq1.enqueue(2, 10);
        REQUIRE(pq1.size() == 5);

        pq2 = pq1;

        REQUIRE(pq1.size() == pq2.size());
        REQUIRE(pq1.toString() == pq2.toString());

        pq2.clear();
        REQUIRE(pq2.size() == 0);
    }
}

//This is a test case for begin and next
//Requires <begin(), next(), enqueue(), clear(), size()>
TEST_CASE("Begin and Next function"){
    prqueue<int> pq;
    stringstream output;
    int value, priority;

    //testing begin with an empty, singular and multiple priority queue 
    SECTION("Testing begin with an empty queue"){
        pq.begin();
        bool hasNext = pq.next(value, priority);

        REQUIRE(pq.size() == 0);
        REQUIRE(hasNext == false);
    }

    SECTION("Testing begin with a single element in the queue"){
        pq.enqueue(10, 1);
        pq.enqueue(12,2);
        pq.enqueue(14,3);

        pq.begin();
        pq.next(value, priority);
        REQUIRE(pq.size() == 3);
        REQUIRE(value == 10);
    }

    SECTION("Testing begin with multiple enqueue"){
        pq.enqueue(10,3);
        pq.enqueue(20,1);
        pq.enqueue(30,2);
        REQUIRE(pq.size() == 3);

        pq.begin();
        while(pq.next(value, priority)){
            output << "Priority: " << priority << ", Value: " << value << "\n";
        }
        REQUIRE(output.str() == "Priority: 1, Value: 20\nPriority: 2, Value: 30\n");
        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Testing begin with multiple elements in descending order"){
        pq.enqueue(30,3);
        pq.enqueue(20,2);
        pq.enqueue(10,1);

        pq.begin();
        pq.next(value, priority);
        REQUIRE(value == 10);
        REQUIRE(pq.size() == 3);
        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    //testing identical priority
    SECTION("Testing begin with idential priority values"){
        pq.enqueue(10,2);
        pq.enqueue(20,2);
        pq.enqueue(30,2);

        pq.begin();
        pq.next(value, priority);
        REQUIRE(pq.size() == 3);
        REQUIRE(value == 10);
    }

    SECTION("Testing next with a single element in the queue"){
        pq.enqueue(10,1);
        pq.begin();

        bool hasNext = pq.next(value, priority);

        REQUIRE(pq.size() == 1);
        REQUIRE(hasNext == false);
        REQUIRE(value == 10);
        REQUIRE(priority == 1);

        hasNext = pq.next(value, priority);
        REQUIRE(hasNext == false);
    }

    //testing ascending ordr
    SECTION("Testing next with multiple elements in ascending order"){
        pq.enqueue(5, 1);
        pq.enqueue(10, 2);
        pq.enqueue(15, 3);

        REQUIRE(pq.size() == 3);
        pq.begin();
        int expectedValues[] = {5, 10, 15};
        int expectedPriorities[] = {1, 2, 3};
        int index = 0;
        while(pq.next(value, priority)){
            REQUIRE(value == expectedValues[index]);
            REQUIRE(priority == expectedPriorities[index]);
            index++;
        }

        bool hasNext = pq.next(value, priority);
        REQUIRE(hasNext == false);

        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Testing next with identical elements"){
        pq.enqueue(10, 2);
        pq.enqueue(20, 2);
        pq.enqueue(30, 2);

        pq.begin();
        int expectedValues[] = {10, 20, 30};
        int expectedPriorities[] = {2, 2, 2};
        int index = 0;
        while (pq.next(value, priority)) {
            REQUIRE(value == expectedValues[index]);
            REQUIRE(priority == expectedPriorities[index]);
            index++;
        }

        bool hasNext = pq.next(value, priority);
        REQUIRE(hasNext == false);

        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Testing next with a moderate number of elements"){
        for(int i = 1; i <= 10; ++i){
            pq.enqueue(i * 10, i);
        }

        pq.begin();
        int expectedValues[10], expectedPriorities[10];
        for(int i = 0; i < 10; ++i){
            expectedValues[i] = (i + 1) * 10;
            expectedPriorities[i] = i + 1;
        }

        int index = 0;
        while(pq.next(value, priority)){
            REQUIRE(value == expectedValues[index]);
            REQUIRE(priority == expectedPriorities[index]);
            index++;
        }

        bool hasNext = pq.next(value, priority);
        REQUIRE(hasNext == false);

        pq.clear();
        REQUIRE(pq.size() == 0);
    }
}   


//This is a test case for the dequeue function
//Requires <dequeue(), enqueue(), size()> 
TEST_CASE("Dequeue operation"){
    prqueue<int> pq;

    //testing empty
    SECTION("Dequeue from an empty prqueue"){
        REQUIRE_THROWS_AS(pq.dequeue(), out_of_range);
    }

    //testing single, multiple elements
    SECTION("Dequeue from a prqueue with a single element"){
        pq.enqueue(5,10);
        int dequeued = pq.dequeue();
        REQUIRE(dequeued == 5);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Dequeue from a prqueue with multiple elements"){
        pq.enqueue(10, 1);
        pq.enqueue(8, 5);
        pq.enqueue(6, 6);
        pq.enqueue(4, 2);
        pq.enqueue(2, 3);
        pq.enqueue(0, 4);

        int first = pq.dequeue();
        REQUIRE(first == 10);
        REQUIRE(pq.size() == 5);
        
        int second = pq.dequeue();
        REQUIRE(second == 4);

        int third = pq.dequeue();
        REQUIRE(third == 2);

        int fourth = pq.dequeue();
        REQUIRE(fourth == 0);
        REQUIRE(pq.size() == 2);

        int fifth = pq.dequeue();
        REQUIRE(fifth == 8);
        REQUIRE(pq.size() == 1);

        int sixth = pq.dequeue();
        REQUIRE(sixth == 6);
        REQUIRE(pq.size() == 0);
    }

    //testing no duplicates
    SECTION("dequeue integers no duplicates decreasing"){
        pq.enqueue(10, 1);
        pq.enqueue(8, 2);
        pq.enqueue(6, 3);
        pq.enqueue(4, 4);
        pq.enqueue(2, 5);

        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 4);
        
        REQUIRE(pq.dequeue() == 8);\
        REQUIRE(pq.toString() == "3 value: 6\n4 value: 4\n5 value: 2\n");
        
        REQUIRE(pq.dequeue() == 6);
        
        REQUIRE(pq.dequeue() == 4);
        
        REQUIRE(pq.dequeue() == 2);
        REQUIRE(pq.size() == 0);
    }

    //testing duplicates
    SECTION("Dequeue from a prqueue with duplicate elements"){
        pq.enqueue(10, 2);
        pq.enqueue(20, 3);
        pq.enqueue(30, 2);
        pq.enqueue(40, 4);
        pq.enqueue(50, 2);

        REQUIRE(pq.size() == 5);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.dequeue() == 30);
        REQUIRE(pq.dequeue() == 50);
        REQUIRE(pq.dequeue() == 20);
        REQUIRE(pq.dequeue() == 40);
    }

     SECTION("Enqueue and dequeue elements"){
        pq.enqueue(5,3);
        pq.enqueue(10,2);
        pq.enqueue(15,1);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.dequeue() == 15);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.dequeue() == 5);
        REQUIRE(pq.size() == 0);
        REQUIRE_THROWS_AS(pq.dequeue(), out_of_range);
    }

    SECTION("Dequeue elements with duplicates"){
        prqueue<int> pq;
        pq.enqueue(10, 3);
        pq.enqueue(20, 2);
        pq.enqueue(30, 1);
        pq.enqueue(40, 2);
        pq.enqueue(50, 1);

        REQUIRE(pq.size() == 5);
        REQUIRE(pq.dequeue() == 30);
        REQUIRE(pq.dequeue() == 50);
        REQUIRE(pq.dequeue() == 20);
        REQUIRE(pq.dequeue() == 40);
        REQUIRE(pq.dequeue() == 10);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Multiple Enqueue and Dequeue Operations") {
        pq.enqueue(10, 1);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.peek() == 10);
        pq.enqueue(20, 3);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.peek() == 10);
        pq.enqueue(15, 2);
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == 10);
        pq.enqueue(25, 4);
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE_THROWS_AS(pq.peek(), out_of_range);
    }   
}

//This test case tests the peek function
//Required: <peek(), size(), enqueue(), dequeue()>
TEST_CASE("Peek operation"){
    prqueue<int> pq;

    //testing empty and non empty priority queue
    SECTION("Peek from an empty priority queue"){
        REQUIRE_THROWS_AS(pq.peek(), out_of_range);
        REQUIRE(pq.size() == 0);
    }

    SECTION("Peek from a non-empty priority queue"){
        pq.enqueue(10, 2);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 1);
        REQUIRE(pq.toString() == "2 value: 10\n");
        pq.enqueue(5, 3);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 2);

        pq.enqueue(20, 1);
        REQUIRE(pq.peek() == 20);
        REQUIRE(pq.size() == 3);
    }

    SECTION("Peek and Dequeue from a non-empty priority queue"){
        pq.enqueue(10, 2);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 1);

        pq.enqueue(5, 3);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 2);

        pq.enqueue(20, 1);
        REQUIRE(pq.peek() == 20);
        REQUIRE(pq.size() == 3);

        int dequeuedValue = pq.dequeue();
        REQUIRE(dequeuedValue == 20);
        REQUIRE(pq.peek() == 10);
        REQUIRE(pq.size() == 2);

        dequeuedValue = pq.dequeue();
        REQUIRE(dequeuedValue == 10);
        REQUIRE(pq.peek() == 5);
        REQUIRE(pq.size() == 1);
    }

    //peek string elements with duplicates and no duplicates
    SECTION("Peek string elements"){
        prqueue<string> pq;
        pq.enqueue("Kelly", 5);
        pq.enqueue("James", 2);
        pq.enqueue("Tom", 8);
        
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.peek() == "James");
    }

    SECTION("Peek from a queue with duplicate priorities"){
        pq.enqueue(10, 3);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 2);
        pq.enqueue(50, 1);

        REQUIRE(pq.peek() == 20);
        int dequeue = pq.dequeue();
        REQUIRE(dequeue == 20);
        REQUIRE(pq.peek() == 50);
        int dequeu2 = pq.dequeue();
        REQUIRE(dequeu2 == 50);
        REQUIRE(pq.peek() == 30);
    }

    //testing with same priority
    SECTION("Peek on a queue with uniform priority elements"){
        prqueue<int> pq;
        pq.enqueue(15, 2);
        pq.enqueue(20, 2);
        pq.enqueue(25, 2);
        
        REQUIRE(pq.peek() == 15);
        int dequeued = pq.dequeue();
        REQUIRE(dequeued == 15);
        REQUIRE(pq.peek() == 20);
        dequeued = pq.dequeue();
        REQUIRE(dequeued == 20);
        REQUIRE(pq.peek() == 25);
    }

    SECTION("Peek and Dequeue alternating elements from the queue"){
        pq.enqueue(10, 2);
        pq.enqueue(20, 1);
        pq.enqueue(30, 3);

        REQUIRE(pq.peek() == 20);
        int dequeued = pq.dequeue();
        REQUIRE(dequeued == 20);
        REQUIRE(pq.peek() == 10);

        pq.enqueue(40, 2);
        REQUIRE(pq.peek() == 10);
        dequeued = pq.dequeue();
        REQUIRE(dequeued == 10);
        REQUIRE(pq.peek() == 40);

        dequeued = pq.dequeue();
        REQUIRE(dequeued == 40);
        REQUIRE(pq.peek() == 30);
    }
}

//This is a test case for operator equality
//Requires: <enqueue(), clear(), size()>
TEST_CASE("Equality Operator"){
    prqueue<int> pq1, pq2, pq3;

    //testing empty and non empty priority queue
    SECTION("Comparing empty priority queue"){
        REQUIRE(pq1 == pq2);
        REQUIRE(pq1.size() == 0);
        pq3.enqueue(10,1);
        REQUIRE_FALSE(pq1 == pq3);
        REQUIRE(pq3.size() == 1);
    }

    SECTION("Comparing non-empty priority queues with the same eleents and sizes"){
        pq1.enqueue(10,2);
        pq1.enqueue(5,1);
        REQUIRE(pq1.size() ==2);

        pq2.enqueue(10,2);
        pq2.enqueue(5,1);
        REQUIRE(pq2.size() ==2);
        REQUIRE(pq1 == pq2);
    }

    //testing priority queues with different sizes and the same sizes
    SECTION("Comparing non-empty priority queues with different sizes"){
        pq1.enqueue(10,2);
        pq2.enqueue(5,1);
        REQUIRE(pq2.size() == 1);
        REQUIRE_FALSE(pq1 == pq2);
        
        pq1.clear();
        pq2.clear();
        REQUIRE(pq2.size() == 0);
        REQUIRE(pq2.size() == 0);
    }

 
    SECTION("Comparing non-empty priority queues with the same priority and value"){
        prqueue<int> pq1, pq2;

        pq1.enqueue(20, 1);
        pq1.enqueue(30, 2);
        REQUIRE(pq1.size() == 2);

        pq2.enqueue(20, 1);
        pq2.enqueue(30, 2);
        REQUIRE(pq2.size() == 2);
        REQUIRE(pq1 == pq2);
    }

    //testing with different elements
    SECTION("Comparing non-empty priority queues with different elements and the same sizes"){
        pq1.enqueue(15,2);
        pq1.enqueue(8,1);

        pq2.enqueue(8,2);
        pq2.enqueue(15,1);
        REQUIRE(pq2.size() == 2);
        REQUIRE(pq1.size() == 2);
        REQUIRE(pq2.size() == 2);
        REQUIRE_FALSE(pq1 == pq2);
    }

    SECTION("Comparing priority queues after enqueue each time") {
        prqueue<int> pq1, pq2;

        for(int i = 1; i <= 20; ++i){
            pq1.enqueue(i, i + 1);
            pq1 = pq2;
            REQUIRE(pq1 == pq2);
            REQUIRE(pq1.size() == pq2.size());
        }
        pq1.clear();
        REQUIRE(pq1.size() == 0);
        pq2.clear();
        REQUIRE(pq2.size() == 0);
    }

    //testing with the same element and size
    SECTION("Comparing non-empty priority queues with the same elements and sizes in reverse order"){
        pq1.enqueue(10, 1);
        pq1.enqueue(5, 2);

        pq2.enqueue(5, 2);
        pq2.enqueue(10, 1);

        pq1 = pq2;
        REQUIRE(pq1 == pq2);
        pq1.clear();
        pq2.clear();
        REQUIRE(pq1 == pq2);
        REQUIRE(pq1.size() == 0);
        REQUIRE(pq2.size() == 0);
    }

    SECTION("Comparing non-empty priority queues with the same elements and sizes after modifications"){
        pq1.enqueue(5, 1);
        pq1.enqueue(10, 2);

        pq2.enqueue(5, 1);
        pq2.enqueue(10, 2);
        
        pq2 = pq1;

        REQUIRE(pq1 == pq2);

        pq1.clear();
        pq2.clear();

        REQUIRE(pq1.size() == pq2.size());

        pq1.enqueue(5, 1);
        pq1.enqueue(10, 2);

        pq1 = pq2;
        REQUIRE(pq1 == pq2);
    }

    //different element and sizes
    SECTION("Comparing non-empty priority queues with different elements and sizes after modifications"){
        pq1.enqueue(15, 2);
        pq1.enqueue(8, 1);

        pq2.enqueue(8, 2);
        pq2.enqueue(15, 1);

        int value = 10;
        pq1.enqueue(value, 1);

        REQUIRE_FALSE(pq1 == pq2);
    }

    SECTION("Comparing empty priority queues after one is cleared"){
        pq1.enqueue(10, 1);
        pq2.enqueue(20, 2);
        pq1.clear();

        REQUIRE_FALSE(pq1 == pq2);
    }
}

//This a test case for the clear function
//Requires <clear(), enqueue(), size(), toString()>
TEST_CASE("Clearing the prqueue"){
    prqueue<int> pq;

    //testing clear for an empty, single and multiple elements
    SECTION("Clear an empty prqueue"){
        pq.clear();
        REQUIRE(pq.size() == 0);
    }

    SECTION("Clear a prqueue with elements"){
        pq.enqueue(5,2);
        pq.enqueue(10,3);
        REQUIRE(pq.size() == 2);
        REQUIRE(pq.toString() == "2 value: 5\n3 value: 10\n");
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }

    SECTION("Clear a prqueue with multiple elements"){
        pq.enqueue(10,2);
        pq.enqueue(8,4);
        pq.enqueue(6,6);
        pq.enqueue(4,8);
        pq.enqueue(2,10);

        REQUIRE(pq.size() == 5);
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }

    //test with same priority
    SECTION("Clear a prqueue with elements of the same priority"){
        prqueue<int> pq;
        pq.enqueue(5, 2);
        pq.enqueue(10, 2);
        pq.enqueue(15, 2);

        REQUIRE(pq.size() == 3);
        REQUIRE(pq.toString() == "2 value: 5\n2 value: 10\n2 value: 15\n");

        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }

    SECTION("Clear a prqueue with duplicate priority elements") {
        pq.enqueue(5, 2);
        pq.enqueue(10, 2);
        pq.enqueue(15, 3);
        REQUIRE(pq.size() == 3);
        REQUIRE(pq.toString() == "2 value: 5\n2 value: 10\n3 value: 15\n");

        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }

    //test a large test case to see if it can handle that many enqueue
    SECTION("Clear a prqueue with large number of elements"){
        for(int i = 1; i <= 10000; i++){
            pq.enqueue(i, i);
        }
        
        REQUIRE(pq.size() == 10000);
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }

    //clearing the priority queue
    SECTION("Clear priority queue"){
        prqueue<int> pq;
        pq.enqueue(5, 1);
        pq.enqueue(10, 3);
        pq.enqueue(15, 2);

        REQUIRE(pq.size() == 3);
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE_THROWS_AS(pq.peek(), out_of_range);
        REQUIRE_THROWS_AS(pq.dequeue(), out_of_range);
    }

    SECTION("Clear an already empty priority queue"){
        pq.clear();
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.toString() == "");
    }

    //enqueue and clear at the same time
    SECTION("Concurrent Enqueue and Clear"){
        for (int i = 1; i <= 100; ++i) {
            pq.enqueue(i, i);
            if (i % 10 == 0) {
                pq.clear();
            }
        }
        REQUIRE(pq.size() == 0);
    }
}

/*----------------------------------------------------------------------------------------------------------------*/

//Test cases copied from UIN: 664104217

// This is the constructor test case
// Requires: size()
TEST_CASE("Test 1: The Constructor Test") 
{
    // In this section we test int constructor.
    SECTION("Test 1: Empty Int Queue")
    {
        prqueue<int> intQ;
        REQUIRE(intQ.size() == 0);
    }

    // In this section we test string constructor.
    SECTION("Test 1: Empty String Queue")
    {
        prqueue<string> stringQ;
        REQUIRE(stringQ.size() == 0);
    }

    // In this section we test float constructor.
    SECTION("Test 1: Empty float Queue")
    {
        prqueue<float> floatQ;
        REQUIRE(floatQ.size() == 0);
    }

    SECTION("Test 1: Empty char Queue")
    {
        prqueue<char> q;
        REQUIRE(q.size() == 0);
    }

    SECTION("Test 1: Empty double Queue")
    {
        prqueue<double> q;
        REQUIRE(q.size() == 0);
    }

    SECTION("Test 1: Empty bool Queue")
    {
        prqueue<bool> q;
        REQUIRE(q.size() == 0);
    }
}

// This is the ENQUEUE test case
// Requires: size(), toString()
TEST_CASE("Test 2: The Enqueue Test") 
{
    // In this section we test int enqueue with no duplicates
    SECTION("Test 2: Int Enqueue, no duplicate priorities")
    {
        prqueue<int> intQ;
        map<int, int> values = {
            {20, 30},
            {30, 1},
            {45, 5},
            {2, 2},
            {10, 6}
        };

        for(const auto& pair : values){
            intQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(intQ.size() == 5);

        vector<pair<int, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(intQ.toString() == expectedOut.str());
    }

    // In this section we test string enqueue with no duplicates
    SECTION("Test 2: String Enqueue")
    {
        prqueue<string> stringQ;
        map<string, int> values = {
            {"20", 30},
            {"30", 1},
            {"45", 5},
            {"2", 2},
            {"10", 6}
        };

        for(const auto& pair : values){
            stringQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(stringQ.size() == 5);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(stringQ.toString() == expectedOut.str());
    }

    // In this section we test int enqueue with duplicates
    SECTION("Test 2: Int Enqueue, Duplicate Priorities")
    {
        prqueue<int> intQ;
        map<int, int> values = {
            {20, 15},
            {30, 2},
            {45, 2},
            {2, 4},
            {10, 15}
        };

        for(const auto& pair : values){
            intQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(intQ.size() == 5);

        vector<pair<int, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(intQ.toString() == expectedOut.str());

    }

    // In this section we test string enqueue with duplicates
    SECTION("Test 2: String Enqueue, Duplicate Priorities")
    {
        prqueue<string> stringQ;
        map<string, int> values = {
            {"a", 15},
            {"b", 2},
            {"c", 2},
            {"d", 4},
            {"e", 15}
        };

        for(const auto& pair : values){
            stringQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(stringQ.size() == 5);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(stringQ.toString() == expectedOut.str());
    }

    // In this section we test multiple enqueue's of the same priority and value
    SECTION("Test 2: String Enqueue, Same Priorities AND Values")
    {
        prqueue<string> stringQ;
        map<string, int> values = {
            {"a", 2},
            {"a", 2},
            {"a", 2},
            {"a", 2},
            {"a", 2},
        };

        for(const auto& pair : values){
            stringQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(stringQ.size() == 1);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(stringQ.toString() == expectedOut.str());
    }

    // In this section we test enqueue negative and zero priority
    SECTION("Test 2: String Enqueue, zero priority")
    {
        prqueue<string> stringQ;
        map<string, int> values = {
            {"a", -1},
            {"b", 0}
        };

        for(const auto& pair : values){
            stringQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(stringQ.size() == 2);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }
        REQUIRE(stringQ.toString() == expectedOut.str());
    }
}


// This is the CLEAR() test case
// Requires: size(), toString()
TEST_CASE("Test 3: The Clear Test") 
{
    // In this section we test clearing an int prqueue
    SECTION("Test 3: Int Enqueue, Clear")
    {
        prqueue<int> intQ;
        map<int, int> values = {
            {100, 1},
            {200, 1},
            {300, 2},
            {400, 4},
            {500, 15}
        };

        for(const auto& pair : values){
            intQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(intQ.size() == 5);

        vector<pair<int, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(intQ.toString() == expectedOut.str());

        intQ.clear();

        REQUIRE(intQ.size() == 0);
        REQUIRE(intQ.toString() == "");
    }

    // In this section we test clearing a string prqueue
    SECTION("Test 3: String Enqueue, Clear")
    {
        prqueue<string> strQ;
        map<string, int> values = {
            {"100", 1},
            {"200", 1},
            {"300", 2},
            {"400", 4},
            {"500", 15}
        };

        for(const auto& pair : values){
            strQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(strQ.size() == 5);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(strQ.toString() == expectedOut.str());

        strQ.clear();

        REQUIRE(strQ.size() == 0);
        REQUIRE(strQ.toString() == "");
    }

    // In this section we test clearing an empty queue
    SECTION("Test 3: Clear Empty Queue")
    {
        prqueue<string> strQ;

        REQUIRE(strQ.size() == 0);
        REQUIRE(strQ.toString() == "");

        strQ.clear();

        REQUIRE(strQ.size() == 0);
        REQUIRE(strQ.toString() == "");
    }

}


// This is the assignment =operator test case
// Requires: size(), toString()
TEST_CASE("Test 4: The =Operator Test") 
{
    // In this section we int queue assignment operation
    SECTION("Test 4: Int Queue assignment operation")
    {
        prqueue<int> pq1;
        pq1.enqueue(15, 1);
        pq1.enqueue(13, 3);
        pq1.enqueue(18, 5);
        pq1.enqueue(4, 2);
        pq1.enqueue(2, 2);

        prqueue<int> pq2;
        pq2.enqueue(16, 5);
        pq2.enqueue(17, 6);

        pq2 = pq1;

        REQUIRE(pq2.size() == pq1.size());
        REQUIRE(pq2.toString() == pq1.toString());

    }

    // In this section we test string assignment operation
    SECTION("Test 4: String Queue assignment operation")
    {
        prqueue<string> pq1;
        pq1.enqueue("13", 1);
        pq1.enqueue("13", 1);
        pq1.enqueue("18", 1);

        prqueue<string> pq2;
        pq2.enqueue("16", 5);
        pq2.enqueue("17", 6);

        pq2 = pq1;

        REQUIRE(pq2.size() == pq1.size());
        REQUIRE(pq2.toString() == pq1.toString());
    }

    // In this section we test Scenario 3.
    SECTION("Test 4: Set Filled Queue Equal to Empty Queue")
    {
        prqueue<string> pq1;

        prqueue<string> pq2;
        pq2.enqueue("16", 5);
        pq2.enqueue("17", 6);

        pq2 = pq1;

        REQUIRE(pq2.size() == pq1.size());
        REQUIRE(pq2.toString() == pq1.toString());
    }

    // In this section we test Scenario 4.
    SECTION("Test 4: Set Empty Queue Equal to a Filled Queue")
    {
        prqueue<string> pq1;

        prqueue<string> pq2;
        pq2.enqueue("16", 5);
        pq2.enqueue("17", 6);

        pq1 = pq2;

        REQUIRE(pq2.size() == pq1.size());
        REQUIRE(pq2.toString() == pq1.toString());
    }

    // In this section we test Scenario 5.
    SECTION("Test 4: Queue equality, clearing one queue and not the other")
    {
        prqueue<int> pq1;
        pq1.enqueue(15, 1);
        pq1.enqueue(13, 3);
        pq1.enqueue(18, 5);
        pq1.enqueue(4, 2);
        pq1.enqueue(2, 2);

        prqueue<int> pq2;
        pq2.enqueue(16, 5);
        pq2.enqueue(17, 6);

        // set the second que equal to the first queue
        pq2 = pq1;
        // validate that pq2 equals pq1
        REQUIRE(pq2.size() == pq1.size());
        REQUIRE(pq2.toString() == pq1.toString());
        // clear pq1
        pq1.clear();
        // validate that pq2 DIDN'T clear
        REQUIRE(pq2.size() != 0);
        REQUIRE(pq2.toString() != "");
        // validate that pq1 DID clear
        REQUIRE(pq1.size() == 0);
        REQUIRE(pq1.toString() == "");

    }
}


// This is the dequeue test case
// Requires: size(), tostring(), dequeue()
TEST_CASE("Test 5: The Dequeue Test") 
{
    // In this section we test Scenario 1.
    SECTION("Test 5: Simple Dequeue Test")
    {
        prqueue<string> strQ;
        map<string, int> values = {
            {"100", 1},
            {"200", 1},
            {"300", 2},
            {"400", 4},
            {"500", 15}
        };

        for(const auto& pair : values){
            strQ.enqueue(pair.first, pair.second);
        }

        REQUIRE(strQ.size() == 5);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        stringstream expectedOut;
        for(const auto& pair : sortedValues){
            expectedOut << pair.second << " value: " << pair.first << "\n";
        }

        REQUIRE(strQ.toString() == expectedOut.str());

        REQUIRE(strQ.dequeue() == "100");
        REQUIRE(strQ.size() == 4);
        REQUIRE(strQ.dequeue() == "200");
        REQUIRE(strQ.size() == 3);
        REQUIRE(strQ.dequeue() == "300");
        REQUIRE(strQ.size() == 2);
        REQUIRE(strQ.dequeue() == "400");
        REQUIRE(strQ.size() == 1);
        REQUIRE(strQ.dequeue() == "500");
        REQUIRE(strQ.toString() == "");
    }

    // In this section we test Scenario 2.
    SECTION("Test 5: Dequeue test")
    {
        prqueue<int> q;
        q.enqueue(1, 2);
        q.enqueue(1, 1);
        q.enqueue(3, 3);
        q.enqueue(1, 4);

        string output = "1 value: 1\n2 value: 1\n3 value: 3\n4 value: 1\n";
        REQUIRE(q.size() == 4);
        REQUIRE(q.toString() == output);

        REQUIRE(q.dequeue() == 1);
        string output2 = "2 value: 1\n3 value: 3\n4 value: 1\n";
        REQUIRE(q.size() == 3);
        REQUIRE(q.toString() == output2);

        REQUIRE(q.dequeue() == 1);
        string output3 = "3 value: 3\n4 value: 1\n";
        REQUIRE(q.size() == 2);
        REQUIRE(q.toString() == output3);


        REQUIRE(q.dequeue() == 3);
        string output4 = "4 value: 1\n";
        REQUIRE(q.size() == 1);
        REQUIRE(q.toString() == output4);

        REQUIRE(q.dequeue() == 1);
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");

    }

    // In this section we test Scenario 3.
    SECTION("Test 5: Dequeue w/ duplicate priorities")
    {
        prqueue<int> q;
        q.enqueue(10, 1);
        q.enqueue(20, 1);
        q.enqueue(30, 1);
        q.enqueue(40, 1);

        REQUIRE(q.dequeue() == 10);
        REQUIRE(q.dequeue() == 20);
        REQUIRE(q.dequeue() == 30);
        REQUIRE(q.dequeue() == 40);
        REQUIRE(q.toString() == "");
    }

    // In this section we test Scenario 4.
    SECTION("Test 5: Dequeue, Enqueue, and more dequeue")
    {
        prqueue<int> q;
        q.enqueue(10, 1);
        q.enqueue(20, 1);
        q.enqueue(30, 1);
        q.enqueue(40, 1);

        REQUIRE(q.dequeue() == 10);
        REQUIRE(q.dequeue() == 20);
        REQUIRE(q.dequeue() == 30);
        REQUIRE(q.dequeue() == 40);
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");

        q.enqueue(50, 1);
        q.enqueue(60, 1);

        REQUIRE(q.dequeue() == 50);
        REQUIRE(q.size() == 1);
        REQUIRE(q.dequeue() == 60);
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");

    }

    // long dequeue test
    SECTION("Test 5: Dequeue, Enqueue, and more dequeue, long")
    {
        prqueue<int> q;

        q.enqueue(-1, 1);
        q.enqueue(-2, 1);
        q.enqueue(-3, 1);
        q.enqueue(-4, 1);
        q.enqueue(0, 1);
        q.enqueue(2, 1);
        q.enqueue(3, 1);
        q.enqueue(4, 1);
        q.enqueue(10, 1);
        q.enqueue(20, 1);
        q.enqueue(30, 1);
        q.enqueue(40, 1);

        REQUIRE(q.dequeue() == -1);
        REQUIRE(q.dequeue() == -2);
        REQUIRE(q.dequeue() == -3);
        REQUIRE(q.dequeue() == -4);
        REQUIRE(q.dequeue() == 0);
        REQUIRE(q.dequeue() == 2);
        REQUIRE(q.dequeue() == 3);
        REQUIRE(q.dequeue() == 4);
        REQUIRE(q.size() == 4);
        REQUIRE(q.dequeue() == 10);
        REQUIRE(q.dequeue() == 20);
        REQUIRE(q.dequeue() == 30);
        REQUIRE(q.size() == 1);
        REQUIRE(q.dequeue() == 40);
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");


        q.enqueue(-50, 1);
        q.enqueue(-60, 1);
        q.enqueue(500, 1);
        q.enqueue(600, 1);
        q.enqueue(-5, 1);
        q.enqueue(-6, 1);
        q.enqueue(5, 1);
        q.enqueue(6, 1);
        q.enqueue(50, 1);
        q.enqueue(60, 1);


        REQUIRE(q.dequeue() == -50);
        REQUIRE(q.size() == 9);
        REQUIRE(q.dequeue() == -60);
        REQUIRE(q.size() == 8);
        REQUIRE(q.dequeue() == 500);
        REQUIRE(q.size() == 7);
        REQUIRE(q.dequeue() == 600);
        REQUIRE(q.size() == 6);
        REQUIRE(q.dequeue() == -5);
        REQUIRE(q.size() == 5);
        REQUIRE(q.dequeue() == -6);
        REQUIRE(q.size() == 4);
        REQUIRE(q.dequeue() == 5);
        REQUIRE(q.size() == 3);
        REQUIRE(q.dequeue() == 6);
        REQUIRE(q.size() == 2);
        REQUIRE(q.dequeue() == 50);
        REQUIRE(q.size() == 1);
        REQUIRE(q.dequeue() == 60);
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");
    }

    // long dequeue test, string queue
    SECTION("Test 5: Dequeue, Enqueue, and more dequeue, long")
    {
        prqueue<string> q;

        q.enqueue("-1", 1);
        q.enqueue("-2", 1);
        q.enqueue("-3", 1);
        q.enqueue("-4", 1);
        q.enqueue("0", 1);
        q.enqueue("2", 1);
        q.enqueue("3", 1);
        q.enqueue("4", 1);
        q.enqueue("10", 1);
        q.enqueue("20", 1);
        q.enqueue("30", 1);
        q.enqueue("40", 1);

        REQUIRE(q.dequeue() == "-1");
        REQUIRE(q.size() == 11);
        REQUIRE(q.dequeue() == "-2");
        REQUIRE(q.size() == 10);
        REQUIRE(q.dequeue() == "-3");
        REQUIRE(q.size() == 9);
        REQUIRE(q.dequeue() == "-4");
        REQUIRE(q.size() == 8);
        REQUIRE(q.dequeue() == "0");
        REQUIRE(q.size() == 7);
        REQUIRE(q.dequeue() == "2");
        REQUIRE(q.size() == 6);
        REQUIRE(q.dequeue() == "3");
        REQUIRE(q.size() == 5);
        REQUIRE(q.dequeue() == "4");
        REQUIRE(q.size() == 4);
        REQUIRE(q.dequeue() == "10");
        REQUIRE(q.size() == 3);
        REQUIRE(q.dequeue() == "20");
        REQUIRE(q.size() == 2);
        REQUIRE(q.dequeue() == "30");
        REQUIRE(q.size() == 1);
        REQUIRE(q.dequeue() == "40");
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");


        q.enqueue("-50", 1);
        q.enqueue("-60", 1);
        q.enqueue("500", 1);
        q.enqueue("600", 1);
        q.enqueue("-5", 1);
        q.enqueue("-6", 1);
        q.enqueue("5", 1);
        q.enqueue("6", 1);
        q.enqueue("50", 1);
        q.enqueue("60", 1);


        REQUIRE(q.dequeue() == "-50");
        REQUIRE(q.size() == 9);
        REQUIRE(q.dequeue() == "-60");
        REQUIRE(q.size() == 8);
        REQUIRE(q.dequeue() == "500");
        REQUIRE(q.size() == 7);
        REQUIRE(q.dequeue() == "600");
        REQUIRE(q.size() == 6);
        REQUIRE(q.dequeue() == "-5");
        REQUIRE(q.dequeue() == "-6");
        REQUIRE(q.dequeue() == "5");
        REQUIRE(q.dequeue() == "6");
        REQUIRE(q.dequeue() == "50");
        REQUIRE(q.dequeue() == "60");
        REQUIRE(q.toString() == "");
    }

    // long dequeue, char
    SECTION("Test 5: Dequeue, Enqueue, and more dequeue, long (char values)") {
        prqueue<char> q;

        q.enqueue('A', 1);
        q.enqueue('B', 1);
        q.enqueue('C', 1);
        q.enqueue('D', 1);
        q.enqueue('E', 1);
        q.enqueue('F', 1);
        q.enqueue('G', 1);
        q.enqueue('H', 1);
        q.enqueue('I', 1);
        q.enqueue('J', 1);
        q.enqueue('K', 1);
        q.enqueue('V', 1);


        REQUIRE(q.dequeue() == 'A');
        REQUIRE(q.size() == 11);
        REQUIRE(q.dequeue() == 'B');
        REQUIRE(q.size() == 10);
        REQUIRE(q.dequeue() == 'C');
        REQUIRE(q.size() == 9);
        REQUIRE(q.dequeue() == 'D');
        REQUIRE(q.size() == 8);
        REQUIRE(q.dequeue() == 'E');
        REQUIRE(q.size() == 7);
        REQUIRE(q.dequeue() == 'F');
        REQUIRE(q.size() == 6);
        REQUIRE(q.dequeue() == 'G');
        REQUIRE(q.size() == 5);
        REQUIRE(q.dequeue() == 'H');
        REQUIRE(q.size() == 4);
        REQUIRE(q.dequeue() == 'I');
        REQUIRE(q.size() == 3);
        REQUIRE(q.dequeue() == 'J');
        REQUIRE(q.size() == 2);
        REQUIRE(q.dequeue() == 'K');
        REQUIRE(q.size() == 1);
        REQUIRE(q.dequeue() == 'V');
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");

        q.enqueue('X', 1);
        q.enqueue('Y', 1);
        q.enqueue('Z', 1);
        q.enqueue('a', 1);
        q.enqueue('b', 1);
        q.enqueue('c', 1);

        REQUIRE(q.dequeue() == 'X');
        REQUIRE(q.size() == 5);
        REQUIRE(q.dequeue() == 'Y');
        REQUIRE(q.size() == 4);
        REQUIRE(q.dequeue() == 'Z');
        REQUIRE(q.size() == 3);
        REQUIRE(q.dequeue() == 'a');
        REQUIRE(q.size() == 2);
        REQUIRE(q.dequeue() == 'b');
        REQUIRE(q.size() == 1);
        REQUIRE(q.dequeue() == 'c');
        REQUIRE(q.size() == 0);
        REQUIRE(q.toString() == "");
    }

}

// This tests the peek() function
// Require: size(), dequeue()
TEST_CASE("Test 6: Peek Test")
{
    // This is a basic peek test
    SECTION("Test 6: Peek")
    {
        prqueue<int> q;
        q.enqueue(200, 2);
        q.enqueue(300, 3);
        q.enqueue(400, 4);

        REQUIRE(q.peek() == 200);   

        q.enqueue(100, 1);
        // validate that the new priority changed
        REQUIRE(q.peek() == 100);
    }

    // This tests the peek function after dequeue'ing elements
    SECTION("Test 6: Peek after dequeue")
    {
        prqueue<int> q;
        q.enqueue(100, 1);
        q.enqueue(200, 2);
        q.enqueue(300, 3);
        q.enqueue(400, 4);

        REQUIRE(q.size() == 4);
        REQUIRE(q.peek() == 100);
        REQUIRE(q.dequeue() == 100);

        REQUIRE(q.size() == 3);
        REQUIRE(q.peek() == 200);
        REQUIRE(q.dequeue() == 200);

        REQUIRE(q.size() == 2);
        REQUIRE(q.peek() == 300);
        REQUIRE(q.dequeue() == 300);

        REQUIRE(q.size() == 1);
        REQUIRE(q.peek() == 400);
        REQUIRE(q.dequeue() == 400);

        REQUIRE(q.size() == 0);
    }

    // This tests the peek function w/ duplicate priorities
    SECTION("Test 6: Peek with duplicate priorities")
    {
        prqueue<int> q;
        q.enqueue(200, 1);
        q.enqueue(100, 1);
        q.enqueue(300, 1);
        q.enqueue(400, 4);
        q.enqueue(900, 1);

        REQUIRE(q.size() == 5);
        REQUIRE(q.peek() == 200);
        REQUIRE(q.peek() == q.dequeue());

        REQUIRE(q.size() == 4);
        REQUIRE(q.peek() == 100);
        REQUIRE(q.peek() == q.dequeue());

        REQUIRE(q.size() == 3);
        REQUIRE(q.peek() == 300);
        REQUIRE(q.peek() == q.dequeue());

        REQUIRE(q.size() == 2);
        REQUIRE(q.peek() == 900);
        REQUIRE(q.peek() == q.dequeue());

        REQUIRE(q.size() == 1);
        REQUIRE(q.peek() == 400);
        REQUIRE(q.peek() == q.dequeue());

        REQUIRE(q.size() == 0);
    }

    // long peek
    SECTION("Long peek test")
    {
        prqueue<int> q;
        q.enqueue(0, 10);
        q.enqueue(0, 9);
        q.enqueue(0, 8);

        REQUIRE(q.peek() == 0);
        REQUIRE(q.peek() == q.dequeue());
        REQUIRE(q.peek() == 0);
        REQUIRE(q.peek() == q.dequeue());
        REQUIRE(q.peek() == 0);
        REQUIRE(q.peek() == q.dequeue());
    }
}

// Testing the next function
// Requires: size(), value, priority
TEST_CASE("Test 7: Next() Test")
{
    // this section tests basic next function
    SECTION("Test 7: Basic next(), long queue")
    {
        prqueue<string> q;
        map<string, int> values = {
            {"100", 1},
            {"200", 99},
            {"300", 2},
            {"400", 4},
            {"500", 15},
            {"600", 8},
            {"700", 7},
            {"800", 5},
            {"900", 14},
            {"10", 15},
            {"11", 100},
            {"12", -1},
            {"13", 0},
            {"14", 40},
            {"15", 19}
        };

        string value;
        int priority;

        for(const auto& pair : values){
            q.enqueue(pair.first, pair.second);
        }

        REQUIRE(q.size() == 15);

        vector<pair<string, int>> sortedValues(values.begin(), values.end());
        sort(sortedValues.begin(), sortedValues.end(), [](const auto& a, const auto& b){
            return a.second < b.second;
        });

        q.begin();

        for(const auto& pair : sortedValues){
            q.next(value, priority);
            REQUIRE(pair.first == value);
            REQUIRE(pair.second == priority);
        }

    }

    // This section tests the next() function with an empty queue.
    SECTION("Next() with an empty queue") 
    {
        prqueue<int> q;
        int value, priority;

        // Try to call next() on an empty queue.
        REQUIRE_FALSE(q.next(value, priority));
        REQUIRE(q.size() == 0);
    }
}

TEST_CASE("Test 8: ==operator")
{
    prqueue<int> q1;
    prqueue<int> q2;

    SECTION("empty queue '==' check")
    {
        REQUIRE(q1.size() == q2.size());
        REQUIRE(q1.toString() == q2.toString());
        REQUIRE(q1 == q2);
    }

    SECTION("basic '==' check")
    {
        q1.enqueue(1, 2);
        q1.enqueue(2, 1);
        q2.enqueue(1, 2);
        q2.enqueue(2, 1);

        REQUIRE(q1.size() == 2);
        REQUIRE(q2.size() == 2);
        REQUIRE(q1.size() == q2.size());
        REQUIRE(q1.toString() == q2.toString());
        REQUIRE(q1 == q2);
    }

    SECTION("basic '==' check, string queue")
    {
        prqueue<string> pq;
        prqueue<string> pq2;

        pq.enqueue("1", 2);
        pq.enqueue("2", 1);
        pq2.enqueue("1", 2);
        pq2.enqueue("2", 1);

        REQUIRE(pq.size() == 2);
        REQUIRE(pq2.size() == 2);
        REQUIRE(pq.size() == pq2.size());
        REQUIRE(pq.toString() == pq2.toString());
        REQUIRE(pq == pq2);
    }

    SECTION("basic '==' check using '=' overloaded operator")
    {
        q1.enqueue(1, 2);
        q1.enqueue(2, 1);

        q2 = q1;

        REQUIRE(q1.size() == 2);
        REQUIRE(q2.size() == 2);
        REQUIRE(q1.size() == q2.size());
        REQUIRE(q1.toString() == q2.toString());
        REQUIRE(q1 == q2);
    }

    SECTION("Non-equal queues with different elements") 
    {
        q1.enqueue(1, 2);
        q1.enqueue(2, 1);
        q2.enqueue(1, 2);
        q2.enqueue(3, 3);  // Different element

        REQUIRE(q1.size() == 2);
        REQUIRE(q2.size() == 2);
        REQUIRE_FALSE(q1 == q2);
        REQUIRE_FALSE(q1.toString() == q2.toString());

    }

    SECTION("Non-equal queues with different sizes") 
    {
        q1.enqueue(1, 2);
        q2.enqueue(1, 2);
        q2.enqueue(2, 1);  // Different size

        REQUIRE(q1.size() == 1);
        REQUIRE(q2.size() == 2);
        REQUIRE_FALSE(q1 == q2);
        REQUIRE_FALSE(q1.toString() == q2.toString());

    }

    SECTION("Equal queues with duplicate elements") 
    {
        q1.enqueue(1, 2);
        q1.enqueue(1, 2);  // Duplicate elements
        q2.enqueue(1, 2);
        q2.enqueue(1, 2);  // Duplicate elements

        REQUIRE(q1 == q2);

        // Additional assertions
        REQUIRE(q1.size() == q2.size());
        REQUIRE(q1.toString() == q2.toString());

    }
}