#include<bits/stdc++.h>
using namespace std;
template<class T>
struct ChainNode{
    T value;
    ChainNode<T> *next;
    ChainNode(T x){
        this->value=x;
    }
    ChainNode<T>(T x,ChainNode *next){
        this->value=x;this->next=next;      //插入一个新元素，并表明新元素的指向；
    }
    ChainNode(ChainNode *x){
        this->next=x;
        this->value=x->value;
    }    
};
template<class T>
class Chain_list{
    public:
        Chain_list(){

        }
        Chain_list(int capacity);
        Chain_list(const Chain_list<T>&);
        ~Chain_list();
        inline bool empty();
        inline T find(int k);
        inline int search(T x);
        inline void insert(int k,T x);
        inline void erase(int k);
        inline void output();
        inline void pushback(T x);
        inline void divide();
        int List_capacity;
        ChainNode<T> *first;
        ChainNode<T> *last;    
};
template<class T>
Chain_list<T>::Chain_list(int capacity){
    if(capacity<1) cout<<"The capacity is illegal!"<<endl;
    first=NULL;
    last=NULL;
    List_capacity=0;
}
template<class T>
Chain_list<T>::~Chain_list(){
    while(first!=NULL){
        ChainNode<T> *p=first->next;
        delete first;
        first=p;
    }
}
template<class T>
Chain_list<T>::Chain_list(const Chain_list<T> &thelist){
    List_capacity=thelist.List_capacity;
    if(List_capacity==0) {
        first=NULL;
        last=NULL;return ;
    }
    ChainNode<T> *p_first=thelist.first;
    ChainNode<T> *p_last=thelist.last;
    first=new ChainNode<T>(p_first->value);
    last=new ChainNode<T>(p_last->value);
    ChainNode<T> *target=thelist.first;
    ChainNode<T> *point=thelist.first;
    while(point!=NULL){
        target=new ChainNode<T>(point->value);
        target=target->next;
        point=point->next;
    }
    target->next=NULL;
}
template<class T>
bool Chain_list<T>::empty(){
    return (List_capacity==0)?0:1;
}
template<class T>
T Chain_list<T>::find(int k){
    ChainNode<T> *current=first;
    for(int i=0;i<k;i++) current=current->next;
    return current->value;
}
template<class T>
int Chain_list<T>::search(T x){
    ChainNode<T> *current=first;
    int now=0;
    while(now!=List_capacity&&current->value!=x){
        current=current->next;now++;
    }
    return (now==List_capacity)?-1:now;
}
template<class T>
void Chain_list<T>::insert(int k,T x){
    int index;
    ChainNode<T> *current=first;
    if(k<0) {cout<<"This is illeagl!"<<endl;return ;}
    if(k==0){                   //插入到表头
        first=new ChainNode<T>(x,first);
    }
    else{
        for(int index=0;index<k-1;index++) current=current->next; //插入位置的前驱元素
        current->next=new ChainNode<T>(x,current->next); //令前驱元素指向插入的新元素 此处的current->next是当前未插入时的那个
    }  
    List_capacity++;
}
template<class T>
void Chain_list<T>::erase(int k){
    ChainNode<T> *aim_node;
    if(k==0){
        aim_node=first;
        first=first->next;
    }
    else{
        ChainNode<T> *current=first;
        for(int index=0;index<k-1;index++) current=current->next;
        aim_node=current->next;
        current->next=current->next->next;
    }
    List_capacity--;
    delete aim_node;
}
template<class T>
void Chain_list<T>::pushback(T x){
    ChainNode<T> *newnode=new ChainNode<T>(x,NULL);
    if(first==NULL){
        first=last=newnode;
    }
    else{
        last->next=newnode;
        last=newnode;
    }
    List_capacity++;
}
template<class T>
void Chain_list<T>::output(){
    ChainNode<T> *current=first;
    for(int i=0;i<List_capacity;i++){ 
        cout<<current->value<<" ";
        current=current->next;
    }
    cout<<endl;
}
int n,m,element;
Chain_list<int> list_d(5000);
Chain_list<int> list_e(5000);   //链表e可拆分为e f e存储奇数，f存储偶数。
Chain_list<int> list_f(5000);
template<class T>
inline void generate_d(){
    for(int i=1;i<=m;i++){
        cin>>element;
        list_d.insert(0,element);
    }
    ChainNode<T> *empty_node=new ChainNode<T>(-3379);
    ChainNode<T> *current=list_d.first;
    for(int i=0;i<list_d.List_capacity-1;i++) current=current->next;
    cout<<"now "<<current->value<<" "<<empty_node->value<<endl;
    current->next=new ChainNode<T>(empty_node);
    empty_node->next=list_d.first;
    cout<<"the d is ";
    list_d.output();    
}
template<class T>
inline void split(){
    ChainNode<T> *current=list_d.first;
 /*  for(int i=0;i<list_d.List_capacity;i++){
        if(i%2==0) list_e.pushback(current->value);
        else list_f.pushback(current->value);
        current=current->next;
    }*/ 
    int i=0;
    while(current->value!=-3357&&i!=list_d.List_capacity){
        if(i%2==0) list_e.pushback(current->value);
        else list_f.pushback(current->value);
        current=current->next;   
        i++;
    }
    cout<<"Now the odd index of list_d is "<<endl;
    list_e.output();
    cout<<"Now the even index of list_d is "<<endl;
    list_f.output();
    
}
template<class T>
void Chain_list<T>::divide(){
    ChainNode<T> *current=list_d.first;
    int i=0;
    while(List_capacity){
        if(i%2==0) list_e.pushback(this->first->value);
        else list_f.pushback(this->first->value);
        erase(0);
        i++;
    }
    cout<<"Now the odd index of list_d is "<<endl;
    list_e.output();
    cout<<"Now the even index of list_d is "<<endl;
    list_f.output();
}
int main(){
    cin>>n>>m;
    generate_d<int>();list_d.divide();    
    //split<int>();
    system("pause");
    return 0;
}

/*
5 6
1 2 3 4 5
7 8 9 10 11 12
*/