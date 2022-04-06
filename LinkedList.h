#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    if (obj.head == NULL) {
        head = NULL;
        size = 0;
        
    }
    else {
        
        
        head = new Node<T> (obj.head->data);
        head->prev = head;
        head->next = head;
    
        Node<T> * curr1 = head;
        Node<T> * curr2 = obj.head;
        for (int i = 0; i < obj.size - 1; i++) {
            curr1->next = new Node<T> (curr2->next->data, curr1, NULL);
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        head->prev = curr1;
        curr1->next = head;
    
        curr1 = NULL;
        curr2 = NULL;
    
        size = obj.size;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    if (head == NULL) return;
    Node<T> * tmp;
    for (int i = 0; i < size - 1; i++) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    tmp = head;
    head = NULL;
    delete tmp;

    size = 0;
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    return size == 0;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    if (node == NULL) return false;
    Node<T> *curr = head;
    for (int i = 0; i < size; i++) {
        if (curr->data == node->data && curr->next == node->next && curr->prev == node->prev) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    if (isEmpty()) return NULL;

    return head; 
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    if (isEmpty()) return NULL;

    return head->prev;     
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> * curr = head;
    for (int i = 0; i < size; i++) {
        if (curr->data == data) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    if (index < 0 || index > size -1) return NULL;

    Node<T> * curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr;

}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
    if (isEmpty()) {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
    }
    else {
        Node<T> *tmp = new Node<T>(data);
        tmp->next = head;
        tmp->prev = head->prev;
        tmp->prev->next = tmp;
        head->prev = tmp;
        head = tmp;  
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
    if (isEmpty()) {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
    }
    else {
        Node<T> *tmp = new Node<T>(data);
        tmp->prev = head->prev;
        tmp->next = head;
        head->prev->next = tmp;
        head->prev = tmp;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    if (node == NULL) return;

    if (isEmpty()) {
        if (head == node) {
            insertAtTheFront(data);
            return;
        }
        else {
            return;
        }
    }

    if (node == head->prev) {
        insertAtTheEnd(data);
        return;
    }
    else {
        bool finded = false;

        Node<T> *curr = head;

        for (int i = 0; i < size; i++) {

            if (curr == node) {

                finded = true;
                break;
            }
            curr = curr->next;
        }
        if (finded) {
            Node<T> *tmp = new Node<T> (data, node, node->next);
            tmp->next->prev = tmp;
            node->next = tmp;
            size++;
        }
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    if (k < 2) return;

    int add_size, count;
    count = add_size = 0;
    Node<T> *curr = head;

    for(int i = 0; i < size; i++) {
        count++;
        if (count == k - 1) {
            /* insert and skip the node*/
            Node<T> *tmp = new Node<T> (data, curr, curr->next);
            tmp->next->prev = tmp;
            curr->next = tmp;         
            add_size++;

            curr = curr->next;
            count = 0; 
            
        }
        curr = curr->next;
    }
    size += add_size; 
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    if (node == NULL) return;

    if (head == NULL) return;

    if (head == node) {
        if (size == 1) {
            delete head;
            head = NULL;
            size--;
        }
        else {
            head->next->prev = head->prev;
            head->prev->next = head->next;
            head = head->next;
            delete node;
            size--;
        }

    }
    else {
        Node<T> *curr = head;
        for (int i = 0; i < size; i++) {
            if (curr == node) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                size--;
                break;                
            }
            curr = curr->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    if (head == NULL) return;

    if (head->data == data && size == 1) {
        delete head;
        head = NULL;
        size--;
        return;
    }
    else {
        int substract_size = 0;
        Node<T> *curr = head;
        for (int i = 0; i < size; i++) {
            if (curr->data == data) {
                if (curr == head) {
                    if (head ->next == head) {
                        head = NULL;
                        delete curr;
                        substract_size++;
                    }
                    else {
                        head->next->prev = head->prev;
                        head->prev->next = head->next;
                        Node<T> * tmp = head;
                        head = head->next;
                        curr = head;
                        delete tmp;
                        substract_size++;
                    }                    
                }
                else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    Node<T> * tmp = curr;
                    curr = curr->next;
                    delete tmp;
                    substract_size++;
                }                
            }
            else {
                curr = curr->next;
            }
        }
        size -= substract_size;
    }   
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    if (head == NULL) return;

    Node<T> *tmp;
    for (int i = 0; i < size - 1; i++) {
        tmp = head;
        head = head->next;         /* iterate until i = size - 1 
                                    rather than size since  last_node->next was deleted */
        delete tmp;
    }
    tmp = head;
    head = NULL;     /* delete last node and assigned head to null*/
    delete tmp;

    size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    if (k < 2) return;

    int count = 1;
    Node<T> *curr = head;
    int substract_size = 0;

    for (int i = 0; i < size; i++) {
        if (count == k) {
            Node<T> *tmp = curr;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            curr = curr->next;
            delete tmp;
            substract_size++;
            count = 1; 
        }
        else {
            curr = curr->next;
            count++;
        }
    }
    size -= substract_size;
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
    if (node1 == node2) return;

    if ((node1 == head) && (node2 == head->prev)) {
        if (size == 2) {
            head = node2;
            return;
        }
        else {
            node2->next = node1->next;
            node1->prev = node2->prev;
            node2->next->prev = node2;
            node1->prev->next = node1;
            node1->next = node2;
            node2->prev = node1;
            head = node2;
            return;
        }

    }

    if ((node2 == head) && (node1 == head->prev)) {
        if (size == 2) {
            head = node1;
            return;
        }
        else {
            node1->next = node2->next;
            node2->prev = node1->prev;
            node1->next->prev = node1;
            node2->prev->next = node2;
            node2->next = node1;
            node1->prev = node2;
            head = node1;
            return;
        }        
    }

    Node<T> *curr = head;
    int check = 0;
    for (int i = 0; i < size; i++) {
        if (curr == node1 || curr == node2) check++;
        curr = curr->next;
    }
    if (!check) return;
    else {
        if (node1->next == node2) {

            node2->prev = node1->prev;
            node1->next = node2->next;
            node2->prev->next = node2;
            node1->next->prev = node1;
            node1->prev = node2;
            node2->next = node1;

            if (node1 == head) {
                head = node2;
                return;
            }
            if (node2 == head) {
                head = node1;
                return;
            }
        }
        else if (node2->next == node1) {
            node1->prev = node2->prev;
            node2->next = node1->next;
            node1->prev->next = node1;
            node2->next->prev = node2;
            node2->prev = node1;
            node1->next = node2;

            if (node1 == head) {
                head = node2;
                return;
            }
            if (node2 == head) {
                head = node1;
                return;
            }
        }
        else {
            Node<T> *tmp = node1->next;
            node1->next = node2->next;
            node2->next = tmp;
            node2->next->prev = node2;
            node1->next->prev = node1;
            
            tmp = node1->prev;
            node1->prev = node2->prev;
            node2->prev = tmp;
            node2->prev->next = node2;
            node1->prev->next = node1;

            if (node1 == head) {
                head = node2;
                return;
            }
            if (node2 == head) {
                head = node1;
                return;
            }
        }



    } 

    


    return;
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    Node<T> *n1, *n2;
    for (int i = 0; i < size; i++) {
        n1 = getNodeAtIndex(i);
        n2 = getNodeAtIndex((i * i + seed) % size);
        swap(n1, n2);

    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    if (this != &rhs) {
        removeAllNodes();
        if (rhs.head == NULL) {
            return *this;
        }
        Node<T> *curr = rhs.head;
        for (int i = 0; i < rhs.size; i++) {
            insertAtTheEnd(curr->data);
            curr = curr->next;
        }
        size = rhs.size;
    }
    return *this;

}

#endif //LINKEDLIST_H
