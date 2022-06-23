#pragma once

#include "tree.h"
#include "cassert"


void tests_tree() {
    BinarySearchTree<int> test1; // 0 1 2 3 4
    BinarySearchTree<int> test2; //     2 3 4 5 6
    BinarySearchTree<int> test3; // 0 1 2 3 4 5 6
    BinarySearchTree<int> test4; //     2 3 4
    BinarySearchTree<int> test5; // 0 1       5 6
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
    BinarySearchTree<int> test6;
    test6 = test1;
    assert(test6 == test1);
    int data_[7] = {3, 1, 0, 2, 5, 4, 6};
    int *data = test3.GetData();
    int count = 0;
    for (int i = 0; i < test3.GetSize(); i++) {
        if (data[i] == data_[i]) {
            count++;
        }
    }
    assert(count == 7);
    delete[] data;

};