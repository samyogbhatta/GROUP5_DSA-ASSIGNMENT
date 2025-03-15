#include <iostream>
#include <cstdlib>
#include <chrono>
#include <limits>
#include <string>

using namespace std;
using namespace chrono;

// Node structure to store data in the linked list
struct Node {
    long long int data;   // Data stored in the node
    Node* next; // Pointer to the next node in the list
};

// Head of the linked list
Node* head = NULL;

// Function to create a new node
Node* create_node(long long int data) {
    Node* newNode = new Node(); // Allocate memory for a new node
    if (!newNode) {
        cout << "Error: Memory allocation failed.\n";
        exit(1);
    }
    newNode->data = data; // Set the data
    newNode->next = NULL; // Initialize the next pointer to NULL
    return newNode;
}

// Function to insert a node at the beginning
void insert_at_beginning(long long int value) {
    Node* newNode = create_node(value); // Create a new node
    newNode->next = head; // Point the new node to the head
    head = newNode; // Update the head to the new node
}

// Function to print the linked list
void print_list() {
    Node* temp = head; // Start from the head
    while (temp != NULL) {
        cout << temp->data << " -> "; // Print the data
        temp = temp->next; // Move to the next node
    }
    cout << "NULL\n";
}

// Function to assign values to the list
void assign() {
    string input;
    cout << "Enter numbers to add to the list. Type 'done' to stop inputting.\n";
    
    while (true) {
        cout << "Enter a number: ";
        cin >> input;
        if (input == "done") {
            cout << "Input complete.\n";
            break;
        }
        try {
            long long int u_inp = stoll(input);
            insert_at_beginning(u_inp);
        } catch (invalid_argument& e) {
            cout << "Invalid input. Please enter a number or 'done' to finish.\n";
        } catch (out_of_range& e) {
            cout << "Number out of range. Please enter a smaller number.\n";
        }
    }
}

// Function to get the length of the list
int list_length() {
    int counter = 0;
    Node* start = head; // Start from the head
    while (start != NULL) {
        counter++;
        start = start->next; // Move to the next node
    }
    return counter;
}

// Function to get the value of a node at a specific index
long long int node_value_at(int index) {
    Node* temp = head; // Start from the head
    int counter = 0;
    while (temp != NULL && counter < index) {
        temp = temp->next; // Move to the next node
        counter++;
    }
    if (temp == NULL) {
        return -1; // Return -1 if the index is out of bounds
    }
    return temp->data;
}

// Function to perform selection sort on the list
void selection_sort() {
    for (Node* start = head; start != nullptr; start = start->next) {
        Node* min_node = start;
        for (Node* curr = start->next; curr != nullptr; curr = curr->next) {
            if (curr->data < min_node->data) {
                min_node = curr;
            }
        }
        if (min_node != start) {
            long long int temp = start->data;
            start->data = min_node->data;
            min_node->data = temp;
        }
    }
}

// Function to split the list for merge sort
Node* split(Node* head) {
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    Node* fast = head;
    Node* slow = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }

    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

// Function to merge two sorted lists
Node* merge(Node* first, Node* second) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;

    if (first->data < second->data) {
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}

// Function to perform merge sort on the list
Node* merge_sort(Node* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    Node* second = split(head);

    head = merge_sort(head);
    second = merge_sort(second);

    return merge(head, second);
}

// Function to find the middle of the list
Node* middle(Node* start, Node* last) {
    if (start == NULL) {
        return NULL;
    }
    if (start == last) {
        return start;
    }
    Node* slow = start;
    Node* fast = start->next;

    while (fast != last) {
        fast = fast->next;
        slow = slow->next;
        if (fast != last) {
            fast = fast->next;
        }
    }
    return slow;
}

// Function to perform binary search on the list
void binary_search(long long int value) {
    Node* start = head;
    Node* last = NULL;
    bool found = false;
    while (!found) {
        Node* mid = middle(start, last);
        if (mid == NULL) {
            cout << "The value is not in the list.";
            break;
        }
        if (mid->data == value) {
            cout << "Value found in the list.";
            found = true;
            break;
        } else if (start == last) {
            cout << "The value is not in the list.";
            break;
        } else if (mid->data < value) {
            start = mid->next;
        } else {
            last = mid;
        }
    }
}

void interpolation_search(long long int value) {
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* low = head;
    Node* high = head;
    
    // Move high to the last node
    while (high->next != nullptr) {
        high = high->next;
    }

    while (low != nullptr && high != nullptr && low != high && high->next != low) {
        if (low->data == high->data) {
            if (low->data == value) {
                cout << "Value found in the list." << endl;
            } else {
                cout << "Value not found in the list." << endl;
            }
            return;
        }

        // Estimate position using pointer traversal
        Node* pos = low;
        int steps = (value - low->data) * list_length() / (high->data - low->data);

        // Move pos forward by "steps" positions
        for (int i = 0; pos != nullptr && i < steps; i++) {
            pos = pos->next;
        }

        if (pos == nullptr) {
            cout << "Value not found in the list." << endl;
            return;
        }

        if (pos->data == value) {
            cout << "Value found in the list." << endl;
            return;
        } else if (pos->data < value) {
            low = pos->next;
        } else {
            high = pos;
        }
    }

    cout << "Value not found in the list." << endl;
}


// Function to handle user input and operations
void user_input() {
    char u_inp = '~';
    assign(); // Allow the user to enter an unlimited number of integers
    while (u_inp != '0') {
        cout << "\n\nWhat action would you like to perform on the list?\n1. Add more elements.\n2. Sort the list using Selection Sort\n3. Sort the list using Merge Sort\n4. Search for an element using Binary Search\n5. Search for an element using Interpolation Search\n6. Display the list\n\n0. Exit the program\n>";
        cin >> u_inp;
        switch (u_inp) {
            case '0': {
                break;
            }
            case '1': {
                assign(); // Allow the user to add more elements
                break;
            }
            case '2': {
                auto q_start = high_resolution_clock::now();
                selection_sort();
                cout << "\nThe list has been sorted using Selection Sort:\n";
                print_list();
                auto q_end = high_resolution_clock::now();
                double q_time = duration<double>(q_end - q_start).count();
                cout << "\nTime taken: " << q_time << " ms";
                break;
            }
            case '3': {
                auto m_start = high_resolution_clock::now();
                head = merge_sort(head);
                cout << "\nThe list has been sorted using Merge Sort:\n";
                print_list();
                auto m_end = high_resolution_clock::now();
                double m_time = duration<double>(m_end - m_start).count();
                cout << "\nTime taken: " << m_time << " ms";
                break;
            }
            case '4': {
                long long int search;
                cout << "\nEnter the value to search for: ";
                cin >> search;
                auto b_start = high_resolution_clock::now();
                binary_search(search);
                auto b_end = high_resolution_clock::now();
                double b_time = duration<double>(b_end - b_start).count();
                cout << "\nTime taken: " << b_time << " ms";
                break;
            }
            case '5': {
                long long int search;
                cout << "\nEnter the value to search for: ";
                cin >> search;
                auto i_start = high_resolution_clock::now();
                interpolation_search(search);
                auto i_end = high_resolution_clock::now();
                double i_time = duration<double>(i_end - i_start).count();
                cout << "\nTime taken: " << i_time << " ms";
                break;
            }
            case '6': {
                print_list();
                break;
            }
            default: {
                cout << "\nInvalid option, please try again.";
            }
        }
    }
}

int main() {
    user_input();
    return 0;
}