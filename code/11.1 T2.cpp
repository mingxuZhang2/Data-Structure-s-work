#include<bits/stdc++.h>
using namespace std;
#define prime 17
int n,m,a,b[50],op;
template<class T>
struct Node{
    T element;
    bool neverused;
    int length;
    int index;
    Node<T> *next;
    Node<T>(){
        this->next=NULL;
        this->element=0;
        this->index=0;
        this->neverused=0;
    }
    Node<T>(T element,int index,Node *pr){
        this->element=element;this->index=index;
        this->next=pr;
        this->neverused=0;
    }
};
template<class T>
struct chainnode{
    T element;
    Node<T> *first;
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
    inline void output(int index);
    chainnode<T> bucket[20];
    Node<T> *tail;
    int length;
};
template<class T>
Hash<T>::Hash(){
    length=0;
    for(int i=0;i<20;i++) {
        bucket[i].first=new Node<T>(0,0,NULL);
        bucket[i].element=0;
    }
    
}
template<class T>
int Hash<T>::calc(T element){
    return element%prime;
}
template<class T>
void Hash<T>::insert(T element,int index){
    length++;
    int Hash_num=calc(index);
    cout<<"Hash "<<Hash_num<<" "<<bucket[Hash_num].element<<" "<<(bucket[Hash_num].first->neverused)<<endl;
    if(bucket[Hash_num].first->neverused==0){
        bucket[Hash_num].first->neverused=1;
        bucket[Hash_num].element=element;
        bucket[Hash_num].first->index=index;return ;
    }
    Node<T> *current=bucket[Hash_num].first;
    Node<T> *before=current;
    while(1){
        before=current;
        cout<<"test "<<current->index<<" "<<current->next<<endl;
        if(current->index>=index||(current->next==NULL)) break;
        current=current->next;
        
    }
    Node<T> *new_node=new Node<T>(element,index,current->next);
    before->next=new_node;
}
template<class T>
void Hash<T>::erase(int index){
    int Hash_num=calc(index);
    if(bucket[Hash_num].first->index==index) {bucket[Hash_num].first->neverused=0;return ;}
    Node<T> *current=bucket[Hash_num].first->next;
    Node<T> *before=current;
    int now=0;
    while(1){
        if(now>1) before=before->next;
        current=current->next;
        if(current->index>=index||current->next==NULL) break;
        now++;
    }
    before->next=current;
}
template<class T>
T Hash<T>::search(int index){
    if(bucket[index].first->index==index) return bucket[index].element;
    Node<T> *current=bucket[index].first->next;
    while(current->index!=index) current=current->next;
    return current->element;
}
int main(){
    Hash<int> list;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a>>b[i];
        list.insert(a,b[i]);
    }
    cout<<"Now the list is here:"<<endl;
    cout<<"The fitst one is the value and the second one is index the third one is the array's figure"<<endl;
    for(int i=0;i<n;i++){
        cout<<list.search(b[i])<<" ";
    }
    cout<<endl;
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>b[i];
        list.erase(b[i]);
    }
    system("pause");
    return 0;
}