#pragma once


#include <fstream>
#include "iostream"
#include "errors.h"

template<class T>
class BinarySearchTree {
private: // Узел, поля, перечисления
    enum choose {
        Left,
        Right,
        Root
    };

    typedef struct Node {
        T key;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        int balance = 0;

        Node() {
            key = T();
        }

        Node(T item) {
            key = item;
        }

        Node(T item, int Balance) {
            key = item;
            balance = Balance;
        }

    } Node;

    Node *root = nullptr;

public: // Конструкторы

    BinarySearchTree() {

    }

    BinarySearchTree(T *items, int count) {
        for (int i = 0; i < count; i++) {
            Insert(items[i]);
        }
    }

    BinarySearchTree(const BinarySearchTree<T> &Tree) {
        if (Tree.root != nullptr) {
            root = new Node(Tree.root->key, Tree.root->balance);
            CopyNode(root, Tree.root->left, Left);
            CopyNode(root, Tree.root->right, Right);
        } else {
            root == nullptr;
        }
    }

public: // методы

    int GetSize() {
        int count = 0;
        GetSize_(root, count);
        return count;
    }

    void Insert(T Key) {
        if (root == nullptr) {
            root = new Node(Key);
        } else {
            Insert_(root, nullptr, Key, Root);
        }
    }

    bool Contains(T Key) {
        if (Find_(root, Key) != nullptr) return true;
        return false;
    }

    int RemoveKey(T Key) {
        RemoveKey_(root, Key);
        return 0;
    }

    template<typename Func>
    BinarySearchTree<T> Map(Func func) {
        BinarySearchTree<T> newTree;
        T *data = GetData();
        for (int i = 0; i < GetSize(); i++) {
            newTree.Insert(func(data[i]));
        }
        delete[] data;
        return newTree;
    }

    template<typename Func>
    BinarySearchTree<T> Where(Func func) {
        BinarySearchTree<T> temp;
        BinarySearchTree<T> newTree = temp;
        if (root == nullptr) return newTree;
        Where_(newTree, root, func);
        return newTree;
    }

    template<typename Func>
    T Reduce(Func func) {
        T result = 0;
        if (root == nullptr) return result;
        Reduce_(root, func, result);
        return result;
    }

    BinarySearchTree<T> Merge(BinarySearchTree<T> Tree) {
        BinarySearchTree < T > newTree = *this;
        Merge_(&newTree, Tree.root);
        return newTree;
    }

    void Concat(BinarySearchTree<T> Tree) { //mergein
        Merge_(this, Tree.root);
    }

    BinarySearchTree<T> GetSub(T Key) {
        Node *node = Find_(root, Key);
        BinarySearchTree<T> temp;
        BinarySearchTree<T> newTree = temp;
        if (node == nullptr) return newTree;
        newTree.root = new Node(Key, node->balance);
        CopyNode(newTree.root, node->left, Left);
        CopyNode(newTree.root, node->right, Right);
        return newTree;
    }

    bool SubTree(BinarySearchTree<T> Tree) { //is Sub tree
        if (root == nullptr) return true;
        Node *node = Find_(root, Tree.root->key);
        return FindSub_(node, Tree.root);
    }

    T *GetData() {
        int size = GetSize();
        try {
            T *arr = new T[size];
            int index = 0;
            GetData_(arr, root, index);
            return arr;
        }
        catch (...) {
            return nullptr;
        }
    }

    T *Show() {
        int choose;
        scanf("%d", &choose);
        T *data = new T[GetSize()];
        int index = 0;
        switch (choose) {
            case 1:
                show_Rlr(data, root, index);
                break;
            case 2:
                show_Rrl(data, root, index);
                break;
            case 3:
                show_lRr(data, root, index);
                break;
            case 4:
                show_lrR(data, root, index);
                break;
            case 5:
                show_rRl(data, root, index);
                break;
            case 6:
                show_rlR(data, root, index);
                break;
            default:
                throw new IndexOutOfRange(WrongIndex);
        }
        return data;
    }

