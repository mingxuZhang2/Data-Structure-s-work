#include<bits/stdc++.h>
using namespace std;
template<class T>
struct ChainNode{
    T element;
    ChainNode<T> *next;
    ChainNode(T val,ChainNode *pr){
        this->element=val;
        this->next=pr;
    }
    ChainNode(T val){
        this->element=val;
        this->next=NULL;
    }
};
template<class T>
class Stack{
    public:
        Stack(int capacity);
        ~Stack(){
            
        }
        inline bool empty();
        inline void pop();
        inline void push(T element);
        inline T top();
        inline int size();
    private:
        ChainNode<T> *stack_top; //指针，指向栈顶元素，链表的左端是栈顶元素
        int capacity;
};
template<class T>
Stack<T>::Stack(int capacity){
    stack_top=NULL;
    capacity=0;
}
template<class T>
bool Stack<T>::empty(){
    return (capacity==0?0:1);
}
template<class T>
void Stack<T>::pop(){
    if(capacity==0) {cout<<"The capacity is 0,you cannot pop it!"<<endl;return ;}
    stack_top=stack_top->next;
    capacity--;
}
template<class T>
void Stack<T>::push(T element){
    stack_top=new ChainNode<T>(element,stack_top);
    capacity++;
}
template<class T>
T Stack<T>::top(){
    return this->stack_top->element;
}
template<class T>
int Stack<T>::size(){
    return capacity;
}
Stack<char> s(100);
int main(){
    string a;
    cin>>a;
    if(a[0]==')'){
        cout<<"illegal input!"<<endl;
        return 0;
    }
    for(int i=0;i<a.length();i++){
        if(a[i]=='(') s.push('(');
        else{
            if(s.empty()==0){
                cout<<"illegal input!"<<endl;
                return 0;
            }
            s.pop();
        }
    }
    if(s.empty()==0) cout<<"The input is correct!"<<endl;
    else cout<<"illegal input!"<<endl;
    system("pause");
    return 0;
}