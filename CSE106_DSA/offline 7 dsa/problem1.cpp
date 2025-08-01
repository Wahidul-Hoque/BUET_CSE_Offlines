#include <iostream>
using namespace std;

int findMax(int arr[],int k, int max,int n){
    int ans=0,count=1;
    for(int i=0;i<n;i++){
        if(ans+arr[i]>max) {
            count++;
            ans=arr[i];
            if(count>k)return 0;
        }
        else {
            ans+=arr[i];
        }
    }
    return 1;
}
int main() {
    int n,k;
    cin>>n>>k;
    
    int arr[n];
    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }
    int max=arr[0];
    long long sum=0;
    for(int i=0;i<n;i++) {
        sum += arr[i];
        if(arr[i]> max) {
            max=arr[i];
        }
    }
    int l=max,r=sum;
    if(n<k){
        cout<<-1<<endl;
        return 0;
    }
    else if(n==k) {
        cout<<max<<endl;
        return 0;
    }
    else{
        while(l<r){
            int mid=(l+r)/2;
            if(findMax(arr,k,mid,n)) {
                r=mid;
            }
            else {
                l=mid+1;
            }
        }

    }
    cout<<l<<endl;
    return 0;

    
}
