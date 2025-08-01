#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0
    front_node=nullptr;
    rear_node=nullptr;
    current_size=0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size
    Node* newnode=new Node(item);
    if(empty()){
        front_node=newnode;
        rear_node=newnode;
    }
    else{
        rear_node->next=newnode;
        rear_node=newnode;
    }
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    if(empty()){
        cout<<"Queue is empty. Can't dequeue from an empty queue."<<endl;
        return -1;
    }
    int r=front_node->data;
    Node* temp= front_node;
    front_node=front_node->next;
    delete temp;
    current_size--;
    if(front_node==nullptr){
        rear_node=nullptr;
    }
    return r;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    while(front_node!=nullptr){
        Node* temp = front_node;
        front_node=front_node->next;
        delete temp;
    }
    rear_node=nullptr;
    current_size=0;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
    if(empty()){
        cout<<"Queue is empty. No front element."<<endl;
        return -1;
    }
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
    if(empty()){
        cout<<"Queue is empty. No back element."<<endl;
        return -1;
    }
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return front_node==nullptr;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
    string res = "<";
    Node* curr=front_node;
    while(curr!=nullptr){
        res+=to_string(curr->data);
        if(curr->next!=nullptr)res+=", ";
        curr=curr->next;
    }
    res+="|";
    return res;
}
