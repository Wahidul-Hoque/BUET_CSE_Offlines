#include <iostream>
using namespace std;

int main() {
    
    int n,b,m;
    cin>>n>>b;
    int arr[n];
    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }  
    cin>>m;
    int blocked[n]={0};
    int seats=n/b;
    for(int i=0;i<b;i++){
        for(int j=0;j<seats;j++){
            int ind=i*seats+j;
            if(arr[ind]==1){
                blocked[ind]=1;
                if(j+1<seats){
                    blocked[ind+1]=1;
                }
            }
            else if(arr[ind]==2){
                blocked[ind]=1;
                if(j+1<seats){
                    blocked[ind+1]=1;
                }
                if(j>0){
                    blocked[ind-1]=1;
                }
            }
        }
    }
    int freeSeats=0;
    for(int i=0;i<n;i++){
        if(blocked[i]==0){
            freeSeats++;
        }
    }
    if(freeSeats<m){
        cout<<"false"<<endl;
    }
    else{
        cout<<"true"<<endl;
    }
     
    return 0;
    
}
