#include<bits/stdc++.h>
using namespace std;
int num;
inline void search(int *a,int l,int r,int aim){
    int mid=(l+r)/2;
    if(a[mid]==aim) return;num++;
    if(a[mid]<aim)  search(a,mid+1,r,aim);
    else search(a,l,mid,aim);
}
int main(){
    int n;int a[10050];
    int m;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    cin>>m;
    search(a,1,n,m);
    cout<<num;
    system("pause");
}