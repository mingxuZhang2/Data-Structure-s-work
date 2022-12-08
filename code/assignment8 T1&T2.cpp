#include<bits/stdc++.h>
using namespace std;
int ac_high;
template<class T,class K>
struct Node{
    T element;     //element为平衡树节点所对应的元素
    K index;        //index为关键字（索引）
    int deep;      //当前节点的树高
    Node<T,K> *leftson;Node<T,K> *rightson;Node<T,K> *parent;
    int left_high;int right_high; //左子树高度 右子树高度
    int balance_factor; //平衡因子 定义为current->left_high-current->right_high;
    int highth; //树高 以A为根节点的树 树高定义为max(A->leth_high,A->right_high)+1
    Node(T val,K index,Node *l,Node *r){    
        this->element=val;this->index=index; 
        leftson=l;rightson=r;
        if(l==NULL) this->left_high=0;
        else this->left_high=max(l->left_high,l->right_high)+1;
        if(r==NULL) this->left_high=0;
        else this->right_high=max(r->left_high,r->right_high)+1;
        this->balance_factor=left_high-right_high;
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
    inline void bfs(Node<T,K> *A);
    inline void get_ans(Node<T,K> *A);
    Node<T,K> *root;
    int size;
};
template<class T,class K>
void AVL<T,K>::get_ans(Node<T,K> *now){
    if(now==root) now->deep=0;
    else now->deep++;
    if(now->leftson) get_ans(now->leftson);
    if(now->rightson) get_ans(now->rightson);
}
template<class T,class K>
void AVL<T,K>::bfs(Node<T,K> *now){
    queue<Node<T,K>*> q;
    q.push(now);
    int dep=5000;
    while(q.size()!=0){
        if(now->leftson==NULL&&now->rightson==NULL){ 
            dep=min(dep,now->deep);
            if(now->deep==dep) cout<<now->index<<" ";
        }
        cout<<endl;
        if(now->leftson) q.push(now->leftson);
        if(now->rightson) q.push(now->rightson);
        q.pop();
        now=q.front();
    }
}
template<class T,class K>
int AVL<T,K>::get_high(Node<T,K> *now){
    return max(now->left_high,now->right_high)+1;
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
        if(current->leftson==NULL&&current->rightson==NULL) return ans;
        if(current->balance_factor==1) current=current->leftson;
        else current=current->rightson;
    }
}
template<class T,class K>
void AVL<T,K>::splay_LL(Node<T,K> *A){
    Node<T,K> *fa=A->parent;
    Node<T,K> *now=A->leftson;
    Node<T,K> *temp_left=now->leftson;     //存储当前(将要替换A位置)的左右儿子
    Node<T,K> *temp_right=now->rightson;
    if(fa->leftson==A){
        fa->leftson=now;now->parent=fa;
        now->rightson=A;A->parent=now;
        A->leftson=temp_right;temp_right->parent=A;
        now->leftson=temp_left;temp_left->parent=now;
    }
    if(fa->rightson==A){
        fa->rightson=now;now->parent=fa;
        now->rightson=A;A->parent=now;
        A->leftson=temp_right;temp_right->parent=A;
        now->leftson=temp_left;temp_left->parent=now;
    }
    now->balance_factor=0;
    A->balance_factor=0; 
}
template<class T,class K>
void AVL<T,K>::splay_LR(Node<T,K> *A){
    Node<T,K> *now=A->leftson->rightson;   //now为之后即将成为新的根节点的节点 是LR
    Node<T,K> *fa=A->parent;               //原节点的父节点
    Node<T,K> *temp_exfa=A->leftson;       //now原本的父节点
    Node<T,K> *temp_left=now->leftson;     //now原来的左右儿子
    Node<T,K> *temp_right=now->rightson;
    int bf=now->balance_factor;
    if(fa->leftson==A){ 
        fa->leftson=now;now->parent=fa;
        now->rightson=A;A->parent=now;
        now->leftson=temp_exfa;temp_exfa->parent=now;
        A->leftson=temp_right;temp_right->parent=A;
        temp_exfa->rightson=temp_left;temp_left->parent=temp_exfa;
    }
    if(fa->rightson==A){
        fa->rightson=now;now->parent=fa;
        now->rightson=A;A->parent=now;
        now->leftson=temp_exfa;temp_exfa->parent=now;
        A->leftson=temp_right;temp_right->parent=A;
        temp_exfa->rightson=temp_left;temp_left->parent=temp_exfa;
    }
    if(bf==0){
        A->balance_factor=0;
        now->balance_factor=0;
        temp_exfa->balance_factor=0;
    }
    else if(bf==1){
        A->balance_factor=-1;
        now->balance_factor=0;
        temp_exfa->balance_factor=0;
    }
    else{
        A->balance_factor=0;
        now->balance_factor=0;
        temp_exfa->balance_factor=1;
    }
}
template<class T,class K>
void AVL<T,K>::splay_RR(Node<T,K> *A){
    Node<T,K> *fa=A->parent;         
    Node<T,K> *now=A->rightson;
    Node<T,K> *temp_left=now->leftson;
    Node<T,K> *temp_right=now->rightson;
    if(fa->leftson==A){
        fa->leftson=now;now->parent=fa;
        now->leftson=A;A->parent=now;
        A->rightson=temp_left;temp_left->parent=A;
        now->rightson=temp_right;temp_right->parent=now;
    }
    if(fa->rightson==A){
        fa->rightson=now;now->parent=fa;
        now->leftson=A;A->parent=now;
        A->rightson=temp_left;temp_left->parent=A;
        now->rightson=temp_right;temp_right->parent=now;
    }
    now->balance_factor=0;
    A->balance_factor=0;
}
template<class T,class K>
void AVL<T,K>::splay_RL(Node<T,K> *A){
    Node<T,K> *now=A->rightson->leftson;   //now为之后即将成为新的根节点的节点 是RL 
    Node<T,K> *fa=A->parent;               //原节点的父节点
    Node<T,K> *temp_exfa=A->rightson;       //now原本的父节点
    Node<T,K> *temp_left=now->leftson;     //now原来的左右儿子
    Node<T,K> *temp_right=now->rightson;
    int bf=now->balance_factor;
    if(fa->leftson==A){ 
        fa->leftson=now;now->parent=fa;
        now->leftson=A;A->parent=now;
        now->rightson=temp_exfa;temp_exfa->parent=now;
        A->rightson=temp_left;temp_right->parent=A;
        temp_exfa->leftson=temp_right;temp_left->parent=temp_exfa;
    }
    if(fa->rightson==A){
        fa->rightson=now;now->parent=fa;
        now->leftson=A;A->parent=now;
        now->rightson=temp_exfa;temp_exfa->parent=now;
        A->rightson=temp_left;temp_right->parent=A;
        temp_exfa->leftson=temp_right;temp_left->parent=temp_exfa;
    }
    if(bf==0){
        A->balance_factor=0;
        now->balance_factor=0;
        temp_exfa->balance_factor=0;
    }
    else if(bf==1){
        A->balance_factor=-1;
        now->balance_factor=0;
        temp_exfa->balance_factor=0;
    }
    else{
        A->balance_factor=0;
        now->balance_factor=0;
        temp_exfa->balance_factor=1;
    }    
}
template<class T,class K>
void AVL<T,K>::insert(K index,T element){
    Node<T,K> *current=root;
    Node<T,K> *fa=NULL;   //新建节点的父节点
    Node<T,K> *A=NULL;      //A是最后一个bf为1/-1的节点 如果需要splay 只可能是该节点需要
    while(current!=NULL){  //找插入节点的前驱，即找到新建节点的父亲
        fa=current;
        if(abs(current->balance_factor)==1) A=current;
        if(current->index>index) current=current->leftson;
        else if(current->index<index) current=current->rightson;
    }
    Node<T,K> *newnode=new Node<T,K>(element,index,NULL,NULL);
    if(root==NULL) {root=newnode;size++;return ;}
    if(fa->index<newnode->index) fa->rightson=newnode;
    if(fa->index>newnode->index) fa->leftson=newnode;
    newnode->parent=fa;
    //只有插入到叶节点时才会改变当前路径上所有节点的树高，否则只改变平衡因子
    while(fa){
        if(newnode==fa->leftson) fa->balance_factor++;
        else fa->balance_factor--;
        if(fa->balance_factor==0) return ;
        else if(abs(fa->balance_factor)==1){
            newnode=newnode->parent;
            fa=fa->parent;
        }
        else if(abs(fa->balance_factor)==2){  //fa为最后一个不稳定的节点 对该节点更新
            if(fa->balance_factor==2&&newnode->balance_factor==1) splay_LL(fa); //当前节点左子树高
            else if(fa->balance_factor==-2&&newnode->balance_factor==-1) splay_RR(fa); //当前节点右子树高
            else if(fa->balance_factor==2&&newnode->balance_factor==-1) splay_LR(fa); 
            else if(fa->balance_factor==-2&&newnode->balance_factor==1) splay_RL(fa);
        }
        else return ;
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
    ac_high=tree.calc_deep();
    tree.get_ans(tree.root);
    cout<<ac_high<<endl;
    tree.bfs(tree.root);
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


6
20 a
15 b
25 c
12 d
18 e
30 f

expect output:
the high is 3
the index is 12 18 30
*/