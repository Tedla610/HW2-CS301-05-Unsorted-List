// Created by Tedla Boke on 9/7/23.
// NetId: uq6435
// Email: tboke@horizon.csueastbay.edu

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// A class to store the Data item
class ItemType {
public:
    int value;
    ItemType() {
        value = 0;
    }
    ItemType(int value) {
        this->value = value;
    }
};

// A struct to store the node of the linked list
struct NodeType {
    ItemType data;
    NodeType* next;
};

// A class to implement the unsorted list using a linked list
class UnsortedList {
private:
    NodeType* head;
public:
    UnsortedList() {
        head = nullptr;
        length = 0;
    }
    ~UnsortedList() {
        NodeType* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    void putItem(ItemType item);
    void putItem(ItemType item, int position);
    void deleteItem(int key);
    ItemType getItem(int position);
    void printAll();
    int length;
};

// A function to append an item at the end of the list
void UnsortedList::putItem(ItemType item) {
    NodeType* newNode = new NodeType;
    newNode->data = item;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
    }
    else {
        NodeType* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    length++;
}

// A function to insert an item at a given position in the list
void UnsortedList::putItem(ItemType item, int position) {
    if (position < 0 || position > length) {
        cout << "Invalid position" << endl;
        return;
    }
    NodeType* newNode = new NodeType;
    newNode->data = item;
    if (position == 0) {
        newNode->next = head;
        head = newNode;
    }
    else {
        NodeType* temp = head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    length++;
}

// A function to delete an item with a given key from the list
void UnsortedList::deleteItem(int key) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    NodeType* temp = head;
    NodeType* prev = nullptr;
    while (temp != nullptr && temp->data.value != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Key not found" << endl;
        return;
    }
    if (prev == nullptr) {
        head = head->next;
    }
    else {
        prev->next = temp->next;
    }
    delete temp;
    length--;
}

// A function to get an item at a given position in the list
ItemType UnsortedList::getItem(int position) {
    if (position < 0 || position >= length) {
        cout << "Invalid position" << endl;
        return ItemType();
    }
    NodeType* temp = head;
    for (int i = 0; i < position; i++) {
        temp = temp->next;
    }
    return temp->data;
}

// A function to print all the keys in order in the list
void UnsortedList::printAll() {
    NodeType* temp = head;
    while (temp != nullptr) {
        cout << temp->data.value << " ";
        temp = temp->next;
    }
    cout << endl;
}

// A function to read data from a file and perform operations on the list
void readData(const string& filename, UnsortedList& list) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Cannot open file" << endl;
        return;
    }
    string line;
    int count = 0;
    while (getline(fin, line)) {
        count++;
        stringstream ss(line);
        string token;
        if (count == 1) {
            while (getline(ss, token, ',')) {
                int value = stoi(token);
                ItemType item(value);
                list.putItem(item);
            }
            cout << "After adding numbers from first line: ";
            list.printAll();
        }
        else if (count == 2) {
            while (getline(ss, token, ',')) {
                int key = stoi(token);
                list.deleteItem(key);
            }
            cout << "After deleting numbers from second line: ";
            list.printAll();
        }
        else if (count == 3) {
            while (getline(ss, token, ',')) {
                int value, position;
                stringstream st(token);
                getline(st, token, '@');
                value = stoi(token);
                getline(st, token, '@');
                if (token == "END") {
                    position = list.length;
                }
                else {
                    position = stoi(token);
                }
                ItemType item(value);
                list.putItem(item, position);
            }
            cout << "After adding numbers from third line: ";
            list.printAll();
        }
    }
    fin.close();
}

int main() {
    string filename;

    cout << "Enter the name of the input data file: ";
    cin >> filename;

    UnsortedList myList;

    readData(filename, myList);

    return 0;
}


