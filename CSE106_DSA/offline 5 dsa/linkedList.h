#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{   
    node* head;
    node* tail;
    node* curr;
    int size;
    // declare head, tail, cur and other variables you need
} linkedList;

void init(linkedList* list)
{   
    list->head=NULL;
    list->tail=NULL;
    list->curr=NULL;
    list->size=0;
    // implement initialization
}

void free_list(linkedList* list)
{   
    node* temp=list->head;
    while(temp!=NULL){
        node* del=temp;
        temp=temp->next;
        free(del);
    }
    init(list);
    // implement destruction of list
}

void print(linkedList* list)
{   
    printf("[ ");
    if(!list->size){
        printf(". ]");
        printf("\n");
        return;
    }
    node* temp=list->head;
    while(temp!=NULL){
        printf("%d ",temp->element);
        if(temp==list->curr){
            printf("\b| ");
        }
        temp=temp->next;
    }
    if(list->curr==NULL)printf("| ");
    printf("]\n");
    // implement list printing
}

void insert(int item, linkedList* list)
{   
    node* newn =(node*)malloc(sizeof(node));
    newn->element=item;
    newn->next=NULL;
    newn->prev=NULL;
    if(list->size==0){
        list->head=newn;
        list->tail=newn;
        list->curr=newn;       
    }
    else{
        newn->next=list->curr->next;
        newn->prev=list->curr;
        //list->curr->next=newn;
        if(list->curr->next)list->curr->next->prev=newn;
        else list->tail=newn;
        
        list->curr->next=newn;
        list->curr=newn;

    }
    list->size++;
    //print(list);

    // implement insert function
}

int delete_cur(linkedList* list)
{   
    node* temp=list->curr;
    int item=temp->element;
    if(temp->prev){
        temp->prev->next=temp->next;
    }
    else list->head=temp->next;
    if(temp->next){
        temp->next->prev=temp->prev;
    }
    else{
        list->tail=temp->prev;
    }
    if(temp->next)list->curr=temp->next;
    else list->curr=temp->prev;
    free(temp);
    list->size--;
    
    return item;
    // implement deletion of current index function
}

void append(int item, linkedList* list)
{   
    node* newn=(node*)malloc(sizeof(node));
    newn->element=item;
    newn->next=NULL;
    newn->prev=list->tail;
    if(list->tail)list->tail->next=newn;
    else list->head=newn;
    list->tail=newn;
    if(list->curr==NULL)list->curr=newn;
    list->size++;
    //print(list);
    // implement append function
}

int size(linkedList* list)
{   
    return list->size;
    // implement size function
}



int is_present(int n, const linkedList* list)
{   
    node* temp=list->head;
    while(temp){
        if(temp->element==n)return 1;
        temp=temp->next;
    }
    return 0;
    // implement presence checking function
}

void clear(linkedList* list)
{   
    free_list(list);
    //print(list);
    // implement list clearing function
}

void delete_item(int item, linkedList* list)
{   
    node* temp = list->head;
    while (temp) {
        if (temp->element == item){
            if(temp==list->curr){
                delete_cur(list);
            }
            else{
                if(temp->prev)temp->prev->next=temp->next;
                else list->head=temp->next;
                if(temp->next)temp->next->prev=temp->prev;
                else list->tail=temp->prev;
                free(temp);
                list->size--;
                
            }
            return;
        }
        temp=temp->next;
    }
    printf("%d not found\n",item);
    // implement item deletion function
}



// you can define helper functions you need