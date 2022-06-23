#pragma once

#include "set.h"
#include "cassert"


void tests_set() {
    Set<int> test1; // 0 1 2 3 4
    Set<int> test2; //     2 3 4 5 6
    Set<int> test3; // 0 1 2 3 4 5 6
    Set<int> test4; //     2 3 4
    Set<int> test5; // 0 1       5 6
    for (int i = 0; i < 5; i++) {
        test1.Insert(i);
        test2.Insert(i + 2);
    }
    for (int i = 0; i < 7; i++) {
        test3.Insert(i);
    }
    for (int i = 2; i < 5; i++) {
        test4.Insert(i);
    }
    test5.Insert(0), test5.Insert(1);
    Set<int> test6 = test1;
    test6.Union(test2);
    assert(test6 == test3);
    Set<int> test7 = test1;
    test7.Intersection(test2);
    assert(test7 == test4);
    Set<int> test8 = test1;
    test8.Subtraction(test2);
    assert(test8 == test5);
    Set<int> test9 = test1.Map([](int x) { return (x * x); });
    Set<int> test10;
    for (int i = 0; i < 5; i++) {
        test10.Insert(i * i);
    }
    assert(test10 == test9);
    Set<int> test11;
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            test11.Insert(i);
        }
    }
    Set<int> test12 = test1.Where([](int x) { return (x % 2 == 0); });
    assert(test12 == test11);
    Set<int> test13 = test1;
    test13.Remove(2);
    test13.Insert(2);
    assert(test13 == test1);
};