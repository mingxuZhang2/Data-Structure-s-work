#include<bits/stdc++.h>
using namespace std;
#define prime 17
int n,m,a,b,op;
template<class T>
struct Node{
    T element;bool neverused;
    int index;
};
template<class T>
class Hash{
    public:
    Hash();
    ~Hash(){

    }
    inline void insert(T element,int index);
    inline void erase(int index);
    inline T search(int index);
    inline int calc(T element);
    Node<T> bucket[1000];
    Node<T> new_bucket[1000];
    int length;
    inline void resort();
};
template<class T>
Hash<T>::Hash(){
    length=0;
}
template<class T>
int Hash<T>::calc(T element){
    return element%prime;
}
template<class T>
void Hash<T>::insert(T element,int index){
    length++;
    int Hash_num=calc(index);
    if(bucket[Hash_num].neverused==0){
        bucket[Hash_num].neverused=1;
        bucket[Hash_num].element=element;
        bucket[Hash_num].index=index;return ;
    }
    int now=Hash_num;
    while(bucket[now].neverused==1) now++;
    bucket[now].neverused=1;
    bucket[now].element=element;
    bucket[now].index=index;
}
template<class T>
void Hash<T>::erase(int index){
    int Hash_num=calc(index);
    if(bucket[Hash_num].index==index) {bucket[index].neverused=0;return ;}
    int now=Hash_num;
    while(bucket[now].index!=index) now++;
    bucket[now].neverused=0;
}
template<class T>
T Hash<T>::search(int index){
    while(1){
        if(bucket[index].index==index&&bucket[index].neverused!=0) return bucket[index].element;
        if(bucket[index].index!=index&&bucket[index].neverused!=0) index++;
        if(index==length||bucket[index].neverused==0) return -1; 
    }
}
template<class T>
void Hash<T>::resort(){
    copy(bucket,bucket+16,new_bucket);
    memset(bucket,0,sizeof(bucket));
    for(int i=0;i<16;i++) 
    if(new_bucket[i].neverused==1) insert(new_bucket[i].element,new_bucket[i].index);
    
}
int main(){
    Hash<int> list;
    memset(list.bucket,0,sizeof(list.bucket));
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        list.insert(a,b);
    }
    cout<<list.length<<endl;
    cout<<"Now the list is here:"<<endl;
    cout<<"The fitst one is the value and the second one is index the third one is the array's figure"<<endl;
    for(int i=0;i<16;i++){
        cout<<list.bucket[i].element<<" "<<list.bucket[i].index<<" "<<list.bucket[i].neverused<<endl;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>b;
        list.erase(b);
    }
    cout<<"Now the list is here:"<<endl;
    cout<<"The fitst one is the value and the second one is index the third one is the array's figure"<<endl;
    for(int i=0;i<16;i++){
        cout<<list.bucket[i].neverused<<" "<<list.bucket[i].element<<" "<<list.bucket[i].index<<endl;
    }
    list.resort();
    cout<<"After resort the list,the answer is: "<<endl;
    cout<<"The first one is the neverused and the second one is element and the last one is array's figure"<<endl;
    for(int i=0;i<16;i++){
        cout<<list.bucket[i].neverused<<" "<<list.bucket[i].element<<" "<<i<<endl;
    }
    system("pause");
    return 0;
}
/*
14
10 0
20 17
30 34
40 68
50 2
70 3
60 20
80 5
90 100
100 51
110 55
120 78
130 14
140 98

10
17
0
34
68
2
3
14
78
55
14


*/