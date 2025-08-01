#ifndef HEAP_H
#define HEAP_H
#include<vector>
using namespace std;
class Heap{
private:
    vector<int> arr;
    int capacity;
    int heap_size;

    void heapify_down(int a){
        while(2*a<=heap_size){
            int largest=a;
            int left= 2*a;
            int right= 2*a +1;

            if(left<= heap_size && arr[left]>arr[a]){
                largest=left;
            }
            if(right<= heap_size && arr[right]>arr[largest]){
                largest=right;
            }
            if(largest==a)break;
            int t=arr[a];
            arr[a]=arr[largest];
            arr[largest]=t;
            a=largest;
        }        
    }
public:
    Heap(int size){
        capacity=size;
        heap_size=0;
        arr.resize(size+1);
        arr[0]=-1;
    }

    Heap(vector<int>& numbers){
        capacity=numbers.size();
        heap_size=numbers.size();
        arr.resize(capacity+1);
        for(int i=0;i<numbers.size();i++){
            arr[i+1]=numbers[i];
        }
        for(int i=heap_size/2;i>0;i--){
            heapify_down(i);
        }

    }
    void insert(int k){
        if(heap_size>=capacity)return;

        heap_size++;
        arr[heap_size]=k;
        int a=heap_size;
        while( a> 1 && arr[a/2]<arr[a]){
            int t=arr[a];
            arr[a]=arr[a/2];
            arr[a/2]=t;

            a=a/2;
        }
    }
    int getMax(){
        if(heap_size>0)return arr[1];
        else return -1;
    }
    void deleteKey(){
        if(heap_size==0)return;
        if(heap_size==1){
            heap_size--;
            return;
        }
        arr[1]=arr[heap_size];
        heap_size--;
        heapify_down(1);
    }
    int size(){
        return heap_size;
    }

};

//Heapsort function
void heapsort(vector<int>&v){
    Heap h(v);
    for(int i=0;i<v.size();i++){
        v[i]=h.getMax();
        h.deleteKey();
    }
}


#endif