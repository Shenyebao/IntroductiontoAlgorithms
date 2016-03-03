#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main() {
    int a[5] = {3,4,7,2,5};
    BinaryTree<int> bt(a, 5);
    cout<<bt.size()<<endl;
    cout<<bt.findmin()->key<<endl;
    cout<<bt.findmax()->key<<endl;
    cout<<bt.find(5)->key<<endl;
    vector<int> v = bt.inorder();
    for(auto it = v.begin(); it != v.end(); it++)
        cout<<*it<<" ";
    cout<<endl;
    bt.remove(2);
    vector<int> v1 = bt.inorder();
    for(auto it = v1.begin(); it != v1.end(); it++)
        cout<<*it<<" ";
    cout<<endl;
    return 0;
}