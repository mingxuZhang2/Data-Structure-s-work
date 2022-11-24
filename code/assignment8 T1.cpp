#include<bits/stdc++.h>
using namespace std;
template<class T,class K>
struct Node{
    T element;     //element为平衡树节点所对应的元素
    K index;        //index为关键字（索引）
    int deep;      //当前节点的树高
    Node<T,K> *leftson;Node<T,K> *rightson;
    int left_high;int right_high; //左子树高度 右子树高度
    int balance_factor; //平衡因子 定义为current->left_high-current->right_high;
    int highth; //树高
    Node(T val,K index,Node *l,Node *r){    
        this->element=val;this->index=index; 
        leftson=l;rightson=r;deep=0;this->balance_factor=0;
    }
    Node(){
        element=0,index=0,leftson=rightson=NULL;deep=0;
    }
};
template<class T,class K>
class AVL{
    public:
    AVL(T val,K index,Node<T,K> *l,Node<T,K> *r);
    AVL(int l);
    ~AVL(){

    }
    inline void insert(K index,T element);  //将关键字为index 元素值为element的元素插入AVL
    inline void erase(K index);      //删除关键字为index的元素
    inline T find(K index);            //查找关键字为index的元素
    inline int calc_deep();  //计算AVL树的高度 时间复杂度为logn级别
    inline T nearest(); //返回AVL中与根节点最近的节点
    inline void change_factor(K index); //修改平衡因子 index是最后插入元素的关键字 要更改这条路径的bf
    inline void change_high(K index);//修改从根节点到index这条路径上所有节点的树高
    inline void splay_LL(Node<T,K> *A);
    inline void splay_RR(Node<T,K> *A);
    inline void splay_LR(Node<T,K> *A);  //其中A是目前bf为2或者-2的节点
    inline void splay_RL(Node<T,K> *A);
    inline Node<T,K>* search_fa(Node<T,K> *A); //寻找A的父亲;
    inline int get_high(Node<T,K> *now);
    Node<T,K> *root;
    int size;
};
template<class T,class K>
int AVL<T,K>::get_high(Node<T,K> *now){
    return max(now->left_high,now->right_high)+1,
}
template<class T,class K>
AVL<T,K>::AVL(T val,K index,Node<T,K> *l,Node<T,K> *r){
    root=new Node<T,K>(val,index,l,r);
    size=0;
}
template<class T,class K>
AVL<T,K>::AVL(int l){
    root=NULL;size=0;
}
template<class T,class K>
void AVL<T,K>::change_high(K index){
    Node<T,K> *current=root;
    while(current->index!=index){
        if(current->index<index) current->right_high++,current=current->rightson;
        else current->left_high++,current=current->leftson;
    }
}
template<class T,class K>
void AVL<T,K>::change_factor(K index){
    Node<T,K> *current=root;
    while(current->index!=index){
        current->balance_factor=current->left_high-current->right_high;
        if(current->index<index) current=current->rightson;
        else current=current->leftson;
    }
    return ;
}   
template<class T,class K>
Node<T,K> *AVL<T,K>::search_fa(Node<T,K> *A){
    Node<T,K> *current=root;
    while(current->index!=A->index){
        if(current->index<A->index) current=current->rightson;
        if(current->index<A->index) current=current->leftson;
    }
    return current;
}
template<class T,class K>
int AVL<T,K>::calc_deep(){
    Node<T,K> *current=root;
    int ans=0;
    while(1){
        ans++;
        if(current->leftson==current->rightson==NULL) return ans;
        if(current->balance_factor==1) current=current->leftson;
        else current=current->rightson;
    }
}
template<class T,class K>
void AVL<T,K>::splay_LL(Node<T,K> *A){
    Node<T,K> *fa=search_fa(A);
    Node<T,K> *now=A->leftson;
    Node<T,K> *temp_left=now->leftson;
    Node<T,K> *temp_right=now->rightson;
    if(fa->leftson==A){
        fa->leftson=now;
        now->rightson=A;
        A->leftson=temp_right;
        now->leftson=temp_left;
    }
    if(fa->rightson==A){
        fa->rightson=now;
        now->rightson=A;
        A->leftson=temp_right;
        now->leftson=temp_left;
    }
    now->left_high=max(temp_left->left_high,temp_left->right_high)+1;
    A->left_high=max(temp_right->left_high,temp_right->right_high)+1;
    A->right_high=A->right_high

}
template<class T,class K>
void AVL<T,K>::splay_LR(Node<T,K> *A){
    
}
template<class T,class K>
void AVL<T,K>::splay_RR(Node<T,K> *A){
    Node<T,K> *fa=search_fa(A);
    Node<T,K> *now=A->leftson;
    Node<T,K> *temp_left=A->leftson->leftson;
    Node<T,K> *temp_right=A->leftson->rightson;
    if(fa->leftson==A){
        fa->leftson=now;
        now->leftson=A;
        A->rightson=temp_left;
        now->rightson=temp_right;
    }
    if(fa->rightson==A){
        fa->rightson=now;
        now->leftson=A;
        A->rightson=temp_left;
        now->rightson=temp_right;
    }
    now->balance_factor=0;
    A->balance_factor=0;
    A->left_high=
}
template<class T,class K>
void AVL<T,K>::splay_RL(Node<T,K> *A){
    
}
template<class T,class K>
void AVL<T,K>::insert(K index,T element){
    Node<T,K> *current=root;
    Node<T,K> *fa=NULL;   //新建节点的父节点
    Node<T,K> *A=NULL;      //A是最后一个bf为1/-1的节点 如果需要splay 只可能是该节点需要
    while(current!=NULL){  //找插入节点的前驱，即找到新建节点的父亲
        fa=current;
        if(abs(current->balance_factor)==1) A=current;
        if(current->index>index) current=current->leftson,current->deep=fa->deep+1;
        else if(current->index<index) current=current->rightson,current->deep=fa->deep+1;
    }
    if(root==NULL) {root=newnode;size++;return ;}
    Node<T,K> *newnode=new Node<T,K>(element,index,NULL,NULL);
    //只有插入到叶节点时才会改变当前路径上所有节点的树高，否则只改变平衡因子
    if(A==NULL){  //如果不存在bf为-1/1的节点 那么插入后树一定平衡 直接更新bf即可
        if(fa->index<newnode->index&&fa->leftson==NULL) fa->rightson=newnode,change_high(newnode->index);
        if(fa->index<newnode->index&&fa->leftson!=NULL) fa->rightson=newnode;
        if(fa->index>newnode->index&&fa->rightson==NULL) fa->leftson=newnode,newnode->deep=fa->deep+1,change_high(newnode->index);
        if(fa->index>newnode->index&&fa->rightson!=NULL) fa->leftson=newnode;
        change_factor(newnode->index);
        return ;
    }
    if(A->balance_factor==1){
        if(newnode->index>A->index){ //如果左边树高 插入到右侧 不会产生不平衡情况
            if(fa->index<newnode->index&&fa->leftson==NULL) fa->rightson=newnode,change_high(newnode->index);
            if(fa->index<newnode->index&&fa->leftson!=NULL) fa->rightson=newnode;
            if(fa->index>newnode->index&&fa->rightson==NULL) fa->leftson=newnode,newnode->deep=fa->deep+1,change_high(newnode->index);
            if(fa->index>newnode->index&&fa->rightson!=NULL) fa->leftson=newnode;
            change_factor(newnode->index);
            return ;
        }
        else{    //左边树高 插入左边就可能异常
            int decide; //记录是插入到左边还是右边 左边为0 右边为1
            if(fa->index<newnode->index&&fa->leftson==NULL) decide=1,fa->rightson=newnode,change_high(newnode->index);
            if(fa->index<newnode->index&&fa->leftson!=NULL) decide=1,fa->rightson=newnode;
            if(fa->index>newnode->index&&fa->rightson==NULL) decide=0,fa->leftson=newnode,newnode->deep=fa->deep+1,change_high(newnode->index);
            if(fa->index>newnode->index&&fa->rightson!=NULL) decide=0,fa->leftson=newnode;
            change_factor(newnode->index);
            if(A->balance_factor!=2) return ;
            if(decide==1) splay_LR(A);
            else splay_LL(A);
        }
    }
    if(A->balance_factor==-1){
        if(newnode->index<A->index){ //如果右边树高 插入到左侧 那么不会产生不平衡
            if(fa->index<newnode->index&&fa->leftson==NULL) fa->rightson=newnode,change_high(newnode->index);
            if(fa->index<newnode->index&&fa->leftson!=NULL) fa->rightson=newnode;
            if(fa->index>newnode->index&&fa->rightson==NULL) fa->leftson=newnode,newnode->deep=fa->deep+1,change_high(newnode->index);
            if(fa->index>newnode->index&&fa->rightson!=NULL) fa->leftson=newnode;
            change_factor(newnode->index);
            return ;
        }
        else{   //右边树高 插入到右侧 可能产生异常
            int decide; //记录是插入到左边还是右边 左边为0 右边为1
            if(fa->index<newnode->index&&fa->leftson==NULL) decide=1,fa->rightson=newnode,change_high(newnode->index);
            if(fa->index<newnode->index&&fa->leftson!=NULL) decide=1,fa->rightson=newnode;
            if(fa->index>newnode->index&&fa->rightson==NULL) decide=0,fa->leftson=newnode,newnode->deep=fa->deep+1,change_high(newnode->index);
            if(fa->index>newnode->index&&fa->rightson!=NULL) decide=0,fa->leftson=newnode;
            change_factor(newnode->index); 
            if(A->balance_factor!=-2) return ;     
            if(decide==1) splay_RR(A);
            else splay_RL(A);
        }
    }
}
template<class T,class K>
T AVL<T,K>::find(K index){
    Node<T,K> *current=root;
    while(current!=NULL){
        if(current->index==index) return current->element;
        else if(index<current->index) current=current->leftson;
        else current=current->rightson;
    }
    return '0';
}
template<class T,class K>
void AVL<T,K>::erase(K index){
    Node<T,K> *current=root;  //待删除元素节点
    Node<T,K> *fa=NULL;
    while(current!=NULL){
        if(current->index==index) break; //找到current 即为要删除的节点
        fa=current;
        if(current->index==index) break; //找到current 即为要删除的节点
        else if(index<current->index) current=current->leftson;
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
    AVL<char,int> tree(0);
    for(int i=1;i<=n;i++){
        cin>>index>>ch;
        tree.insert(index,ch);
    }
    cin>>m;
    
    for(int i=1;i<=m;i++){
        cin>>op;
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