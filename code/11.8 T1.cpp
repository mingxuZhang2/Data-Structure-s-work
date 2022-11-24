#include<bits/stdc++.h>
#define MAXN 10050
using namespace std;
template<class T>
class double_edge_queue{
    public:
        double_edge_queue(int size){
            tail=head=now_size=0;maxsize=0;
            create(size);
        }
        ~double_edge_queue(){

        }
        inline void ask_left();
        inline void ask_right();
        inline void insert_front(int val);
        inline void insert_tail(int val);
        inline bool is_empty(){
            return (now_size==0)?1:0;
        }
        inline bool is_full(){
            return (now_size==maxsize)?1:0;
        }
        inline void delete_front();
        inline void delete_tail();
        inline void print();
        inline void create(int max_size);
        int head;
        int tail;
        int maxsize;
        int now_size;
        int *edge_queue;
};
template<class T>
void double_edge_queue<T>::print(){
    cout<<"Now the element in the deque is that: ";
    for(int i=head;i!=tail;i=(i+1)%maxsize){
        cout<<edge_queue[i]<<" ";
    }
    cout<<edge_queue[tail]<<endl;
}
template<class T>
void double_edge_queue<T>::create(int size){
    cout<<maxsize<<endl;
    if(maxsize!=0){ cout<<"you have been created a deque!"<<endl;return ;}
    maxsize=size;
    edge_queue=new int[maxsize];
    for(int i=0;i<maxsize;i++) edge_queue[i]=MAXN;
    cout<<"Now the deque has been created and each of the value is 10050"<<endl;
}
template<class T>
void double_edge_queue<T>::ask_left(){
    if(now_size==0) cout<<"EMPTY!"<<endl;
    else cout<<edge_queue[head]<<" "<<endl;
}
template<class T>
void double_edge_queue<T>::ask_right(){
    if(now_size==0) cout<<"EMPTY!"<<endl;
    else cout<<edge_queue[tail]<<" "<<endl;
}
template<class T>
void double_edge_queue<T>::insert_front(int k){
    if(this->is_full()==1) {cout<<"Now the deque is full!"<<endl;return ;}
    if(this->edge_queue[head]==MAXN){
        edge_queue[head]=k;
        now_size++;
        this->print();
        return ;
    }
    head=(head+maxsize-1)%maxsize;
    edge_queue[head]=k;
    now_size++;
    this->print();
}
template<class T>
void double_edge_queue<T>::insert_tail(int k){
    if(this->is_full()==1){ cout<<"Now the deque is full!"<<endl;return ;}
    if(this->edge_queue[tail]==MAXN){
        edge_queue[tail]=k;
        now_size++;
        this->print();
        return ;
    }
    tail=(tail+1)%maxsize;
    edge_queue[tail]=k;
    now_size++;
    this->print();
}
template<class T>
void double_edge_queue<T>::delete_front(){
    if(this->is_empty()==1) {cout<<"Now the deque is empty!You can not delete any element!"<<endl;return ;}
    int temp=edge_queue[head];
    edge_queue[head]=MAXN;
    if(head!=tail) head=(head+1)%maxsize;
    now_size--;
    this->print();
}
template<class T>
void double_edge_queue<T>::delete_tail(){
    if(this->is_empty()==1){ cout<<"Now the deque is empty!You can not delete any element!"<<endl;return ;}
    int temp=edge_queue[tail];
    edge_queue[tail]=MAXN;
    if(head!=tail) tail=(tail-1+maxsize)%maxsize;
    now_size--;
    this->print();
}
int main(){
    int a;
    double_edge_queue<int> dequ(10000);
    string s;
    while(s!="END"){
        cin>>s;
        if(s=="AddLeft"){
            cin>>a;
            dequ.insert_front(a);
            cout<<"qwq "<<a<<endl;
        }
        if(s=="AddRight"){
            cin>>a;
            dequ.insert_tail(a);
        }
        if(s=="IsFull"){
            cout<<(dequ.is_full()==1?"Yes":"No")<<endl;
        }
        if(s=="IsEmpty"){
            cout<<(dequ.is_empty()==1?"Yes":"No")<<endl;
        }
        if(s=="DeleteLeft") dequ.delete_front();
        if(s=="DeleteRight") dequ.delete_tail();
     }
    system("pause");
    return 0;
}
/*
AddLeft 1
AddLeft 2
DeleteRight
IsFull
DeleteLeft
IsEmpty
AddRight 3
AddLeft 2
AddRight 1
END
*/