#include<bits/stdc++.h>
using namespace std;
template<class T>
class priorityqueue{
    public:
        priorityqueue(int maxsize);
        ~priorityqueue(){

        }
        inline void create(T *nowarray,int size);
        inline void expand(T *&a,int oldlength,int newlength);
        inline void push(T k);
        inline void pop();
        inline void update();
        inline T top();
        inline int capacity(){
            return size;
        }
        inline bool empty(){
            return (size==0)?1:0;
        }
        int size;
        int maxsize;
        T *queue;
};
template<class T>
priorityqueue<T>::priorityqueue(int maxsize){
    size=0;
    this->maxsize=maxsize;
    queue=new T[maxsize*2+1];
}
template<class T>
T priorityqueue<T>::top(){
    return queue[1];
}
template<class T>
void priorityqueue<T>::expand(T *&a,int oldlength,int newlength){
    T *new_queue=new T[newlength];
    copy(a,a+oldlength,new_queue);
    delete []a;
    a=new_queue;
}
template<class T>
void priorityqueue<T>::push(T k){
    if(size==maxsize-1) expand(queue,size,size*2),maxsize=size*2;
    int current=++size;
    while(current!=1&&queue[current/2]<k){
        queue[current]=queue[current/2];
        current/=2;
    }
    queue[current]=k;
    /*
    
    */
}
template<class T>
void priorityqueue<T>::pop(){
    //queue[1].~T();
    T last=queue[size];
    queue[size]=queue[1];
    size--;
    int current=1;int son=2; //current存储从上之下遍历到第几个节点 son存储current的孩子 用于判断是否上移
    while(size>=son){
        if(son<size&&queue[son]<queue[son+1]) son++; //兄弟之间 son是最大的儿子
        if(last>=queue[son]) break; //如果到了插入位置 即当前的现在的值要大于下一层最大的孩子的值 说明可以插入到这个位置
        queue[current]=queue[son];
        current=son;son*=2; //搜索完这一层 开始迭代下一层
    }
    queue[current]=last;
    /*
    int current=1;int son=2;
    while(size>=son){
        if(queue[son]>queue[son+1]) queue[current]=queue[son],current=son;
        else queue[current]=queue[son+1],current=son+1;
        son=son*2;
    }
    queue[size]=minx;
    */
}
template<class T>
void priorityqueue<T>::create(T *nowarray,int size){
    queue=nowarray;this->size=size;
    for(int i=size/2;i>=1;i--){
        T now=queue[i];int son=i*2;//now是当前要上传的元素 i是当前更新到第几个节点 son为当前扫到节点的孩子
        while(son<=size){
            if(son<size&&queue[son]<queue[son+1]) son++;
            if(now>=queue[son]) break;
            queue[son/2]=queue[son];son*=2; //目前的now还太小了 不能当上面的父亲 那就继续往下扫，由于他一定会在下面出现，我们需要提前把位置预留出来
        }
        queue[son/2]=now; //最后我们只需要将当前更新元素放到符合要求的位置上即可
    }
}
int main(){
    int n;int b[500];
    priorityqueue<int> q(500);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>b[i];
    q.create(b,n);
    for(int i=1;i<=n;i++){
        cout<<q.top()<<" ";
        q.pop();
    }
    cout<<endl;
    for(int i=n;i>=1;i--) cout<<q.queue[i]<<" ";
    system("pause");
    return 0;
}
/*
10
8 9 7 4 5 6 1 3 2 10
*/