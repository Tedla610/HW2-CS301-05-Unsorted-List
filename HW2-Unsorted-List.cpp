// Created by Tedla Boke on 9/7/23.
// NetId: uq6435
// Email: tboke@horizon.csueastbay.edu

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// A class to store the data item
class ItemType {
public:
    int value; // The value of the item
    ItemType() { // Default constructor
        value = 0;
    }
    ItemType(int value) { // Parameterized constructor
        this->value = value;
    }
};

// A struct to store the node of the linked list
struct NodeType {
    ItemType data; // The data item
    NodeType* next; // The pointer to the next node
};

// A class to implement the unsorted list using a linked list
class UnsortedList {
private:
    NodeType* head; // The pointer to the head of the list
    // The length of the list
public:
    UnsortedList() { // Default constructor
        head = nullptr;
        length = 0;
    }
    ~UnsortedList() { // Destructor
        NodeType* temp; // A temporary pointer to store the current node
        while (head != nullptr) { // Loop until the list is empty
            temp = head; // Store the head node in temp
            head = head->next; // Move the head to the next node
            delete temp; // Delete the temp node
        }
    }
    void putItem(ItemType item); // A function to append an item at the end of the list
    void putItem(ItemType item, int position); // A function to insert an item at a given position in the list
    void deleteItem(int key); // A function to delete an item with a given key from the list
    ItemType getItem(int position); // A function to get an item at a given position in the list
    void printAll(); // A function to print all the keys in order in the list
    int length;
};

// A function to append an item at the end of the list
void UnsortedList::putItem(ItemType item) {
    NodeType* newNode = new NodeType; // Create a new node
    newNode->data = item; // Assign the item to the node data
    newNode->next = nullptr; // Set the node next pointer to NULL
    if (head == nullptr) { // If the list is empty
        head = newNode; // Set the head pointer to the new node
    }
    else { // If the list is not empty
        NodeType* temp = head; // Create a temporary pointer to store the current node
        while (temp->next != nullptr) { // Loop until the end of the list is reached
            temp = temp->next; // Move the temp pointer to the next node
        }
        temp->next = newNode; // Link the last node to the new node
    }
    length++; // Increment the length of the list by 1
}

// A function to insert an item at a given position in the list
void UnsortedList::putItem(ItemType item, int position) {
    if (position < 0 || position > length) { // If the position is invalid
        cout << "Invalid position" << endl; // Print an error message
        return; // Return from the function without inserting anything
    }
    NodeType* newNode = new NodeType; // Create a new node
    newNode->data = item; // Assign the item to the node data
    if (position == 0) { // If the position is 0 (the beginning of the list)
        newNode->next = head; // Set the node next pointer to point to the current head node
        head = newNode; // Set the head pointer to point to the new node
    }
    else { // If the position is not 0 (somewhere in the middle or the end of the list)
        NodeType* temp = head; // Create a temporary pointer to store the current node
        for (int i = 0; i < position - 1; i++) { // Loop until the node before the position is reached
            temp = temp->next; // Move the temp pointer to the next node
        }
        newNode->next = temp->next; // Set the node next pointer to point to the node after the position
        temp->next = newNode; // Set the temp node next pointer to point to the new node
    }
    length++; // Increment the length of the list by 1
}

// A function to delete an item with a given key from the list
void UnsortedList::deleteItem(int key) {
    if (head == nullptr) { // If the list is empty
        cout << "List is empty" << endl; // Print an error message
        return; // Return from the function without deleting anything
    }
    NodeType* temp = head; // Create a temporary pointer to store the current node
    NodeType* prev = nullptr; // Create a pointer to store the previous node
    while (temp != nullptr && temp->data.value != key) { // Loop until the end of the list is reached or the key is found
        prev = temp; // Store the current node in prev
        temp = temp->next; // Move the temp pointer to the next node
    }
    if (temp == nullptr) { // If the key is not found in the list
        cout << "Key not found" << endl; // Print an error message
        return; // Return from the function without deleting anything
    }
    if (prev == nullptr) { // If the key is found in the head node
        head = head->next; // Set the head pointer to point to the next node
    }
    else { // If the key is found somewhere else in the list
        prev->next = temp->next; // Set the prev node next pointer to point to the node after the temp node
    }
    delete temp; // Delete the temp node
    length--; // Decrement the length of the list by 1
}

