#include<bits/stdc++.h>
using namespace std;
template<class T>
struct ChainNode{
    T value;
    T index;
    ChainNode<T> *next;
    ChainNode(T x){
        this->value=x;
    }
    ChainNode<T>(T index,T x,ChainNode *next){
        this->index=index;
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
        Chain_list(int capacity);
        ~Chain_list(){
        }
        inline void erasee(T k);
        inline void pushback(T x,T index);
        inline void func();
        int List_capacity;
        ChainNode<T> *first;
        ChainNode<T> *last; 
        int index;   
};
template<class T>
Chain_list<T>::Chain_list(int capacity){
    if(capacity<1) cout<<"The capacity is illegal!"<<endl;
    first=NULL;
    last=NULL;
    List_capacity=0;
}
template<class T>
void Chain_list<T>::erasee(T k){
    ChainNode<T> *aim_node;
    ChainNode<T> *current=first;
    ChainNode<T> *temp=first;
    for(int i=0;i<List_capacity;i++){
        if(i>1) temp=temp->next;
        if(current->value==k){
            if(i==0){
                last->next=first->next;
                List_capacity--;
                return ;
            }
            if(i==List_capacity-1){
                aim_node=current->next;
                last=temp;
                temp->next=current->next;
                List_capacity--;
                return ;   
            }
            aim_node=current->next;
            temp->next=current->next;
            List_capacity--;
            return ;
        }   
        current=current->next;
    }
}
template<class T>
void Chain_list<T>::pushback(T x,T index){
    ChainNode<T> *newnode=new ChainNode<T>(index,x,NULL);
    if(first==NULL){
        first=last=newnode;
    }
    else{
        last->next=newnode;
        last=newnode;
    }
    List_capacity++;
}
Chain_list<int> List(1000);
int n,m,element;
template<class T>
void Chain_list<T>::func(){
    ChainNode<T> *current=first;
    for(int i=0;i<List_capacity-1;i++){
        current=current->next;
    }
    current->next=first;
    int now=1;
    current=first;
    while(this->List_capacity!=1){
        if(now%m==0){
            cout<<current->value<<" ";
            erasee(current->index);

        }
        current=current->next;
        now++;
    } 
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        List.pushback(i,i);
    }
    List.func();
    system("pause");
    return 0;
}