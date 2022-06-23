#pragma once

#include <fstream>
#include "tree.h"

template<class T>

class Set {

private: //дерево и узел для <<

    BinarySearchTree<T> items;
    typedef struct Node {
    } Node;

public: //конструкторы

    Set(T *items, int count) {
        this->items = BinarySearchTree<T>(items, count);
    }

    Set() {
        items;
    }

    Set(const Set<T> &set) {
        items = (set.items);
    }

public: //методы

    T *GetData() {
        return items.GetData();
    }

    template<typename Func>
    Set<T> Map(Func func) {
        Set<T> newSet;
        BinarySearchTree<T> temp = items;
        newSet.items = temp.Map(func);
        return newSet;
    }

    template<typename Func>
    Set<T> Where(Func func) {
        Set<T> newSet;
        newSet.items = items.Where(func);
        return newSet;
    }

    template<typename Func>
    T Reduce(Func func) {
        return items.Reduce(func);
    }

    void Insert(T item) {
        items.Insert(item);
    }

    void Clean() {
        T *data = GetData();
        int size = GetSize();
        for (int i = 0; i < size; i++) {
            Remove(data[i]);
        }
        delete[] data;
    }

    void Remove(T item) {
        items.RemoveKey(item);
    }

    int GetSize() {
        return items.GetSize();
    }

    bool SubKey(T Key) {
        return items.Contains(Key);
    }

    bool SubSet(const Set<T> set) {
        return items.SubTree(set.items);
    }

    void Union(Set<T> set) { //Merge
        items.Concat(set.items);
    }

    void Intersection(Set<T> set) {
        BinarySearchTree<T> old_tree_1 = items;
        BinarySearchTree<T> old_tree_2 = items;
        T *old_data = GetData();
        int old_size = GetSize();
        for (int i = 0; i < old_size; i++) { //очистка множества, чтобы добавлять новые данные
            Remove(old_data[i]);
        }
        old_tree_2.Concat(set.items); //все данные из обоих множеств
        T *data = old_tree_2.GetData(); //все данные из обоих множеств в массиве
        for (int i = 0; i < old_tree_2.GetSize(); i++) { //если данные есть в двух старых, то вставка
            if ((old_tree_1.Contains(data[i]) and set.items.Contains(data[i]))) {
                Insert(data[i]);
            }
        }
        delete[] old_data;
        delete[] data;
    }

    void Subtraction(Set<T> set) {
        T *data = set.GetData();
        for (int i = 0; i < set.GetSize(); i++) {
            if (SubKey(data[i])) {
                Remove(data[i]);
            }
        }
        delete[] data;
    }

    void WriteToFile() {
        T *data = GetData();
        ofstream fout;
        fout.open("test_set");
        fout << GetSize() << " ";
        for (int i = 0; i < GetSize(); i++) {
            fout << data[i] << " ";
        }
        fout.close();
        delete[] data;
    }

    void ReadFromFile() {
        Clean();
        int size;
        ifstream fin("test_set");
        fin >> size;
        T temp;
        for (int i = 0; i < size; i++) {
            fin >> temp;
            Insert(temp);
        }
        fin.close();
    }


public: //операторы и деструктор

    Set<T> operator=(const Set<T> set) {
        Set<T> temp;
        temp.items = set.items;
        return temp;
    }

    friend std::ostream &operator<<(std::ostream &stream, Set &object) {
        int size = object.GetSize();
        T *data = object.items.GetData();
        for (int i = 0; i < size; i++) {
            stream << data[i] << " ";
        }
        stream << " ";
        delete[] data;
    }

    bool operator==(Set<T> set) {
        if (set.GetSize() != GetSize()) {
            return false;
        }
        T *data = set.GetData();
        for (int i = 0; i < GetSize(); i++) {
            if (!(SubKey(data[i]))) {
                delete[] data;
                return false;
            }
        }
        delete[] data;
        return true;
    }

    ~Set() {
    }

};