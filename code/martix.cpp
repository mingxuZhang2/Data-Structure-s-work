#include<bits/stdc++.h>
using namespace std;
int n,m,a;
template<class T>
class lower_Martix{
    public:
        lower_Martix(int capacity);
        ~lower_Martix(){

        }
        inline void insert(int i,int j,T value);  //按行存储;
        inline void reverse();
        inline T get(int i,int j);
        inline void output();
        inline void expand(int old_length,int new_length,T *&a);
        inline void test();
    private:
        int capacity;
        int length;
        T *element;
};
template<class T>
lower_Martix<T>::lower_Martix(int capacity){
    this->capacity=capacity;
    length=0;
    element=new T[capacity];
}
template<class T> 
void lower_Martix<T>::expand(int old_length,int new_length,T *&a){
    T *new_martix=new T[new_length];
    copy(a,a+old_length,new_martix);
    delete []a;
    a=new_martix;
    capacity=new_length;
}
template<class T>
void lower_Martix<T>::insert(int i,int j,T value){
    if(length>capacity+1) expand(length,2*length,element);
    int now=i*(i-1)/2;
    element[now+j]=value;
    length++;
}
template<class T>
T lower_Martix<T>::get(int i,int j){
    int now=i*(i-1)/2;
    return element[now+j];
}
template<class T>
void lower_Martix<T>::output(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cout<<get(i,j)<<" ";
        cout<<endl;
    }
}
template<class T>
void lower_Martix<T>::reverse(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j<i) cout<<0<<" ";
            else cout<<get(j,i)<<" ";
        }
        cout<<endl;
    }
}
template<class T>
void lower_Martix<T>::test(){
    for(int i=1;i<=length;i++) cout<<element[i]<<" ";
}
int main(){
    lower_Martix<int> martix(10);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        cin>>a;
        if(a!=0) martix.insert(i,j,a);
    }
    martix.reverse();
    //martix.output();
    system("pause");
    return 0;
}
/*
4 4
1 0 0 0
2 3 0 0
4 5 6 0
7 8 9 10
*/