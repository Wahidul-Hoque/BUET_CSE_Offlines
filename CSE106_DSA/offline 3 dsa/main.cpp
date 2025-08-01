#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" ;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    //freopen("test_input_1.txt", "r", stdin); // Test Case 1
    freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output_2.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    int id_array[10001]={0};
    for (int i = 1; i <= N; i++)
    {
        cout<<"Operation "<<i;
        int number,id,timestamp;
        cin>>number;
        if(number==1){
            cin>>id>>timestamp;
            cout<<" (Arrival "<<id<<" "<<timestamp<<"): ";
            
            id_array[id]=timestamp;
            if(id_array[0]==0){
                if(Q1->empty() && Q2->empty()){
                    if(randomQueue()==1){
                        Q1->enqueue(id);
                    }
                    else{
                        Q2->enqueue(id);
                    }
                }
                else if(Q1->empty()){
                    Q1->enqueue(id);
                }
                else if(Q2->empty()){
                    Q2->enqueue(id);
                }
                else{
                    if(id_array[Q1->back()]<id_array[Q2->back()]){
                        Q1->enqueue(id);
                    }
                    else Q2->enqueue(id);
                }
            }
            else{
                Q->enqueue(id);
            }
        }
        else if(number==2){
            cin>>id>>timestamp;
            cout<<" (Leave "<<id<<" "<<timestamp<<"): ";
            id_array[id]=0;
            int m=Q1->size(),n=Q2->size(),o=Q->size();
            if(id_array[0]==0){

                for(int i=0;i<m;i++){
                    int a= Q1->dequeue();
                    if(a!=id)Q1->enqueue(a);
                }
                for(int i=0;i<n;i++){
                    int a= Q2->dequeue();
                    if(a!=id)Q2->enqueue(a);
                }
            }
            else{
                for(int i=0;i<o;i++){
                    int a= Q->dequeue();
                    if(a!=id)Q->enqueue(a);
                }
            }
        }
        
        else if(number==3){
            cout<<" (Merge): ";
            if(id_array[0]==0){
                id_array[0]=1;
                while(Q1->size()!=0 ||  Q2->size()!=0){
                    if(Q1->size()!=0 &&  Q2->size()!=0){
                        if(id_array[Q1->front()]<id_array[Q2->front()]){
                            Q->enqueue(Q1->dequeue());
                        }
                        else{
                            Q->enqueue(Q2->dequeue());
                        }
                    }
                    else if(Q1->size()!=0){
                        Q->enqueue(Q1->dequeue());
                    }
                    else if(Q2->size()!=0){
                        Q->enqueue(Q2->dequeue());
                    }             
                }
            }
        }
        else if(number==4){
            cout<<" (Split): ";
            if(id_array[0]==1){
                id_array[0]=0;
                int gg = (Q->size()/2);
                for(int i=0;i<gg;i++){
                    Q1->enqueue(Q->dequeue());
                    Q2->enqueue(Q->dequeue());
                }
                if(Q->size()==1)Q1->enqueue(Q->dequeue());
            }
        }
        else{
            cout<<" (Departure): ";
            if(id_array[0]==0){
                if(!Q1->empty() && !Q2->empty()){
                    if(randomQueue()==1){
                        int a=Q1->dequeue();
                    }
                    else{
                        int a=Q2->dequeue();
                    }
                }
                else if(!Q2->empty()){
                    int a=Q2->dequeue();
                }
                else if(!Q1->empty()){
                    int a=Q1->dequeue();
                }
            }
            else{
                int a=Q->dequeue();
            }
        }
        // TODO: Edit here to add your own logic
        cout<<"\n"<<"Q1: "<<Q1->toString();
        cout<<"\n"<<"Q2: "<<Q2->toString();
        cout<<"\n"<<"Q : "<<Q->toString()<<endl;
        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}