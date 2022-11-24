#include<bits/stdc++.h>
using namespace std;
template<class T,class K>
struct Node{
    T element;
    K index;
    Node<T,K> *leftson;Node<T,K> *rightson;
    int num_lefttree;
    Node(T val,K index,Node *l,Node *r){
        this->element=val;this->index=index;
        leftson=l;rightson=r;
        num_lefttree=1;
    }
    Node(){
        num_lefttree=1;element=0,index=0,leftson=rightson=NULL;
    }
};
template<class T,class K>
class Binary_search_tree{
    public:
    Binary_search_tree(T val,K index,Node<T,K> *l,Node<T,K> *r);
    Binary_search_tree(int l);
    ~Binary_search_tree(){

    }
    inline void insert(K index,T element);
    inline void erase(K index);
    inline T find(K index);
    inline void output();
    Node<T,K> *root;
    int size;
};
template<class T,class K>
Binary_search_tree<T,K>::Binary_search_tree(T val,K index,Node<T,K> *l,Node<T,K> *r){
    root=new Node<T,K>(val,index,l,r);
    size=0;
}
template<class T,class K>
Binary_search_tree<T,K>::Binary_search_tree(int l){
    root=NULL;size=0;
}
template<class T,class K>
void Binary_search_tree<T,K>::insert(K index,T element){
    Node<T,K> *current=root;
    Node<T,K> *fa=NULL;
    while(current!=NULL){  //第一个循环找插入节点的前驱，即找到新建节点的父亲
        fa=current;
        if(current->index>index) current->num_lefttree++,current=current->leftson;
        else if(current->index<index) current=current->rightson;
        
    }
    Node<T,K> *newnode=new Node<T,K>(element,index,NULL,NULL);
    if(root==NULL) {root=newnode;size++;return ;}
    if(fa->index<newnode->index) fa->rightson=newnode;
    if(fa->index>newnode->index) fa->leftson=newnode;
    size++;
}
template<class T,class K>
T Binary_search_tree<T,K>::find(K index){
    Node<T,K> *current=root;
    while(current!=NULL){
        if(current->index==index) return current->element;
        else if(index<current->index) current=current->leftson;
        else current=current->rightson;
    }
    return '0';
}
template<class T,class K>
void dfs(Node<T,K> *current,int k){
    cout<<current->element<<" "<<current->num_lefttree<<" "<<k<<endl;
    if(k==current->num_lefttree){
        cout<<"The kth minimum is "<<current->element<<endl;
        return ;
    }
    if(k>=current->num_lefttree) dfs(current->rightson,k-current->num_lefttree);
    else if(k<current->num_lefttree) dfs(current->leftson,k);
}
template<class T,class K>
void Binary_search_tree<T,K>::erase(K index){
    Node<T,K> *current=root;  //待删除元素节点
    Node<T,K> *fa=NULL;
    while(current!=NULL){
        if(current->index==index) break; //找到current 即为要删除的节点
        fa=current;
        if(current->index==index) break; //找到current 即为要删除的节点
        else if(index<current->index) current=current->leftson,current->num_lefttree--;
        else current=current->rightson;
        if(current==NULL) break;
    }
    if(current->leftson==NULL&&current->rightson==NULL){  //当删除节点是叶节点时 直接删除即可
        if(fa->leftson==current) fa->leftson=NULL;
        else fa->rightson=NULL;
    }
    else if(current->leftson!=NULL&&current->rightson!=NULL){   //删除节点有两个孩子，需要遍历
        Node<T,K> *maximum=current->leftson;
        cout<<"Now is "<<maximum->index<<endl;
        while(maximum->rightson!=NULL&&maximum->leftson!=NULL){     //此循环目的是找到左子树最大的那个元素
            maximum=maximum->rightson;
        }
        Node<T,K> *newnode=new Node<T,K>(maximum->element,maximum->index,current->leftson,current->rightson);
        cout<<"the maximum is "<<maximum->index<<endl;
        if(current==root) {root=newnode;return ;}
        if(fa->leftson==current) fa->leftson=newnode,newnode->num_lefttree=current->num_lefttree;
        else fa->rightson=newnode;

    }
    else{  //当删除节点有一个孩子
        if(fa==NULL) this->root=current->rightson;
        else if(fa->leftson==current) fa->leftson=current->leftson;
        else if(fa->rightson==current) fa->rightson=current->rightson;
    }
    
    size--;
}
int main(){
    int n,m,op;
    int index;char ch;
    cin>>n;
    //cin>>index>>ch;
    Binary_search_tree<char,int> tree(0);
    for(int i=1;i<=n;i++){
        cin>>index>>ch;
        tree.insert(index,ch);
    }
    cin>>m;
    
    for(int i=1;i<=m;i++){
        cin>>op;
        /*tree.erase(op);
        cout<<"After erase the element is "<<tree.find(op)<<endl;
        cout<<"Now the root is "<<tree.root->element<<endl;*/
        dfs(tree.root,op);
        cout<<endl;
    }

    system("pause");
    return 0;
}
/*
11
30 a
5 b
2 d
40 c
35 e
80 f
32 g
60 h
85 i
31 j
33 k
4
40
60
35
30

*/