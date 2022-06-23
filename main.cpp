#include <iostream>
#include "tree.h"
#include "set.h"
#include "classes.h"
#include "set_tests.h"
#include "tree_tests.h"
#include "errors.h"
void tests(){
    tests_set();
    tests_tree();
}

using namespace std;

int main() {
    tests();
    int main_key = 0;
    while (main_key != 3) {
        cout << "1 - set, 2 - tree, 3 - exit\n";
        cin >> main_key;
        switch (main_key) {
            case 1: {
                Set<int> set_1;
                Set<int> set_2;
                Set<int> result;
                int set_key = 0;
                while (set_key != 6) {
                    cout << "1 - Input set, 2 - Output set, 3 - Insert or Delete key\n"
                            "4 - Write or Read set from file,5 - Operations with sets, 6 - Exit\n";
                    scanf("%d", &set_key);
                    switch (set_key) {
                        case 1:
                            set_1.Clean();
                            set_2.Clean();
                            cout << "set_1, enter size: ";
                            int size_1;
                            cin >> size_1;
                            for (int i = 0; i < size_1; i++) {
                                int input;
                                cin >> input;
                                set_1.Insert(input);
                            }
                            cout << "set_2, enter size: ";
                            int size_2;
                            cin >> size_2;
                            for (int i = 0; i < size_2; i++) {
                                int input;
                                cin >> input;
                                set_2.Insert(input);
                            }
                            break;
                        case 2:
                            cout << "set_1:\n";
                            cout << set_1;
                            cout << "\nset_2:\n";
                            cout << set_2;
                            cout << "\nres_set:\n";
                            cout << result;
                            cout << "\n";
                            break;
                        case 3:
                            int choose;
                            cout << "1 - Remove,2 - Insert?\n";
                            cin >> choose;
                            if (choose == 1) {
                                cout << "1 - set_1, 2 - set_2 and what to remove?\n";
                                cin >> choose;
                                int element;
                                cin >> element;
                                if (choose == 1) {
                                    set_1.Remove(element);
                                }
                                if (choose == 2) {
                                    set_2.Remove(element);
                                }
                            }
                            if (choose == 2) {
                                cout << "1 - set_1, 2 - set_2 and what to insert?\n";
                                cin >> choose;
                                int element;
                                cin >> element;
                                if (choose == 1) {
                                    set_1.Insert(element);
                                }
                                if (choose == 2) {
                                    set_2.Insert(element);
                                }
                            }
                            break;
                        case 4:
                            cout << "1 - Write set_1, 2 - Write set_2, 3 - Write res_set\n"
                                    "4 - Read set_1, 5 - Read set_2, 6 - Read res_set\n";
                            cin >> choose;
                            if (choose == 1) {
                                set_1.WriteToFile();
                            }
                            if (choose == 2) {
                                set_2.WriteToFile();
                            }
                            if (choose == 3) {
                                result.WriteToFile();
                            }
                            if (choose == 4) {
                                set_1.ReadFromFile();
                            }
                            if (choose == 5) {
                                set_2.ReadFromFile();
                            }
                            if (choose == 6) {
                                result.ReadFromFile();
                            }
                            break;
                        case 5:
                            cout << "1 - Union set_1 and set_2, 2 - Intersection set_1 and set_2\n"
                                    "3 - Set_1 minus Set_2, 4 - Set_2 minus Set_1\n";
                            cin >> choose;
                            if (choose == 1) {
                                result.Clean();
                                result.Union(set_2);
                                result.Union(set_1);
                            }
                            if (choose == 2) {
                                result.Clean();
                                result.Union(set_1);
                                result.Intersection(set_2);
                            }
                            if (choose == 3) {
                                result.Clean();
                                result.Union(set_1);
                                result.Subtraction(set_2);
                            }
                            if (choose == 4) {
                                result.Clean();
                                result.Union(set_2);
                                result.Subtraction(set_1);
                            }
                            if (choose == 1 or choose == 2 or choose == 3 or choose == 4) {
                                cout << "Result was saved into res_set\n";
                            }
                            break;
                        case 6:
                            set_key = 6;
                            break;
                        default:
                            cout << "Error, try again\n";
                    }
                }
                break;
            }

            case 2: {
                BinarySearchTree<int> tree1;
                BinarySearchTree<int> tree2;
                BinarySearchTree<int> res;
                int tree_key = 0;
                while (tree_key != 7) {
                    cout << "1 - Input trees, 2 - Output trees, 3 Insert or Delete key\n"
                            "4 - Write or Read tree from file, 5 - Operation with trees\n"
                            "6 - travels in tree, 7 - Exit\n";
                    int choose;
                    cin >> tree_key;
                    switch (tree_key) {
                        case 1:
                            int size;
                            cout << "Enter size and tree_1:";
                            cin >> size;
                            for (int i = 0; i < size; i++) {
                                cin >> choose;
                                tree1.Insert(choose);
                            }
                            cout << "Enter size and tree_2:";
                            cin >> size;
                            for (int i = 0; i < size; i++) {
                                cin >> choose;
                                tree2.Insert(choose);
                            }
                            break;
                        case 2:
                            cout << "tree_1:\n";
                            cout << tree1;
                            cout << "\ntree_2:\n";
                            cout << tree2;
                            cout << "\nres_tree:\n";
                            cout << res;
                            cout << "\n";
                            break;
                        case 3:
                            cout << "1 - Remove,2 - Insert?\n";
                            cin >> choose;
                            if (choose == 1) {
                                cout << "1 - set_1, 2 - set_2 and what to remove?\n";
                                cin >> choose;
                                int element;
                                cin >> element;
                                if (choose == 1) {
                                    tree1.RemoveKey(element);
                                }
                                if (choose == 2) {
                                    tree2.RemoveKey(element);
                                }
                            }
                            if (choose == 2) {
                                cout << "1 - set_1, 2 - set_2 and what to insert?\n";
                                cin >> choose;
                                int element;
                                cin >> element;
                                if (choose == 1) {
                                    tree1.Insert(element);
                                }
                                if (choose == 2) {
                                    tree2.Insert(element);
                                }
                            }
                            break;
                        case 4:
                            cout << "1 - Write tree_1, 2 - Write tree_2, 3 - Write res_tree\n"
                                    "4 - Read tree_1, 5 - Read tree_2, 6 - Read res_tree\n";
                            cin >> choose;
                            if (choose == 1) {
                                tree1.WriteToFile();
                            }
                            if (choose == 2) {
                                tree2.WriteToFile();
                            }
                            if (choose == 3) {
                                res.WriteToFile();
                            }
                            if (choose == 4) {
                                tree1.ReadFromFile();
                            }
                            if (choose == 5) {
                                tree2.ReadFromFile();
                            }
                            if (choose == 6) {
                                res.ReadFromFile();
                            }
                            break;
                        case 7:

                            break;
                        case 6:
                            cout << "1 - tree_1, 2 - tree_2, 3 - res_tree\n";
                            cin >> choose;
                            try {
                                if (choose == 1) {
                                    int size_temp = tree1.GetSize();
                                    int *data;
                                    std::cout << "Choose tree traversal:\n";
                                    std::cout << "l - left, r - right, R - root\n1 - Rlr, 2 - Rrl, 3 - lRr\n4 - lrR, 5 - rRl, 6 - rlR\n\n";
                                    data = tree1.Show();
                                    for(int i = 0; i < size_temp; i++){
                                        cout << data[i] << " ";
                                    }
                                    delete[] data;
                                    cout << "\n";
                                }
                                if (choose == 2) {
                                    int size_temp = tree2.GetSize();
                                    int *data;
                                    std::cout << "Choose tree traversal:\n";
                                    std::cout << "l - left, r - right, R - root\n1 - Rlr, 2 - Rrl, 3 - lRr\n4 - lrR, 5 - rRl, 6 - rlR\n\n";
                                    data = tree2.Show();
                                    for(int i = 0; i < size_temp; i++){
                                        cout << data[i] << " ";
                                    }
                                    delete[] data;
                                    cout << "\n";
                                }
                                if (choose == 3) {
                                    int size_temp = res.GetSize();
                                    int *data;
                                    std::cout << "Choose tree traversal:\n";
                                    std::cout << "l - left, r - right, R - root\n1 - Rlr, 2 - Rrl, 3 - lRr\n4 - lrR, 5 - rRl, 6 - rlR\n\n";
                                    data = res.Show();
                                    for(int i = 0; i < size_temp; i++){
                                        cout << data[i] << " ";
                                    }
                                    delete[] data;
                                    cout << "\n";
                                }

                            }
                            catch (IndexOutOfRange *e) {
                                cout << e->IndexErrorList(1) << endl;

                                delete e;
                            }
                            break;
                        case 5:
                            cout << "1 - Where with (x % 2 == 0) to tree_1, 2 - Map with (x*x) to tree_1\n"
                                    "3 - Where with (x % 2 == 0) to tree_2, 4 - Map with (x*x) to tree_2\n"
                                    "5 - Concat tree_1 with tree_2\n";
                            cin >> choose;
                            if(choose == 1){
                                res = tree1.Where([](int x){return x % 2 == 0;});
                            }
                            if(choose == 2){
                                res = tree1.Map([](int x){return x * x;});
                            }
                            if(choose == 3){
                                res = tree2.Where([](int x){return x % 2 == 0;});
                            }
                            if(choose == 4){
                                res = tree2.Map([](int x){return x * x;});
                            }
                            if(choose == 5){
                                res.Clean();
                                res.Concat(tree1);
                                res.Concat(tree2);
                            }
                            cout << "Result was saved into res_tree\n";
                            break;
                        default:
                            cout << "Error, try again\n";
                    }
                }
                break;
            }

            case 3: {
                break;
            }
            default: {
                cout << "Error! Choose again: 1 - set, 2 - tree, 3 - exit\n";
                cin >> main_key;
            }
        }
    }
}