// A function to get an item at a given position in the list
ItemType UnsortedList::getItem(int position) {
    if (position < 0 || position >= length) { // If the position is invalid
        cout << "Invalid position" << endl; // Print an error message
        return ItemType(); // Return a default item object
    }
    NodeType* temp = head; // Create a temporary pointer to store the current node
    for (int i = 0; i < position; i++) { // Loop until the position is reached
        temp = temp->next; // Move the temp pointer to the next node
    }
    return temp->data; // Return the data item of the temp node
}

// A function to print all the keys in order in the list
void UnsortedList::printAll() {
    NodeType* temp = head; // Create a temporary pointer to store the current node
    while (temp != nullptr) { // Loop until the end of the list is reached
        cout << temp->data.value << " "; // Print the value of the data item of the temp node
        temp = temp->next; // Move the temp pointer to the next node
    }
    cout << endl; // Print a new line
}

// A function to read data from a file and perform operations on the list
void readData(const string& filename, UnsortedList& list) {
    ifstream fin(filename); // Open an input file stream with the given filename
    if (!fin.is_open()) { // If opening fails
        cout << "Cannot open file" << endl; // Print an error message
        return; // Return from function without reading anything
    }
    string line; // A string variable to store each line of data from file
    int count = 0; // A counter variable to keep track of which line is being read
    while (getline(fin, line)) { // Loop until all lines are read from file
        count++; // Increment counter by 1
        stringstream ss(line); // Create a string stream object with line as input
        string token; // A string variable to store each token separated by comma or @ symbol
        if (count == 1) { // If it is first line of data
            while (getline(ss, token, ',')) { // Loop until all tokens are read from line separated by comma
                int value = stoi(token); // Convert token string to integer value
                ItemType item(value); // Create an item object with value as parameter
                list.putItem(item); // Append item at end of list using putItem function
            }
            cout << "After adding numbers from first line: ";
            list.printAll(); // Print all keys in order in list using printAll function
        }
        else if (count == 2) { // If it is second line of data
            while (getline(ss, token, ',')) { // Loop until all tokens are read from line separated by comma
                int key = stoi(token); // Convert token string to integer key
                list.deleteItem(key); // Delete item with key from list using deleteItem function
            }
            cout << "After deleting numbers from second line: ";
            list.printAll(); // Print all keys in order in list using printAll function
        }
        else if (count == 3) { // If it is third line of data
            while (getline(ss, token, ',')) { // Loop until all tokens are read from line separated by comma
                int value, position; // Declare two integer variables to store value and position
                stringstream st(token);
                getline(st, token, '@'); // Split token at '@' to get value and position
                value = stoi(token); // Convert value token string to integer value
                getline(st, token, '@'); // Get position token
                if (token == "END") {
                    position = list.length; // If position is "END", set it to the end of the list
                }
                else {
                    position = stoi(token); // Convert position token string to integer position
                }
                ItemType item(value); // Create an item object with value as parameter
                list.putItem(item, position); // Insert item at specified position in list using putItem function
            }
            cout << "After adding numbers from third line: ";
            list.printAll(); // Print all keys in order in list using printAll function
        }
    }
    fin.close(); // Close the input file stream
}

int main() {
    string filename;

    // Ask the user to enter the input filename
    cout << "Enter the name of the input data file: ";
    cin >> filename;

    UnsortedList myList; // Create an empty unsorted list

    // Read data from the file and perform operations on the list
    readData(filename, myList);

    return 0;
}