    void WriteToFile() { //Rlr //stream
        T *data = GetData();
        ofstream fout;
        fout.open("test_tree");
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
        ifstream fin("test_tree");
        fin >> size;
        T temp;
        for (int i = 0; i < size; i++) {
            fin >> temp;
            Insert(temp);
        }
        fin.close();
    }

    void Clean() {
        T *data = GetData();
        int size = GetSize();
        for (int i = 0; i < size; i++) {
            RemoveKey(data[i]);
        }
        delete[] data;
    }

public: // Деструктор и операторы

    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &Tree) {
        deleteTree(root);
        if (Tree.root != nullptr) {
            root = new Node(Tree.root->key, Tree.root->balance);
            CopyNode(root, Tree.root->left, Left);
            CopyNode(root, Tree.root->right, Right);
        } else {
            root = nullptr;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &stream, BinarySearchTree &object) {
        Node *temp = object.root;
        operator_two_arrows(temp, 0, stream);
    }

    bool operator==(BinarySearchTree<T> &tree) {
        if (this->GetSize() == tree.GetSize()) {
            return this->SubTree(tree);
        }
    }

    ~BinarySearchTree() {
        deleteTree(root);
    }

private: // Внутрення кухня
    void rotateLeft(Node *node) {
        Node *nextNode = node->right;
        if (nextNode == nullptr) {
            int i = 0;
        }
        node->right = nextNode->left;
        if (nextNode->left != nullptr) nextNode->left->parent = node;
        nextNode->left = node;
        nextNode->parent = node->parent;
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = nextNode;
            } else {
                node->parent->right = nextNode;
            }
        }
        node->parent = nextNode;
        if (/*node->balance == -2 &&*/ nextNode->balance == -1) {
            node->balance = 0;
            nextNode->balance = 0;
        } else {
            if (/*node->balance == -2 &&*/ nextNode->balance == 0) {
                node->balance = -1;
                nextNode->balance = 1;
            }
        }
        if (node == root) root = nextNode;
    }

    void rotateRight(Node *node) {
        Node *nextNode = node->left;
        node->left = nextNode->right;
        if (nextNode->right != nullptr) nextNode->right->parent = node;
        nextNode->right = node;
        nextNode->parent = node->parent;
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = nextNode;
            } else {
                node->parent->right = nextNode;
            }
        }
        node->parent = nextNode;
        if (/*node->balance == 2 && */ nextNode->balance == 1) {
            node->balance = 0;
            nextNode->balance = 0;
        } else {
            if (/*node->balance == 2 && */nextNode->balance == 0) {
                node->balance = 1;
                nextNode->balance = -1;
            }
        }
        if (node == root) root = nextNode;
    }

    void bigRotateLeft(Node *node) {
        Node *rNode = node->right;
        Node *rlNode = node->right->left;
        rotateRight(node->right);
        rotateLeft(node);
        if (rlNode->balance == 1) {
            node->balance = 0;
            rNode->balance = -1;
            rlNode->balance = 0;
        }
        if (rlNode->balance == -1) {
            node->balance = 1;
            rNode->balance = 0;
            rlNode->balance = 0;
        }
        if (rlNode->balance == 0) {
            node->balance = 0;
            rNode->balance = 0;
            rlNode->balance = 0;
        }
    }

    void bigRotateRight(Node *node) {
        Node *lNode = node->left;
        Node *lrNode = node->left->right;
        rotateLeft(node->left);
        rotateRight(node);
        if (lrNode->balance == -1) {
            node->balance = 0;
            lNode->balance = 1;
            lrNode->balance = 0;
        }
        if (lrNode->balance == 1) {
            node->balance = -1;
            lNode->balance = 0;
            lrNode->balance = 0;
        }
        if (lrNode->balance == 0) {
            node->balance = 0;
            lNode->balance = 0;
            lrNode->balance = 0;
        }
    }

    void Rotate(Node *node) {
        if (node->balance == -2) {
            if (node->right->balance == -1 || node->right->balance == 0) {
                rotateLeft(node);
            } else {
                bigRotateLeft(node);
            }
        }
        if (node->balance == 2) {
            if (node->left->balance == 1 || node->left->balance == 0) {
                rotateRight(node);
            } else {
                bigRotateRight(node);
            }
        }
    }

    static void operator_two_arrows(Node *p, int level, std::ostream &stream) {
        if (p != nullptr) {
            operator_two_arrows(p->right, level + 1, stream);
            for (int i = 0; i < level; i++) {
                stream << "   ";
            }
            stream << p->key << " <\n";
            operator_two_arrows(p->left, level + 1, stream);
        }
    }

    void GetData_(T *arr, Node *node, int &index) {
        if (node != nullptr) {
            arr[index] = node->key;
            index++;
            GetData_(arr, node->left, index);
            GetData_(arr, node->right, index);
        }
    }

    void GetSize_(Node *node, int &count) {
        if (node != nullptr) {
            count++;
            GetSize_(node->left, count);
            GetSize_(node->right, count);
        }
    }

    void Merge_(BinarySearchTree<T> *newTree, Node *node) {
        if (node != nullptr) {
            newTree->Insert(node->key);
            Merge_(newTree, node->left);
            Merge_(newTree, node->right);
        }
    }

    bool FindSub_(Node *thisNode, Node *treeNode) {
        if (treeNode == nullptr) return true;
        if (thisNode == nullptr) return false;
        if (thisNode->key != treeNode->key) return false;
        return (FindSub_(thisNode->left, treeNode->left) &&
                FindSub_(thisNode->right, treeNode->right));
    }

    Node *Find_(Node *node, T Key) {
        if (node == nullptr) return nullptr;
        if (node->key == Key) return node;
        if (Key > node->key) Find_(node->right, Key);
        else Find_(node->left, Key);
    }

    void CopyNode(Node *prevNode, Node *node, choose ident) {
        if (node != nullptr) {
            Node *newNode = new Node(node->key, node->balance);
            newNode->parent = prevNode;
            if (ident == Left) prevNode->left = newNode;
            else prevNode->right = newNode;
            CopyNode(newNode, node->left, Left);
            CopyNode(newNode, node->right, Right);
        }
    }


    template<typename Func>
    void Where_(BinarySearchTree<T> &newTree, Node *node, Func func) {
        if (node != nullptr) {
            if (func(node->key)) newTree.Insert(node->key);
            Where_(newTree, node->left, func);
            Where_(newTree, node->right, func);
        }
    }

    template<typename Func>
    void Reduce_(Node *node, Func func, T &result) {
        if (node != nullptr) {
            result = result + func(node->key);
            Reduce_(node->left, func, result);
            Reduce_(node->right, func, result);
        }
    }

    choose findParent(Node *node) {
        if (node->parent == nullptr) return Root;
        if (node->parent->left == node) return Left;
        return Right;
    }

    int Insert_(Node *node, Node *prevNode, T Key, choose ident) {
        if (node == nullptr) {
            node = new Node(Key);
            node->parent = prevNode;
            if (prevNode == nullptr) return 0;
            if (ident == Left) prevNode->left = node;
            if (ident == Right) prevNode->right = node;
            while (node != nullptr) {
                choose ident = findParent(node);
                if (ident == Left) {
                    node = node->parent;
                    node->balance++;
                    if (node->balance == 2) Rotate(node);
                    if (node->balance == 0) return 0;
                }
                if (ident == Right) {
                    node = node->parent;
                    node->balance--;
                    if (node->balance == -2) Rotate(node);
                    if (node->balance == 0) return 0;
                }
                if (ident == Root) {
                    return 0;
                }
            }
        }

        if (Key < node->key) {
            return Insert_(node->left, node, Key, Left);
        }

        if (Key > node->key) {
            return Insert_(node->right, node, Key, Right);
        }

        if (Key == node->key) return -1;
    }

    int RemoveKey_(Node *node, T Key) {
        Node *delNode = Find_(root, Key);
        if (delNode == nullptr) return 0;
        return deleteNode(delNode);
    }

    int deleteNode(Node *node) {
        Node *nowNode = nullptr;
        choose ident = Root;
        if (node->right != nullptr) {
            Node *minNode = node->right;
            ident = Right;
            while (minNode->left != nullptr) {
                minNode = minNode->left;
                ident = Left;
            }
            node->key = minNode->key;
            nowNode = minNode->parent;
            if (ident == Left) {
                minNode->parent->left = minNode->right;
                if (minNode->right != nullptr) minNode->right->parent = minNode->parent;
            }
            if (ident == Right) {
                minNode->parent->right = minNode->right;
                if (minNode->right != nullptr) minNode->right->parent = minNode->parent;
            }
            delete minNode;
        } else {
            if (node->left != nullptr) {
                Node *maxNode = node->left;
                ident = Left;
                while (maxNode->right != nullptr) {
                    maxNode = maxNode->right;
                    ident = Right;
                }
                node->key = maxNode->key;
                nowNode = maxNode->parent;
                if (ident == Right) {
                    maxNode->parent->right = maxNode->left;
                    if (maxNode->left != nullptr) maxNode->left->parent = maxNode->parent;
                }
                if (ident == Left) {
                    maxNode->parent->left = maxNode->left;
                    if (maxNode->left != nullptr) maxNode->left->parent = maxNode->parent;
                }
                delete maxNode;
            } else {
                ident = findParent(node);
                if (ident == Root) {
                    delete root;
                    root = nullptr;
                    return 1;
                }

                if (ident == Left) {
                    node->parent->left = nullptr;
                    nowNode = node->parent;
                    delete node;
                }
                if (ident == Right) {
                    node->parent->right = nullptr;
                    nowNode = node->parent;
                    delete node;
                }
            }
        }
        while (nowNode != nullptr) {
            if (ident == Left) {
                nowNode->balance--;
                if (nowNode->balance == -2) Rotate(nowNode);
                if (nowNode->balance == -1) return 1;
                ident = findParent(nowNode);
                nowNode = nowNode->parent;
            }

            if (ident == Right) {
                nowNode->balance++;
                if (nowNode->balance == 2) Rotate(nowNode);
                if (nowNode->balance == 1) return 1;
                ident = findParent(nowNode);
                nowNode = nowNode->parent;
            }

        }
        return 1;
    }

    void deleteTree(Node *node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    };

    void show_Rlr(T *data, Node *node, int &index) {
        if (node == nullptr) {
            return;    //Если дерева нет, выходим
        }
        data[index] = node->key;
        index++;
        show_Rlr(data, node->left, index); //Обошли левое поддерево
        show_Rlr(data, node->right, index); //Обошли правое поддерево
    }

    void show_Rrl(T *data, Node *node, int &index) {
        if (node == nullptr) {
            return;    //Если дерева нет, выходим
        }
        data[index] = node->key;
        index++;
        show_Rrl(data, node->right, index); //Обошли правое поддерево
        show_Rrl(data, node->left, index); //Обошли левое поддерево
    }

    void show_lRr(T *data, Node *node, int &index) {
        if (node == nullptr) {
            return;    //Если дерева нет, выходим
        }
        show_lRr(data, node->left, index); //Обошли левое поддерево
        data[index] = node->key;
        index++;
        show_lRr(data, node->right, index); //Обошли правое поддерево
    }

    void show_lrR(T *data, Node *node, int &index) {
        if (node == nullptr) {
            return;    //Если дерева нет, выходим
        }
        show_lrR(data, node->left, index); //Обошли левое поддерево
        show_lrR(data, node->right, index); //Обошли правое поддерево
        data[index] = node->key;
        index++;
    }

    void show_rRl(T *data, Node *node, int &index) {
        if (node == nullptr) {
            return;    //Если дерева нет, выходим
        }
        show_rRl(data, node->right, index); //Обошли правое поддерево
        data[index] = node->key;
        index++;
        show_rRl(data, node->left, index); //Обошли левое поддерево
    }

    void show_rlR(T *data, Node *node, int &index) {
        if (node == nullptr) {
            return;    //Если дерева нет, выходим
        }
        show_rlR(data, node->right, index); //Обошли правое поддерево
        show_rlR(data, node->left, index); //Обошли левое поддерево
        data[index] = node->key;
        index++;
    }

};