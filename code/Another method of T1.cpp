#include<bits/stdc++.h>
using namespace std;
int n,m;
bool vis[10000];
int a[10050];
inline void func(){
    int now=1;
    int index=1;
    int num=0;
    while(num!=n){
        if(vis[index]!=1){
            if(now%m==0){cout<<index<<" ";num++;vis[index]=1;}
            now++;
        }
        index++;
        if(index>=9) index=1;
    } 
}

int main(){
    cin>>n>>m;
    func();
    system("pause");
    return 0;
}