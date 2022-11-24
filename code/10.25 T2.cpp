#include<bits/stdc++.h>
using namespace std;
template<class T>
class Stack{
    public:
        Stack(int capacity);
        ~Stack();
        inline bool empty();
        inline void pop();
        inline void push(T element);
        inline T top();
        inline int size();
        inline void expand(T *&a,int old,int new_length);
    private:
        int capacity;
        T *stack;
        int stack_top;    //stack_top存储当前栈顶是第几号元素，即其索引
};
Stack<char> s(10);
template<class T>
Stack<T>::Stack(int inital_capacity){
    capacity=inital_capacity;
    stack_top=0;
    stack=new T[capacity];
}
template<class T>
Stack<T>::~Stack(){
    delete []stack;
}
template<class T>
bool Stack<T>::empty(){
    return (stack_top==0)?0:1;
}
template<class T>
int Stack<T>::size(){
    return capacity;
}
template<class T>
T Stack<T>::top(){
    return stack[stack_top];
}
template<class T>
void Stack<T>::pop(){
    stack[stack_top--].~T();            //实现stack_top的内存回收
}
template<class T>
void Stack<T>::expand(T *&a,int old_length,int new_length){
    T *new_stack=new T[new_length];
    copy(a,a+old_length,new_stack);
    delete []a;
    a=new_stack;
    delete []new_stack;
    capacity=new_length;
}
template<class T>
void Stack<T>::push(T element){
    if(stack_top==capacity)  expand(stack,capacity,2*capacity);
    stack[++stack_top]=element;
}
char a;
string str;
Stack<char> s1(100);
Stack<char> s2(100);
inline void delete_all(){
    for(int i=0;i<str.length();i++){
        if(s1.top()!=a) cout<<s1.top()<<" ";
        s1.pop();
    }    
    cout<<endl;
    system("pause");
}
int main(){
    cin>>a;
    cin>>str;
    cout<<str.length()<<endl;
    for(int i=0;i<str.length();i++) s1.push(str[i]);
    delete_all();
}
