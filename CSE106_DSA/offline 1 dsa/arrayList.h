#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    int size;
    int capacity;
    int curr;

    // declare variables you need
} arrayList;

void init(arrayList* list)
{   
    list->array=(int*)malloc(2*sizeof(int));
    list->capacity=2;
    list->size=0;
    list->curr=0;
    // implement initialization
}

void free_list(arrayList* list)
{   
    free(list->array);
    free(list);
    init(list);
    // implement destruction of list
}

void increase_capacity(arrayList* list)
{   
    if((list->size +1)>(list->capacity)/2.0){
        list->capacity *=2;
        int* new_array=(int*)malloc(list->capacity * sizeof(int));
        for(int i=0;i<list->size;i++){
            new_array[i]=list->array[i];
        }
        free(list->array);
        list->array=new_array;
        printf("Capacity increased from %d to %d\n", list->capacity / 2, list->capacity);
    }
    // implement capacity increase
}

void decrease_capacity(arrayList* list)
{   
    if(list->size -1==0){
        list->capacity=2;
        int* new_array=(int*)malloc(list->capacity * sizeof(int));
        for(int i=0;i<list->size;i++){
            new_array[i]=list->array[i];
        }
        free(list->array);
        list->array=new_array;
        printf("Capacity decreased from %d to %d\n", list->capacity*2, list->capacity);
    }
    else if((list->size -1)<(list->capacity)/4.0){
        list->capacity/=2;
        int* new_array=(int*)malloc(list->capacity * sizeof(int));
        for(int i=0;i<list->size;i++){
            new_array[i]=list->array[i];
        }
        free(list->array);
        list->array=new_array;
        printf("Capacity decreased from %d to %d\n", list->capacity*2, list->capacity);
    }
    // implement capacity decrease
}

void print(arrayList* list)
{   
    printf("[");
    if(!list->size){
        printf(" . ]");
        printf("\n");
        return;
    }
    for(int i=0;i<list->size;i++){
        printf(" %d",list->array[i]); 
        if(i==list->curr)printf("|");   
    }
    printf(" ]");
    printf("\n");
    // implement list printing
}

void insert(int item, arrayList* list)
{   
    increase_capacity(list);
    for (int i = list->size; i > list->curr+1; i--) {
        list->array[i] = list->array[i - 1];
    }
    if(list->size)(list->curr)++;
    list->array[list->curr]=item;
    (list->size)++;
    print(list);
    // implement insert function
}

int delete_cur(arrayList* list)
{   
    int item=list->array[list->curr];
    decrease_capacity(list);    
    for(int i=list->curr;i<list->size-1;i++){
        list->array[i]=list->array[i+1];
    }
    if((list->size ==list->curr+1)  )list->curr--;
    if(list->curr<0)list->curr=0;

    (list->size)--;
    print(list);
    return item;
    // implement deletion of current index function
}

void append(int item, arrayList* list)
{   
    increase_capacity(list);
    list->array[list->size]=item;
    (list->size)++;
    print(list);
    // implement append function
}

int size(arrayList* list)
{   
    return list->size;
    // implement size function
}

void prev(int n, arrayList* list)
{       
    if(list->curr -n >=0){
        list->curr-=n;
        print(list);
    }
    else{
        list->curr=0;
        print(list);
    }
    // implement prev function
}

void next(int n, arrayList* list)
{   
    if(list->size==0){
        list->curr=0;
        print(list);
    }
    else if(list->curr +n <list->size){
        list->curr+=n;
        print(list);
    }
    else{
        list->curr=list->size-1;
        print(list);
    }
    // implement next function
}

int is_present(int n, arrayList* list)
{   
    for(int i=0;i<list->size;i++){
        if(list->array[i]==n)return 1;
    }
    return 0;
    // implement presence checking function
}

void clear(arrayList* list)
{   
    free(list->array);
    list->array=(int*)malloc(2*sizeof(int));
    list->capacity=2;
    list->size=0;
    list->curr=0;
    print(list);
    // implement list clearing function
}

void delete_item(int item, arrayList* list)
{   
    int f=0,ind=0;
    for(int i=0;i<list->size;i++){
        if(list->array[i]==item){
            f=1;ind=i;break;
        }
    }
    if(f){
        decrease_capacity(list);
        for(int i=ind;i<list->size-1;i++){
            list->array[i]=list->array[i+1];
        }
        if(list->size ==list->curr+1)list->curr--;
        (list->size)--;
        print(list);

    }
    else{
        printf("%d not found\n",item);
    }
    // implement item deletion function
}

void swap_ind(int ind1, int ind2, arrayList* list)
{   
    if(ind1==ind2)return;
    if(ind1 >= 0 && ind1 < list->size && ind2 >= 0 && ind2 < list->size){
        int t=list->array[ind1];
        list->array[ind1]=list->array[ind2];
        list->array[ind2]=t;
        print(list);
    }
    // implement swap function
}

// you can define helper functions you need