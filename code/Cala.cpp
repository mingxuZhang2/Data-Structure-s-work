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
    stack=new T[5000];
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
void Stack<T>::push(T element){
   // if(stack_top==capacity)  expand(stack,capacity,2*capacity);
    stack[++stack_top]=element;
}

int main(){
    int ans;
    Stack<int> s(100);
    string ss;
    cin>>ss;
    int now=0;
    while(now!=ss.length()){
        int top=0;
        int mid=0;
        if(ss[now]=='@') break;
        int current=0;
        while(ss[now]>='0'&&ss[now]<='9'){
            current=current*10+ss[now]-'0';
            now++;
        }
        if(ss[now]=='.') s.push(current);
        if(ss[now]=='+'){
            top=s.top();s.pop();
            mid=top+s.top();
            s.pop();s.push(mid);
        }
        else if(ss[now]=='*'){
            top=s.top();s.pop();
            mid=top*s.top();
            s.pop();s.push(mid);
        }
        else if(ss[now]=='-'){
            top=s.top();s.pop();
            mid=s.top()-top;
            s.pop();s.push(mid);
        }
        else if(ss[now]=='/'){
            top=s.top();s.pop();
            mid=s.top()/top;
            s.pop();s.push(mid);
        }
        now++;
    }
    cout<<s.top()<<endl;
    system("pause");
    return 0;
}