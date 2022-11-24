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
        this->value=x;this->next=next;      //插入一个新元素，并建立映射关系；
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
Chain_list<int> list_a(5000);
Chain_list<int> list_b(5000);
Chain_list<int> list_c(5000);
Chain_list<int> list_d(5000);
Chain_list<int> list_e(5000);   //链表e可拆分为e f e存储奇数，f存储偶数。
Chain_list<int> list_f(5000);
inline void generate_a(){
    for(int i=1;i<=n;i++){
        cin>>element;
        list_a.insert(0,element);
    }
    cout<<"the a is :";list_a.output();
 /*   for(int i=1;i<=n;i++){
        cin>>element;
        int index=rand()%(n-1);
        list_a.insert(index,element);
        cout<<"Now we insert an element "<<element<<" to the index of "<<index<<endl;
        cout<<"The answer is "<<endl;
        list_a.output();
    }*/
 //   cout<<"the a is "<<endl;
 //   list_a.output();
}
inline void generate_b(){
    for(int i=1;i<=m;i++){
        cin>>element;
        list_b.insert(0,element);
    }
    cout<<"the b is ";
    list_b.output();    
}
inline void generate_d(){
    for(int i=1;i<=m;i++){
        cin>>element;
        list_d.insert(0,element);
    }
    cout<<"the d is ";
    list_d.output();    
}
inline void meld(){
    int now=0;
    int rest_a=list_a.List_capacity;
    int rest_b=list_b.List_capacity;
    int all=rest_a+rest_b;
    while(list_c.List_capacity!=all){
        if((now%2==0&&rest_a!=0)||rest_b==0){
            cout<<"rest "<<rest_a<<" "<<rest_b<<endl;
            list_c.pushback(list_a.first->value);
            list_a.erase(0);
            rest_a--;

        }
        else{
            list_c.pushback(list_b.first->value);
            list_b.erase(0);
            rest_b--;
        }
        now++;
    }
    list_c.output();
}
template<class T>
inline void split(){
    ChainNode<T> *current=list_d.first;
    for(int i=0;i<list_d.List_capacity;i++){
        if(i%2==0) list_e.pushback(current->value);
        else list_f.pushback(current->value);
        current=current->next;
    }
    cout<<"Now the odd index of list_d is "<<endl;
    list_e.output();
    cout<<"Now the even index of list_d is "<<endl;
    list_f.output();
}
int main(){
    cin>>n>>m;
    generate_a();generate_b();meld();
    system("pause");
    return 0;
}

/*
5 6
1 2 3 4 5
7 8 9 10 11 12
*/