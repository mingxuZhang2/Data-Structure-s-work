#include<bits/stdc++.h>
using namespace std;
template<class T>
class LinearList{
    public:
        virtual ~LinearList(){

        };
        virtual bool empty()=0;
        virtual int size()=0;
        virtual T find(int index)=0;
        virtual int Located(T element)=0;
        virtual void erase(int index) =0;
        virtual void insert(int index,T element)=0;
};
template<class T>
class ArrayList:public LinearList<T>{
    public:
        ArrayList(){

        }
        ArrayList(const ArrayList<T>&);
        ArrayList(int inital_Capacity);
        ~ArrayList(){
            delete []element;
        }
        inline bool empty();
        inline int size();
        inline T find(int index);
        inline int Located(T aim_element);
        inline void erase(int index);
        inline void insert(int index,T element);
    //    inline int capacity();
        inline void output();
        void check_index(int index);
        T *element;
        int Array_length;           //数组长度
        int List_capacity;          //当前线性表存储元素个数
        int inital_capacity;
};
template<class T>
ArrayList<T>::ArrayList(int capacity){
    if(capacity<1){
        cout<<"The inital capacity should >1!"<<endl;
    }
    Array_length=capacity;
    element=new T[Array_length];
    inital_capacity=capacity;
}
template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& Thelist){
    Array_length=Thelist.Array_length;
    List_capacity=Thelist.List_capacity;
    element=new T[Array_length];
    copy(Thelist.element,Thelist.element+List_capacity,element);
}
template<class T>
bool ArrayList<T>::empty(){
    return List_capacity>0?1:0;
}
template<class T>
int ArrayList<T>::size(){
    return List_capacity;
}
template<class T>
void ArrayList<T>::check_index(int index){
    if(index>List_capacity||index<0) cout<<"The index is illegal,Please check it out!"<<endl;
}
template<class T>
T ArrayList<T>::find(int index){
    check_index(index);
    return element[index];
}
template<class T>
int ArrayList<T>::Located(T aim_element){
    int i;bool flag=0;
    for(i=0;i<List_capacity;i++) if(element[i]==aim_element) {flag=1;break;}
    return flag=1?i:-1;
}
template<class T>
void ArrayList<T>::erase(int index){
    check_index(index);
 //   for(int i=index+1;i<List_capacity;i++) element[i-1]=element[i]; List_capacity--;
    copy(element+index+1,element+List_capacity,element+index);
    element[--List_capacity].~T();
    if(List_capacity<Array_length/4){
        Array_length=max(Array_length/2,inital_capacity);
        T *new_array=new T[Array_length];
        copy(element,element+List_capacity,new_array);
        delete []element;
        element=new_array;
    }    
}
template<class T>
inline void expand(T *&a,int old,int new_length){
    if(new_length<0) cout<<"The index is illegal,Please check it out!"<<endl;
    T *new_array=new T[new_length];
    int number=min(old,new_length);
    copy(a,a+number,new_array);
    delete []a;
    a=new_array;
}
template<class T>
void ArrayList<T>::insert(int index,T aim_element){
    if(index>List_capacity||index<0) cout<<"The index is illegal,Please check it out!"<<endl;
    if(List_capacity==Array_length){
        expand(element,Array_length,Array_length*2);
        Array_length*=2;
    }
    copy_backward(element+index,element+List_capacity,element+List_capacity+1);
    element[index]=aim_element;List_capacity++;
   // for(int i=List_capacity-1;i>=index;i--) element[i+1]=element[i];
    //element[index]=aim_element;
    //List_capacity++;
}
template<class T>
void ArrayList<T>::output(){
    for(int i=0;i<List_capacity;i++) cout<<element[i]<<" ";
    cout<<endl;
}
int main(){
    int n;cin>>n;
    ArrayList<int> a(n);
    int option,element;
    cin>>option;
    for(int i=1;i<=option;i++){
        cin>>element;
        a.insert(a.List_capacity,element);
    }
    a.output();
    cin>>option;
    for(int i=1;i<=option;i++){
        int s=rand()%a.List_capacity;
        a.erase(s);
        cout<<"The index is "<<s<<endl;
        a.output();
    }
    system("pause");
    return 0;
}