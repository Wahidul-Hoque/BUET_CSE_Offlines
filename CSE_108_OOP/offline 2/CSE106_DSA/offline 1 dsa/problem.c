#include <stdio.h>
//#include "arrayList.h"
 #include "linkedList.h"

int main()
{
    FILE* file = fopen("in_prob.txt", "r");
    if(file == NULL){
        return 1;
    }

    //arrayList dal, fl;
    linkedList dal, fl;
    init(&dal);
    init(&fl);
    // initialize the lists

    int func, param;
    while(fscanf(file, "%d", &func) == 1 && func != 0)
    {
        if(func == 1 && fscanf(file, "%d", &param) == 1){
            printf("Recruit %d\n", param);
            if(is_present(param,&fl)){
                printf("In the Foe list, cannot recruit\n");
                
            }
            else if(!is_present(param,&dal)){
                printf("DA list:\n");
                append(param,&dal);
            }
            // implement logic here
        }
        else if(func == 2 && fscanf(file, "%d", &param) == 1){
            printf("Fire %d\n", param);
            if(is_present(param,&dal)){
                printf("DA list:\n");
                delete_item(param,&dal);
                printf("Foe list:\n");
                append(param,&fl);
            }
            else{
                printf("%d not found in DA\n",param);
            }
            // implement logic here
        }
        else if(func == 3 && fscanf(file, "%d", &param) == 1){
            printf("Check %d\n", param);
            if(is_present(param,&dal))printf("Friend\n");
            else if(is_present(param,&fl))printf("Foe\n");
            else printf("Unknown\n");
            //implement logic here
        }
        else{
            break;
        }
        printf("\n");
    }
   free_list(&dal);
   free_list(&fl);
    // free memory
    
    return 0;
}