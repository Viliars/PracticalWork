#include <iostream>
#include "avl.h"
using namespace std;
int main() {
    AVLTree t;
    t.insert("abra");
    t.insert("cadabra");
    t.insert("foo");
    t.insert("bar");
    t.print();
    t.remove("cadabra");
    cout<<"-----------------------------------------------------"<<endl;
    t.print();
    return 0;
}
