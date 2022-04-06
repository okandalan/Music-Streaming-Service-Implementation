#include <iostream>

#include "LinkedList.h"
using namespace std;

int main() {
    LinkedList<float> llist;

    llist.print();
    llist.insertAtTheFront(1);

    llist.insertAtTheFront(1);
    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(1);

    llist.print();
    cout << "*************\n";

    llist.removeNode(1);
    
    LinkedList<float> llist2;
    llist2 = llist;
    cout << "*************\n";
    
    llist2.print();

    if(llist.contains(llist.getNode(4))) cout << "aaaaaaaa\n";
    cout << "*************\n";

    llist.~LinkedList();
    llist.print();

    return 0;
}
