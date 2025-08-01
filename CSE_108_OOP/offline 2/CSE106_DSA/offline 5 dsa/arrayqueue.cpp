#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    data= new int[initial_capacity];
    capacity=initial_capacity;
    front_idx=-1;
    rear_idx=-1;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    clear();
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    if((rear_idx+1)%capacity==front_idx){
        resize(2*capacity);
    }
    if(empty()){
        front_idx=0;
    }
    rear_idx=(rear_idx+1)%capacity;
    data[rear_idx]=item;

}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element
    if(empty()){
        cout<<"Queue is empty. Can't dequeue from an empty queue."<<endl;
        return -1;
    }
    int r= data[front_idx];
    if(size()==1){
        capacity=2;
        front_idx=-1;
        rear_idx=-1;
    }
    else{
        front_idx=(front_idx+1)%capacity;
        if(((double)size())<=capacity/4.0){
            resize(capacity/2);
        }
    }
    return r;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    if(data){
        delete[] data;
        capacity=2;
        front_idx=-1;
        rear_idx=-1;
        data=new int[2];
    }
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    if(empty())return 0;
    if(rear_idx>=front_idx)return rear_idx-front_idx+1;
    else return capacity - (front_idx-rear_idx-1);
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    if(empty()){
        cout<<"Queue is empty. No front element."<<endl;
        return -1;
    }
    return data[front_idx];
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    if(empty()){
        cout<<"Queue is empty. No back element."<<endl;
        return -1;
    }
    return data[rear_idx];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    return rear_idx==-1;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    string res = "<";
    if(!empty()){
        int i=front_idx;
        while(true){
            res+=to_string(data[i]);
            if(i==rear_idx)break;
            res+=", ";
            i=(i+1)%capacity;
        }
    }
    res+="|";
    return res;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
    int* new_arr=new int[new_capacity];
    int n=size();
    for(int i=0;i<n;i++){
        new_arr[i]=data[(front_idx+i)%capacity];
    }
    delete[] data;
    data=new_arr;
    capacity=new_capacity;
    front_idx=0;
    rear_idx=n-1;
    
}

int ArrayQueue::getCapacity() const
{
    return capacity;
    // TODO: Return the current capacity of the queue
}