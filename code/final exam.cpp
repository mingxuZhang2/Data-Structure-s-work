#include<bits/stdc++.h>
using namespace std;
int a[10050],b[10050];
int n;
inline int erfen(int i){
    if(max(a[i],b[n-1-i])<min(a[i+1],b[n-i])) return i;
    else erfen((i+1)/2);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int i=erfen(n-1);
    cout<<min(a[i+1],b[n-i])<<endl;
    system("pause");
    return 0;
}
/*
6
1 3 5 7 9 11
2 6 9 11 13 17

1 2 3 5 6 7 9 9 11 11 13 17

ans=7

6
1 2 3 4 5 6
7 8 9 10 11 12
*/