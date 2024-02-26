#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

struct testFunc{
    bool operator()(int val){
        return (val % 2 == 0);
    }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Testing llfilter:" << endl;
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    testFunc t1;
    Node* new_head = llfilter(head, t1);
    cout << "Filtered list: ";
    print(new_head);

    cout << "----------" << endl;
    cout << "Testing llpivot:" << endl;
    cout << "Original list: ";
    print(head);


    Node* small_head = new Node(1, NULL);
    Node* large_head = new Node(1, NULL);

    llpivot(head, small_head, large_head, 8);
    cout << "Smaller list: ";
    print(small_head);
    cout << "Larger list: ";
    print(large_head);

    dealloc(head);
    dealloc(new_head);
    dealloc(small_head);
    dealloc(large_head);


    return 0;

}
