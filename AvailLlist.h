//
// Created by ziad on 12/3/2024.
//

#ifndef FILES_ASSIGNMENT_AVAILIST_H
#define FILES_ASSIGNMENT_AVAILIST_H


using namespace std ;
#include <iostream>
struct AvailableNode {
    int position;
    AvailableNode* next;

    AvailableNode(int pos) : position(pos), next(nullptr) {}
};

class AvaiList {
private:
    AvailableNode* head;

public:
    AvaiList() : head(nullptr) {}

    ~AvaiList() {
        while (head) {
            AvailableNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(int position) {
        AvailableNode* newNode = new AvailableNode(position);
        newNode->next = head;
        head = newNode;
    }

    int get() {
        if (!head) return -1;
        int position = head->position;
        AvailableNode* temp = head;
        head = head->next;
        delete temp;
        return position;
    }

    void print() {
        AvailableNode* temp = head;
        cout << "AVAIL LIST: ";
        while (temp) {
            cout << temp->position << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};



#endif //FILES_ASSIGNMENT_AVAILIST_H
