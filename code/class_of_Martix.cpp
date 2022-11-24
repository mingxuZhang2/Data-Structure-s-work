#include<bits/stdc++.h>
using namespace std;
int n,m,a;
template<class T>
struct Node{
    T element;
    int index;int row;int col;
    Node<T> *next;
    Node(T val,int row,int col,Node *pr){
        this->element=val;this->col=col;this->row=row;this->next=pr;
    }
};
template<class T>
class lower_Martix{
    public:
        lower_Martix(int capacity);
        ~lower_Martix(){

        }
        inline void insert(int i,int j,T value);  //按行存储;
        inline void reverse();   //转置;
        inline T get(int i,int j); //输出第i行第j列的元素的值;
        inline void output();
        //inline void expand(int old_length,int new_length,Node<T> *&a);
        inline void test();
        lower_Martix<T> operator*(lower_Martix<T> a); //矩阵乘法
        lower_Martix<T> operator-(lower_Martix<T> a); //矩阵加法
        lower_Martix<T> operator+(lower_Martix<T> a); //矩阵减法
    private:
        int capacity;
        int length;
        Node<T> *element;
        int *colsize; //代表第i列所有的非0元素个数
        int *rowsize;
        int *the_next; //代表前i-1列有多少个元素，当前列的（第i列）的第一个非0元素应存储到the_next+1的位置
};
template<class T>
lower_Martix<T>::lower_Martix(int capacity){
    this->capacity=capacity;
    length=0;
    colsize=new int[5000];
    rowsize=new int[5000];
    the_next=new int[5000];
    element=NULL;
}
lower_Martix<int> martix_ans(1000);
template<class T>
lower_Martix<T> lower_Martix<T>::operator*(lower_Martix<T> a){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            T answer=0;
            for(int k=1;k<=n;k++){
                answer+=(this->get(i,k))*(a.get(k,j));
            }
            if(answer!=0) martix_ans.insert(i,j,answer);
        }
    }
    martix_ans.output();
    return *this;
}
lower_Martix<int> martix_ans_plus(1000);
template<class T>
lower_Martix<T> lower_Martix<T>::operator+(lower_Martix<T> a){
    for(int i=1;i<=n;i++){
        T answer=0;
        for(int j=1;j<=m;j++){
            answer=this->get(i,j)+a.get(i,j);
            if(answer!=0) martix_ans_plus.insert(i,j,answer);
        }
    }
    martix_ans_plus.output();
    return *this;
}
lower_Martix<int> martix_ans_jianfa(1000);
template<class T>
lower_Martix<T> lower_Martix<T>::operator-(lower_Martix<T> a){
        for(int i=1;i<=n;i++){
        T answer=0;
        for(int j=1;j<=m;j++){
            answer=this->get(i,j)-a.get(i,j);
            if(answer!=0) martix_ans_jianfa.insert(i,j,answer);
        }
    }
    martix_ans_jianfa.output();
    return *this;
}
template<class T>
void lower_Martix<T>::insert(int i,int j,T value){
  //  if(length>capacity+1) expand(length,2*length,this->element);
    /*
    this->element[++length].element=value;
    this->element[length].row=i;
    this->element[length].col=j;
    this->element[length].index=length;*/
    element=new Node<T>(value,i,j,element);
    length++;
}
template<class T>
T lower_Martix<T>::get(int i,int j){            //查找 时间复杂度为线性 可优化到log级别（二分查找）
   /*for(int k=1;k<=length;k++) rowsize[element[k].row]++;
    if(rowsize[i]==0) return 0;*/
    /*for(int k=1;k<=length;k++){
        if(element[k].row==i&&element[k].col==j) return element[k].element;
    }
    return 0;*/
    Node<T> *current=element;
    for(int k=1;k<=length;k++){
        if(current->col==j&&current->row==i) return current->element;
        current=current->next;
    }
    delete []current;
    return 0;
}
template<class T>
void lower_Martix<T>::output(){
    cout<<"The calu answer is that :"<<endl;
    Node<T> *current=element;
    for(int i=1;i<=length;i++){
        cout<<(current->row)<<" ";
        current=current->next;
    }
    cout<<endl;
    current=element;
    for(int i=1;i<=length;i++){
        cout<<current->col<<" ";
        current=current->next;
    }
    cout<<endl;
    current=element;
    for(int i=1;i<=length;i++){
        cout<<current->element<<" ";
        current=current->next;
    }
    cout<<endl;
}
template<class T>
void lower_Martix<T>::reverse(){
    
}
template<class T>
void lower_Martix<T>::test(){
    Node<T> *current=element;
    for(int i=1;i<=length;i++){
        cout<<(current->row)<<" ";
        current=current->next;
    }
    cout<<endl;
    current=element;
    for(int i=1;i<=length;i++){
        cout<<current->col<<" ";
        current=current->next;
    }
    cout<<endl;
    current=element;
    for(int i=1;i<=length;i++){
        cout<<current->element<<" ";
        current=current->next;
    }
    cout<<endl;
  /* for(int i=1;i<=m;i++){
        int aa,bb;cin>>aa>>bb;
        cout<<"the answer is :"<<this->get(aa,bb)<<endl;
    }*/ 
}
int main(){
    lower_Martix<int> martix_a(1000);
    lower_Martix<int> martix_b(1000);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        cin>>a;
        if(a!=0) martix_a.insert(i,j,a);
    }
    cout<<"qwq "<<endl;
    martix_a.test();
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        cin>>a;
        if(a!=0) martix_b.insert(i,j,a);
    }
    martix_a.operator*(martix_b);
    martix_a.operator+(martix_b);
    martix_a.operator-(martix_b);
    //martix.output();
    system("pause");
    return 0;
}
/*
4 8
0 0 0 2 0 0 1 0
0 6 0 0 7 0 0 3
0 0 0 9 0 8 0 0
0 4 5 0 0 0 0 0
*/

/*
4 4
1 2 3 4
1 2 3 4
1 2 3 4
0 1 2 0
0 0 1 2
0 5 9 8
1 2 3 5
0 6 5 1
*/
/*
expect:


3 40 48 37
3 40 48 37
3 40 48 37
2 9 15 18


1 2 4 6
1 7 12 12
2 4 6 9
0 7 7 1


1 2 2 2
1 -3 -6 -4
0 0 0 -1
0 -5 -3 -1
*/